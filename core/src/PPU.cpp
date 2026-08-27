//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "PPU.h"

namespace gb::core {
    PPU::PPU() {
        this->cartridge = nullptr;
        this->mmu = nullptr;
    }

    PPU::PPU(Cartridge* cartridge, MMU* mmu) {
        this->cartridge = cartridge;
        this->mmu = mmu;
    }

    void PPU::tick(uint8_t cycles) {
        // GB has 154 scanlines (0-153)
        // each scanline takes exactly 456 T-cycles

        // scanlines 0-143 are the visible lines, 144-153 are invisible scanlines ("VBlank lines")

        // PPU modes: (a "dot" = 2^22 Hz)
        // Mode 2: OAM scan, 80 dots
        // Mode 3: Drawing pixels, 172-289 dots
        // Mode 0: Horizontal Blank, 87-204 dots

        if (!lcd_enabled()) {
            // If the screen is turned off, reset cycles and LY, and exit.
            scanline_cycle = 0;
            ly = 0;
            current_mode = 0;      // Mode 0
            // Ensure STAT register reflects Mode 0
            stat = (stat & 0xFC) | current_mode;
            return;
        }

        scanline_cycle += cycles;

        switch (current_mode) {
            case 2: // OAM scan
                if (scanline_cycle >= 80) {
                    scanline_cycle -= 80;
                    set_mode(3);
                } break;
            case 3: // Pixel Transfer, we fix it to 172 cycles for scanline rendering even though it's variable
                if (scanline_cycle >= 172) {
                    scanline_cycle -= 172;
                    set_mode(0);

                    draw_scanline();
                } break;
            case 0: // HBlank
                if (scanline_cycle >= 204) {
                    scanline_cycle -= 204;
                    ly++;

                    check_lyc_interrupt();

                    if (ly == 144) {
                        set_mode(1);
                        // Fire the VBlank hardware interrupt (Bit 0 of IF)
                        mmu->write(0xFF0F, mmu->read(0xFF0F) | 0x01);
                    } else {
                        set_mode(2);
                    }
                } break;
            case 1: // VBlank
                if (scanline_cycle >= 456) {
                    scanline_cycle -= 456;
                    ly++;

                    if (ly > 153) {
                        // VBlank is over, restart frame
                        ly = 0;
                        set_mode(2);
                    }

                    check_lyc_interrupt();
                } break;
        }
    }

    void PPU::draw_scanline() {
        // we do not emulate 100% accurate rendering

        if (ly >= 144) return; // only draw visible scanlines
        if (!(lcdc & 0x01)) {
            // background disabled, draw blank line
            for (int x = 0; x < 160; x++) {
                screen_buffer[ly * 160 + x] = 0xFFFFFFFF; // White
            }
            return;
        }
        // is window enabled and the window currently visible?
        bool window_enabled = (lcdc & (1 << 5)) && (wy <= ly);
        bool use_unsigned_addressing = (lcdc & (1 << 4)) != 0;

        for (uint8_t x = 0; x < 160; x++) {
            bool is_window = false;
            if (window_enabled && x >= static_cast<int>(wx) - 7) {
                is_window = true;
            }

            uint8_t x_pos;
            uint8_t y_pos;
            uint16_t map_base;
            if (is_window) {
                x_pos = x - (wx - 7);
                // on actual hardware the window has an internal line counter that tracks how many lines of the
                // window have been successfully drawn, this will not work on more obscure ROMS:
                y_pos = ly - wy;
                // window tile map select (bit 6)
                map_base = (lcdc & (1 << 6)) ? 0x9C00 : 0x9800;
            } else {
                x_pos = x + scx;
                y_pos = ly + scy;
                // background tile map select (bit 3)
                map_base = (lcdc & (1 << 3)) ? 0x9C00 : 0x9800;
            }

            uint16_t tile_row = y_pos/8;
            uint8_t tile_col = x_pos/8;

            uint16_t tile_address = map_base + (tile_row * 32) + tile_col;
            uint8_t tile_id = mmu->read(tile_address);

            uint16_t tile_data_base;
            if (use_unsigned_addressing) {
                tile_data_base = 0x8000 + (tile_id * 16);
            } else {
                tile_data_base = 0x9000 + (static_cast<int8_t>(tile_id) * 16); // make signed
            }
            uint8_t row_in_tile = y_pos % 8;
            uint8_t byte1 = mmu->read (tile_data_base + row_in_tile * 2);
            uint8_t byte2 = mmu->read (tile_data_base + row_in_tile * 2 + 1);

            uint8_t bit_index = 7 - (x_pos % 8);
            uint8_t low_bit  = (byte1 >> bit_index) & 0x01;
            uint8_t high_bit = (byte2 >> bit_index) & 0x01;
            uint8_t color_id = (high_bit << 1) | low_bit;
            uint8_t shade = (bgp >> (color_id * 2)) & 0x3;

            screen_buffer[ly * 160 + x] = get_color(shade);
        }

        draw_sprites();
    }

    void PPU::draw_sprites() {
        // Check if Sprites are enabled (Bit 1)
        if (!(lcdc & 0x02)) return;

        // Check sprite size (Bit 2: 0 = 8x8, 1 = 8x16)
        bool use_8x16 = (lcdc & 0x04) != 0;
        int sprite_height = use_8x16 ? 16 : 8;

        for (int i = 39; i >= 0; i--) {
            // Find the sprite in OAM
            uint16_t sprite_addr = 0xFE00 + (i * 4);

            // Subtract offsets to get actual screen coordinates
            int sprite_y = mmu->read(sprite_addr) - 16;
            int sprite_x = mmu->read(sprite_addr + 1) - 8;
            uint8_t tile_id = mmu->read(sprite_addr + 2);
            uint8_t attributes = mmu->read(sprite_addr + 3);

            // Does this sprite intersect the current scanline (LY)?
            if (ly >= sprite_y && ly < (sprite_y + sprite_height)) {

                bool y_flip = (attributes & (1 << 6)) != 0;
                bool x_flip = (attributes & (1 << 5)) != 0;
                bool priority = (attributes & (1 << 7)) != 0;

                // Choose palette (OBP0 at 0xFF48 or OBP1 at 0xFF49)
                uint16_t palette_addr = (attributes & (1 << 4)) ? 0xFF49 : 0xFF48;
                uint8_t palette = mmu->read(palette_addr);

                // Which row of the sprite are we currently drawing?
                int line_in_sprite = ly - sprite_y;

                if (y_flip) {
                    // Read from the bottom up instead
                    line_in_sprite = (sprite_height - 1) - line_in_sprite;
                }

                // In 8x16 mode, the top tile is even, bottom is odd.
                // Hardware ignores the bottom bit of the tile ID.
                if (use_8x16) {
                    tile_id &= 0xFE; // Ignore bit 0
                    if (line_in_sprite >= 8) {
                        tile_id++; // Move to the bottom tile
                    }
                }

                // Fetch the 2 bytes for this row of the sprite
                uint16_t tile_data_addr = 0x8000 + (tile_id * 16);
                uint8_t row_in_tile = line_in_sprite % 8;
                uint8_t byte1 = mmu->read(tile_data_addr + (row_in_tile * 2));
                uint8_t byte2 = mmu->read(tile_data_addr + (row_in_tile * 2) + 1);

                // Draw the 8 pixels horizontally
                for (int px = 0; px < 8; px++) {
                    int screen_x = sprite_x + px;

                    // Don't draw if pixel is off-screen horizontally
                    if (screen_x < 0 || screen_x >= 160) continue;

                    // Extract color ID, handling X-flip
                    int bit_index = x_flip ? px : (7 - px);
                    uint8_t low_bit  = (byte1 >> bit_index) & 0x01;
                    uint8_t high_bit = (byte2 >> bit_index) & 0x01;
                    uint8_t color_id = (high_bit << 1) | low_bit;

                    // Color ID 0 is ALWAYS transparent for sprites
                    if (color_id == 0) continue;

                    // Sprite Priority: If bit 7 is set, the sprite hides BEHIND
                    // non-white background pixels. (We check our buffer to see if
                    // the BG pixel there is currently white/color 0).
                    if (priority) {
                        if (screen_buffer[ly * 160 + screen_x] != get_color(0)) {
                            continue;
                        }
                    }

                    // Translate through sprite palette and draw
                    uint8_t shade = (palette >> (color_id * 2)) & 0x03;
                    screen_buffer[ly * 160 + screen_x] = get_color(shade);
                }
            }
        }
    }

    uint32_t PPU::get_color(uint8_t shade) {
        switch (shade) {
            case 0: return 0xFFFFFFFF; // White / Lightest Green (0xFFE0F8D0)
            case 1: return 0xFFAAAAAA; // Light Gray / Light Green (0xFF88C070)
            case 2: return 0xFF555555; // Dark Gray  / Dark Green  (0xFF346856)
            case 3: return 0xFF000000; // Black      / Darkest Green (0xFF081820)
            default: return 0xFFFFFFFF;
        }
    }

    bool PPU::lcd_enabled() const {
        return (lcdc & 0x80) != 0;
    }

    void PPU::set_mode(uint8_t new_mode) {
        current_mode = new_mode;

        // Clear the bottom 2 bits and insert the new mode
        stat = (stat & 0xFC) | new_mode;

        // Check if the game requested an interrupt for this mode transition
        bool request_interrupt = false;
        if (new_mode == 0 && (stat & (1 << 3))) request_interrupt = true;
        if (new_mode == 1 && (stat & (1 << 4))) request_interrupt = true;
        if (new_mode == 2 && (stat & (1 << 5))) request_interrupt = true;

        if (request_interrupt) {
            // Fire the LCD STAT hardware interrupt (Bit 1 of IF)
            mmu->write(0xFF0F, mmu->read(0xFF0F) | 0x02);
        }
    }

    void PPU::check_lyc_interrupt() {
        if (ly == lyc) {
            // set coincidence flag to 1
            stat |= (1 << 2);

            // check if LY=LYC interrupt is enabled
            if (stat & (1 << 6)) {
                // request LCD STAT interrupt
                mmu->write(0xFF0F, mmu->read(0xFF0F) | 0x02);
            }
        } else {
            // clear coincidence flag
            stat &= ~(1 << 2);
        }
    }

    uint8_t PPU::read_vram(uint16_t address) {
        if (address >= 0x8000 && address < 0xA000) {
            return vram[address - 0x8000];
        }
        return 0xFF;
    }

    void PPU::write_vram(uint16_t address, uint8_t value) {
        if (address >= 0x8000 && address < 0xA000) {
            vram[address - 0x8000] = value;
        }
    }

    uint8_t PPU::read_oam(uint16_t address) {
        if (address >= 0xFE00 && address < 0xFEA0) {
            return oam[address - 0xFE00];
        }
        return 0xFF;
    }

    void PPU::write_oam(uint16_t address, uint8_t value) {
        if (address >= 0xFE00 && address < 0xFEA0) {
            oam[address - 0xFE00] = value;
        }
    }

    uint8_t PPU::read_register(uint16_t address) const {
        if (address == 0xFF40)
            return lcdc;
        if (address == 0xFF41)
            return stat;
        if (address == 0xFF42)
            return scy;
        if (address == 0xFF43)
            return scx;
        if (address == 0xFF44)
            return ly;
        if (address == 0xFF45)
            return lyc;
        if (address == 0xFF46)
            return dma;
        if (address == 0xFF47)
            return bgp;
        if (address == 0xFF48)
            return obp0;
        if (address == 0xFF49)
            return obp1;
        if (address == 0xFF4A)
            return wy;
        if (address == 0xFF4B)
            return wx;

        return 0xFF;
    }
    void PPU::write_register(uint16_t address, uint8_t value) {
        if (address == 0xFF40)
            lcdc = value;
        if (address == 0xFF41)
            // mask the bottom 3 bits since they are read-only
            stat = (value & 0xF8) | (stat & 0x07) | 0x80;
        if (address == 0xFF42)
            scy = value;
        if (address == 0xFF43)
            scx = value;
        if (address == 0xFF44)
            ly = value;
        if (address == 0xFF45)
            lyc = value;
        if (address == 0xFF46) {
            dma = value;
            uint16_t sourceAddr = dma * 0x100;

            if (sourceAddr < 0x8000) {
                // Read ROM
                auto rom = cartridge->get_rom();
                if (sourceAddr + 160 <= rom->size()) {
                    std::copy_n(rom->begin() + sourceAddr, 160, oam.begin());
                }
            }
            else if (sourceAddr >= 0x8000 && sourceAddr < 0xA000) {
                // Read VRAM (Max VRAM size is 0x2000 / 8192 bytes)
                uint16_t offset_vram = sourceAddr - 0x8000;
                if (offset_vram + 160 <= vram.size()) {
                    std::copy_n(vram.begin() + offset_vram, 160, oam.begin());
                }
            }
            else if (sourceAddr >= 0xA000 && sourceAddr < 0xC000) {
                // Read SRAM (Check if SRAM actually exists first)
                auto sram = cartridge->get_sram();
                if (sram && !sram->empty()) {
                    uint16_t offset_sram = sourceAddr - 0xA000;
                    if (offset_sram + 160 <= sram->size()) {
                        std::copy_n(sram->begin() + offset_sram, 160, oam.begin());
                    }
                }
            }
            else if ((sourceAddr >= 0xC000 && sourceAddr < 0xE000) || (sourceAddr >= 0xE000 && sourceAddr < 0xFE00)) {
                // Read WRAM or Echo RAM (Echo RAM 0xE000-0xFDFF maps back to WRAM 0xC000-0xDDFF)
                uint16_t base_wram = (sourceAddr >= 0xE000) ? sourceAddr - 0x2000 : sourceAddr;
                uint16_t offset_wram = base_wram - 0xC000;

                auto wram = mmu->get_wram();
                if (wram && offset_wram + 160 <= wram->size()) {
                    std::copy_n(wram->begin() + offset_wram, 160, oam.begin());
                }
            }
            else {
                // Out of bounds or restricted area (OAM, I/O, HRAM)
                // Real hardware fills OAM with 0xFF or un-updated data during invalid DMAs
                for (int i = 0; i < 160; i++) {
                    write_oam(0xFE00 + i, 0xFF);
                }
            }
        }
        if (address == 0xFF47)
            bgp = value;
        if (address == 0xFF48)
            obp0 = value;
        if (address == 0xFF49)
            obp1 = value;
        if (address == 0xFF4A)
            wy = value;
        if (address == 0xFF4B)
            wx = value;

    }

    void PPU::set_cartridge(Cartridge* cartridge) {
        this->cartridge = cartridge;
    }

    void PPU::set_mmu(MMU* mmu) {
        this->mmu = mmu;
    }

    const uint32_t* PPU::get_screen_buffer() const {
        return screen_buffer;
    }
}