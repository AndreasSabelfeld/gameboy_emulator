//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once
#include <cstdint>

namespace gb::core {
    class Timer {
    public:
        Timer();
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

    private:
        uint8_t divider_register;       // 0xFF04
        uint8_t timer_counter;          // 0xFF05
        uint8_t timer_modulo;           // 0xFF06
        uint8_t timer_control;          // 0xFF07
    };
}
