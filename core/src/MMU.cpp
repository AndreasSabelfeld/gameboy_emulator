//
// Created by Andreas Sabelfeld on 24.04.2026.
//
// Memory Management Unit

#include "MMU.h"
#include "Cartridge.h"
#include "PPU.h"
#include "Joypad.h"
#include "APU.h"
#include "SerialCable.h"
#include "Timer.h"

namespace gb::core {
    MMU::MMU(Cartridge* cartridge, PPU* ppu, APU* apu, Joypad* joypad, Timer* timer, SerialCable* cable) {
        this->cartridge = cartridge;
        this->ppu = ppu;
        this->apu = apu;
        this->joypad = joypad;
        this->timer = timer;
        this->cable = cable;
    }

    uint8_t MMU::read(uint16_t address) {
        if (address < 0x8000) {                // reading rom
            return cartridge->read_rom(address);
        } if (address < 0xA000) {              // reading vram
            return ppu->read_vram(address);
        } if (address < 0xC000) {              // reading sram
            return cartridge->read_sram(address);
        } if (address < 0xE000) {              // reading wram
            return wram[address - 0xC000];
        } if (address < 0xFE00) {              // reading echo ram (prohibited, but possible)
            return wram[address - 0xE000];
        } if (address < 0xFEA0) {              // reading oam
            return ppu->read_oam(address);
        } if (address < 0xFF00) {              // unmapped / prohibited
            return 0xFF;
        } if (address < 0xFF01) {              // reading io
            return joypad->read(address);
        } if (address < 0xFF03) {              // serial cable
            return cable->read(address);
        } if (address < 0xFF08) {              // timer
            return timer->read(address);
        } if (address < 0xFF10) {              // Interrupt Flag (top 3 bits always 1)
            return IF_reg | 0xE0;
        } if (address < 0xFF40) {              // audio
            return apu->read(address);
        } if (address < 0xFF80) {              // PPU Registers
            return ppu->read_register(address);
        } if (address < 0xFFFF) {              // reading hram
            return hram[address - 0xFF80];
        } if (address == 0xFFFF) {
            return IE_reg;
        }

        return 0xFF;
    }
    void MMU::write(uint16_t address, uint8_t value) {
        if (address < 0x8000) {                // writing rom (MBC commands)
            cartridge->write(address, value);
        } else if (address < 0xA000) {         // writing vram
            ppu->write_vram(address, value);
        } else if (address < 0xC000) {         // writing sram
            cartridge->write(address, value);
        } else if (address < 0xE000) {         // writing wram
            wram[address - 0xC000] = value;
        } else if (address < 0xFE00) {         // writing echo ram
            wram[address - 0xE000] = value;    // physically mirrors WRAM
        } else if (address < 0xFEA0) {         // writing oam
            ppu->write_oam(address, value);
        } else if (address < 0xFF00) {         // unmapped / prohibited
            // hardware ignores this write.
        } else if (address < 0xFF01) {         // writing joypad
            joypad->write(address, value);
        } else if (address < 0xFF03) {         // serial cable
            cable->write(address, value);
        } else if (address < 0xFF08) {         // timer
            timer->write(address, value);
        } else if (address < 0xFF10) {
            IF_reg = value;
        } else if (address < 0xFF40) {         // audio
            apu->write(address, value);
        } else if (address < 0xFF80) {         // PPU Registers
            ppu->write_register(address, value);
        } else if (address < 0xFFFF) {         // writing hram
            hram[address - 0xFF80] = value;
        } else if (address == 0xFFFF) {        // IE register
            IE_reg = value;
        }
    }

}
