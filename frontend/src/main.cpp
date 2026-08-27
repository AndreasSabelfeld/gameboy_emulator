//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include <iostream>
#include <string>
#include <vector>

#include "CPU.h"
#include "MMU.h"
#include "Cartridge.h"
#include "PPU.h"
#include "APU.h"
#include "Joypad.h"
#include "Timer.h"
#include "SerialCable.h"
#include "Renderer.h"

// Hardcoded paths for debug mode
const std::string TEST_ROOT = "/Users/andy/CLionProjects/gameboy_emulator/roms/gb-test-roms-master/";

std::vector<std::string> roms = {
    "cgb_sound/cgb_sound.gb",
    "cpu_instrs/cpu_instrs.gb",             // passed
    "dmg_sound/dmg_sound.gb",
    "instr_timing/instr_timing.gb",         // passed
    "interrupt_time/interrupt_time.gb",
    "mem_timing/mem_timing.gb",             // passed
    "mem_timing-2/mem_timing.gb",           // passed
    "oam_bug/oam_bug.gb"
};

void run_frame(gb::core::CPU& cpu) {
    constexpr int MAX_CYCLES_PER_FRAME = 70224;
    cpu.frame_cycles = 0;

    while (cpu.frame_cycles < MAX_CYCLES_PER_FRAME) {
        cpu.step();
    }
}

int main(int argc, char** argv) {
    std::string rom_path;

#ifdef EMULATOR_DEBUG
    // If debugging, ignore arguments and load the specific test ROM
    uint8_t test_rom_idx = 7;
    rom_path = TEST_ROOT + roms[test_rom_idx];
    std::cout << "[DEBUG MODE] Overriding input with test ROM: " << rom_path << std::endl;
#else
    // Normal Mode: Require a ROM path via command line argument
    if (argc < 2) {
        std::cerr << "Error: No ROM provided.\n";
        std::cerr << "Usage: " << argv[0] << " <path_to_rom.gb>\n";
        return EXIT_FAILURE;
    }
    rom_path = argv[1];
#endif

    try {
        // Initialize Hardware Components
        auto cartridge = gb::core::Cartridge(rom_path);
        auto ppu = gb::core::PPU();
        ppu.set_cartridge(&cartridge);

        auto apu = gb::core::APU();
        auto joypad = gb::core::Joypad();
        auto timer = gb::core::Timer();
        auto serial_cable = gb::core::SerialCable();

        auto mmu = gb::core::MMU(&cartridge, &ppu, &apu, &joypad, &timer, &serial_cable);

        // Wire up MMU dependencies
        timer.set_mmu(&mmu);
        ppu.set_mmu(&mmu);
        joypad.set_mmu(&mmu);

        auto cpu = gb::core::CPU(&mmu, &timer, &ppu);

        // Initialize Frontend
        gb::frontend::Renderer renderer(4); // 4x scale
        std::cout << "Starting Emulator with ROM: " << rom_path << std::endl;

        // Main Emulator Loop
        bool running = true;
        while (running) {
            running = renderer.poll_events(joypad);
            run_frame(cpu);
            renderer.render_frame(ppu.get_screen_buffer());
        }

    } catch (const std::exception& e) {
        // Catch initialization errors (like a bad ROM path)
        std::cerr << "Fatal Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}