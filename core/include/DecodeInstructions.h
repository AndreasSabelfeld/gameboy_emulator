//
// Created by Andreas Sabelfeld on 27.04.2026.
//

#pragma once

#include <cstdint>

namespace gb::core {
    struct Instruction {
        const char* mnemonic;       // name of instruction
        uint8_t length;             // how many bytes
        uint8_t cycles;             // how many cycles the instruction takes to execute
        void (*execute)();          // execution function
    };
}
