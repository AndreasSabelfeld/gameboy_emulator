//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <cstdint>

namespace gb::core {
    union Register {
        uint16_t word;
        struct {
            uint8_t low;
            uint8_t high;
        };
    };

    class CPU {
    public:
        CPU();

        uint8_t step();
        void reset();

    private:
        Register AF = { .word = 0x01B0 };       // we use 'BO' for F for testing purposes
        Register BC = { .word = 0x0013 };
        Register DE = { .word = 0x00D8 };
        Register HL = { .word = 0x014D };

        uint16_t PC = 0x0100;        // program counter TODO: initialize at 0x0000 to emulate boot-up sequence once ready
        uint16_t SP = 0xFFFE;        // stack pointer
    };
}