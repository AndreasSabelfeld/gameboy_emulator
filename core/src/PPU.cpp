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
            stat = value;
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
            uint16_t offset;

            /*if (dma < 0x80) {
                // read ROM
                offset = 0;
                std::copy_n(cartridge->get_rom()->begin() + sourceAddr - offset, 160, oam.begin());
            } else if (dma < 0xA0) {
                // read VRAM
                offset = 0x8000;
                std::copy_n(vram.begin() + sourceAddr - offset, 160, oam.begin());
            } else if (dma < 0xC0) {
                // read SRAM
                offset = 0xA000;
                std::copy_n(cartridge->get_sram()->begin() + sourceAddr - offset, 160, oam.begin());
            } else if (dma < 0xE0) {
                // read WRAM
                offset = 0xC000;
                std::copy_n(cartridge->get_rom()->begin() + sourceAddr - offset, 160, oam.begin());
            } else {
                // Out of bounds
            }*/
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
}