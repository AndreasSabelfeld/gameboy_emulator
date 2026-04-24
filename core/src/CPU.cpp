//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "CPU.h"

namespace gb::core {
    CPU::CPU() = default;

    uint8_t CPU::step() {
        // 1. Fetch instruction at PC
        PC++;
        // 2. Decode opcode
        // 3. Execute instruction

        // return amount of cycles operation took
        uint8_t cycles_taken = 0;
        return cycles_taken;
    }
}