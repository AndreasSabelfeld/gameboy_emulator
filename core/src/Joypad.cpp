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

    void Joypad::press_button(bool is_dpad, uint8_t button_bit) {
        bool previously_unpressed = false;

        if (is_dpad) {
            previously_unpressed = (dpad_buttons & (1 << button_bit)) != 0;
            dpad_buttons &= ~(1 << button_bit); // 0 = pressed
        } else {
            previously_unpressed = (action_buttons & (1 << button_bit)) != 0;
            action_buttons &= ~(1 << button_bit); // 0 = pressed
        }

        // If the button changed from unpressed to pressed, fire the Joypad Interrupt (Bit 4)
        if (previously_unpressed && mmu) {
            mmu->write(0xFF0F, mmu->read(0xFF0F) | 0x10);
        }
    }

    void Joypad::release_button(bool is_dpad, uint8_t button_bit) {
        if (is_dpad) {
            dpad_buttons |= (1 << button_bit);  // 1 = unpressed
        } else {
            action_buttons |= (1 << button_bit); // 1 = unpressed
        }
    }

    void Joypad::set_mmu(MMU* mmu) {
        this->mmu = mmu;
    }
}