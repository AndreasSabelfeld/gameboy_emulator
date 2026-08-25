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

const std::string ROM_ROOT = "/Users/andy/CLionProjects/gameboy_emulator/roms/gb-test-roms-master/";

std::array<std::string, 4> roms = {
    "cpu_instrs/cpu_instrs.gb",
    "instr_timing/instr_timing.gb",
    "mem_timing/mem_timing.gb",
    "mem_timing-2/mem_timing.gb"
};

void run_frame(gb::core::CPU& cpu, gb::core::Timer& timer) {
    constexpr int MAX_CYCLES_PER_FRAME = 70224;
    cpu.frame_cycles = 0;

    while (cpu.frame_cycles < MAX_CYCLES_PER_FRAME) {
        cpu.step();
    }
}

int main (int argc, char ** argv) {

    auto cartridge = gb::core::Cartridge(ROM_ROOT + roms[2]);
    auto ppu = gb::core::PPU();
    ppu.set_cartridge(&cartridge);
    auto apu = gb::core::APU();
    auto joypad = gb::core::Joypad();
    auto timer = gb::core::Timer();
    auto serial_cable = gb::core::SerialCable();

    auto mmu = gb::core::MMU(&cartridge, &ppu, &apu, &joypad, &timer, &serial_cable);
    timer.set_mmu(&mmu);
    ppu.set_mmu(&mmu);

    auto cpu = gb::core::CPU(&mmu, &timer);

    std::cout << "Starting Emulator..." << std::endl;

    while (true) {
        run_frame(cpu, timer);
    }

    return 0;
}
