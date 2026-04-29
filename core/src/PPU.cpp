//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "PPU.h"

namespace gb::core {
    PPU::PPU() = default;

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
            /* todo: When the CPU writes to this register, it tells the Gameboy to copy 160 bytes of memory from the
             * Cartridge or WRAM directly into the PPU's OAM (Sprite) memory. */
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

    }
}