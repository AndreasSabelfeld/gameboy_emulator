//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Joypad.h"

namespace gb::core {
    Joypad::Joypad() = default;

    uint8_t Joypad::read(uint16_t address) const {
        uint8_t output = 0xCF;              // buttons unpressed
        if (address != 0xFF00) {
            return output;
        }

        if ((joypad_state & 0x20) == 0) {   // If Bit 5 is 0, the CPU wants to read Action Buttons
            output &= action_buttons;
        }
        if ((joypad_state & 0x10) == 0) {   // If Bit 4 is 0, the CPU wants to read D-Pad
            output &= dpad_buttons;
        }

        return output;
    }

    void Joypad::write(uint16_t address, uint8_t value) {
        if (address != 0xFF00) {
            return;
        }

        joypad_state = (joypad_state & 0xCF) | (value & 0x30);  // only changes bits 4 and 5, other bits are masked
    }
}