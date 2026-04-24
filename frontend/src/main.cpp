//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include <cstdint>
#include "CPU.h"

using namespace gb::core;

int main (int argc, char ** argv) {
    return 0;
}

void run_frame(gb::core::CPU& cpu) {
    const int MAX_CYCLES_PER_FRAME = 70224;
    int current_cycles = 0;

    while (current_cycles < MAX_CYCLES_PER_FRAME) {
        uint8_t cycles = cpu.step();

        current_cycles += cycles;
    }


}