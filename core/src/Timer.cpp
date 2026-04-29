//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Timer.h"

namespace gb::core {
    Timer::Timer() = default;

    uint8_t Timer::read(uint16_t address) const {
        if (address == 0xFF04)
            return divider_register;
        if (address == 0xFF05)
            return timer_counter;
        if (address == 0xFF06)
            return timer_modulo;
        if (address == 0xFF07)
            return timer_control;

        return 0xFF;
    }

    void Timer::write(uint16_t address, uint8_t value) {
        if (address == 0xFF04)
            divider_register = value;
        else if (address == 0xFF05)
            timer_counter = value;
        else if (address == 0xFF06)
            timer_modulo = value;
        else if (address == 0xFF07)
            timer_control = value;
    }
}