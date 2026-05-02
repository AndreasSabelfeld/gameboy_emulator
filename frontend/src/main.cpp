//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include <iostream>

#include "CPU.h"
#include "MMU.h"
#include "Cartridge.h"
#include "PPU.h"
#include "APU.h"
#include "Joypad.h"
#include "Timer.h"
#include "SerialCable.h"

std::string_view rom_file_path = "/Users/andy/CLionProjects/gameboy_emulator/roms/gb-test-roms-master/cpu_instrs/cpu_instrs.gb";
// std::string_view rom_file_path = "/Users/andy/CLionProjects/gameboy_emulator/roms/gb-test-roms-master/instr_timing/instr_timing.gb";
// std::string_view rom_file_path = "/Users/andy/CLionProjects/gameboy_emulator/roms/gb-test-roms-master/mem_timing/mem_timing.gb";

int main (int argc, char ** argv) {

    auto cartridge = gb::core::Cartridge(rom_file_path);
    auto ppu = gb::core::PPU();
    auto apu = gb::core::APU();
    auto joypad = gb::core::Joypad();
    auto timer = gb::core::Timer();
    auto serial_cable = gb::core::SerialCable();

    auto mmu = gb::core::MMU(&cartridge, &ppu, &apu, &joypad, &timer, &serial_cable);

    auto cpu = gb::core::CPU(&mmu);

    std::cout << "Starting Emulator..." << std::endl;

    while (true) {
        cpu.step();
    }

    return 0;
}

void run_frame(gb::core::CPU& cpu) {
    constexpr int MAX_CYCLES_PER_FRAME = 70224;
    int current_cycles = 0;

    while (current_cycles < MAX_CYCLES_PER_FRAME) {
        uint8_t cycles = cpu.step();

        current_cycles += cycles;
    }


}