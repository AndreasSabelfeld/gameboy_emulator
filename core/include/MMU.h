//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <array>
#include <cstdint>

namespace gb::core {

    // Forward declarations for other hardware components
    class Cartridge;
    class PPU;       // Pixel Processing Unit (Graphics)
    class APU;       // Audio Processing Unit
    class Joypad;    // Controller inputs
    class Timer;
    class SerialCable;

    class MMU {
    public:
        MMU(Cartridge* cartridge, PPU* ppu, APU* apu, Joypad* joypad, Timer* timer, SerialCable* cable);

        uint8_t read(uint16_t address);
        void write(uint16_t address, uint8_t value);

    private:
        Cartridge* cartridge;
        PPU* ppu;
        APU* apu;
        Joypad* joypad;
        Timer* timer;
        SerialCable* cable;

        // 57760 bytes of memory that can actually be accessed:

        // std::array<uint8_t, 0x8000> ROM; // 0x0000 - 0x7FFF => Handled by Cartridge
        // std::array<uint8_t, 0x2000> vram;// 0x8000 - 0x9FFF => Owned by PPU
        // std::array<uint8_t, 0x2000> SRAM;// 0xA000 - 0xBFFF => Handled by Cartridge
        std::array<uint8_t, 0x2000> wram;   // 0xC000 - 0xDFFF
                                            // 0xE000 - 0xFDFF is an exact mirror of the WRAM (prohibited)
        // std::array<uint8_t, 0x009F> oam; // 0xFE00 - 0xFE9F => Owned by PPU
                                            // 0xFEA0 - 0xFEFF is unmapped / prohibited
        // std::array<uint8_t, 0x007F> io;  // 0xFF00 - 0xFF7F =>   Handled by Joystick Class,
                                            //                      Serial Link Cable,
                                            //                      Timers,
                                            //                      Audio (APU),
                                            //                      Graphics Registers (PPU)
        std::array<uint8_t, 0x007E> hram;   // 0xFF80 - 0xFFFE

        uint8_t IF_reg = 0xE1;              // 0xFF0F (Top 3 bits always 1)
        uint8_t IE_reg = 0x00;              // 0xFFFF

        // The DMG Boot ROM (256 bytes)
        std::array<uint8_t, 256> boot_rom;
        bool boot_rom_active;               // Maps 0x0000-0x00FF to boot_rom until the game disables it

    };
}