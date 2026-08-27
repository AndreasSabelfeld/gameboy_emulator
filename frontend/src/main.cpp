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

#include "Renderer.h"

const std::string ROM_ROOT = "/Users/andy/CLionProjects/gameboy_emulator/roms/";
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

int main (int argc, char ** argv) {
    auto cartridge = gb::core::Cartridge(ROM_ROOT + "zelda.gb");
#ifdef EMULATOR_DEBUG
    uint8_t test_rom_idx = 7;
    cartridge = gb::core::Cartridge(TEST_ROOT + roms[test_rom_idx]);
#endif
    auto ppu = gb::core::PPU();
    ppu.set_cartridge(&cartridge);
    auto apu = gb::core::APU();
    auto joypad = gb::core::Joypad();
    auto timer = gb::core::Timer();
    auto serial_cable = gb::core::SerialCable();

    auto mmu = gb::core::MMU(&cartridge, &ppu, &apu, &joypad, &timer, &serial_cable);
    timer.set_mmu(&mmu);
    ppu.set_mmu(&mmu);
    joypad.set_mmu(&mmu);

    auto cpu = gb::core::CPU(&mmu, &timer, &ppu);

    gb::frontend::Renderer renderer(4); // 4x scale

    std::cout << "Starting Emulator..." << std::endl;

    bool running = true;
    while (running) {
        running = renderer.poll_events(joypad);
        run_frame(cpu);
        renderer.render_frame(ppu.get_screen_buffer());
    }

    return 0;
}
