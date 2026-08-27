//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <array>

#include "Cartridge.h"
#include "MMU.h"

namespace gb::core {
    class PPU {
    public:
        PPU();
        PPU(Cartridge* cartridge, MMU* mmu);

        void tick(uint8_t cycles);
        bool lcd_enabled() const;
        void check_lyc_interrupt();
        void draw_scanline();
        void draw_sprites();

        uint32_t get_color(uint8_t shade);
        void set_mode(uint8_t new_mode);

        uint8_t read_vram(uint16_t address);
        void write_vram(uint16_t address, uint8_t value);
        uint8_t read_oam(uint16_t address);
        void write_oam(uint16_t address, uint8_t value);
        uint8_t read_register(uint16_t address) const;
        void write_register(uint16_t address, uint8_t value);

        void set_cartridge(Cartridge *cartridge);
        void set_mmu(MMU *mmu);
        const uint32_t *get_screen_buffer() const;

    private:
        Cartridge* cartridge;
        MMU* mmu;

        uint32_t screen_buffer[160 * 144];
        std::array<uint8_t, 0x2000> vram{};   // 0x8000 - 0x9FFF
        std::array<uint8_t, 0x0A0F> oam{};    // 0xFE00 - 0xFE9F

        uint8_t lcdc = 0x91;    /* 0xFF40 - LCD Control
                                 * Bit 4: Tile Data Base Select (0 = 0x8800 signed, 1 = 0x8000 unsigned)
                                 * Bit 3: Tile Map Select       (0 = 0x9800, 1 = 0x9C00)
                                 * Bit 0: BG Enable
                                 */
        uint8_t stat = 0x85;    /* 0xFF41 - LCD Status
                                 * Bit 6: LYC=LY interrupt enable
                                 * Bit 5: Mode 2 OAM interrupt enable
                                 * Bit 4: Mode 1 VBlank interrupt enable
                                 * Bit 3: Mode 0 HBlank interrupt enable
                                 * Bit 2: LYC=LY coincidence flag (1=Match)
                                 * Bits 1-0: current mode
                                 */
        uint8_t scy  = 0x00;    // 0xFF42 - Scroll Y
        uint8_t scx  = 0x00;    // 0xFF43 - Scroll X
        uint8_t ly   = 0x00;    // 0xFF44 - LCD Y Coordinate (Current scanline)
        uint8_t lyc  = 0x00;    // 0xFF45 - LY Compare
        uint8_t dma  = 0xFF;    // 0xFF46 - OAM DMA Transfer
        uint8_t bgp  = 0xFC;    // 0xFF47 - Background Palette
        uint8_t obp0 = 0xFF;    // 0xFF48 - Object Palette 0
        uint8_t obp1 = 0xFF;    // 0xFF49 - Object Palette 1
        uint8_t wy   = 0x00;    // 0xFF4A - Window Y
        uint8_t wx   = 0x00;    // 0xFF4B - Window X

        int scanline_cycle = 0;
        uint8_t current_mode = 2;
    };
}
