//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once
#include <cstdint>
#include "MMU.h"

namespace gb::core {
    class Timer {
    public:
        Timer();
        void set_mmu(MMU* mmu);
        void tick(uint8_t cycles);
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);
        uint8_t read_DIV() const;
        void write_DIV();

    private:
        MMU* mmu;

        uint16_t SYS_CLK = 0xABCC;        // master counter

        uint8_t TIMA = 0x00;           // 0xFF05
        uint8_t TMA = 0x00;            // 0xFF06
        uint8_t TAC = 0xF8;            // 0xFF07

        int overflow_delay = 0;
    };
}
