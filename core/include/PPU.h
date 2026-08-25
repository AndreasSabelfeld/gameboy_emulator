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

        uint8_t read_vram(uint16_t address);
        void write_vram(uint16_t address, uint8_t value);
        uint8_t read_oam(uint16_t address);
        void write_oam(uint16_t address, uint8_t value);

        uint8_t read_register(uint16_t address) const;
        void write_register(uint16_t address, uint8_t value);

        void set_cartridge(Cartridge *cartridge);

        void set_mmu(MMU *mmu);

    private:
        Cartridge* cartridge;
        MMU* mmu;

        std::array<uint8_t, 0x2000> vram{};   // 0x8000 - 0x9FFF
        std::array<uint8_t, 0x009F> oam{};    // 0xFE00 - 0xFE9F

        uint8_t lcdc = 0x91;    // 0xFF40 - LCD Control
        uint8_t stat = 0x85;    // 0xFF41 - LCD Status
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
    };
}
