//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once
#include <cstdint>

namespace gb::core {
    class Joypad {
    public:
        Joypad();

        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);
        void press_button(bool is_dpad, uint8_t button_bit);
        void release_button(bool is_dpad, uint8_t button_bit);

    private:

        /*
        Bit 7 - Not used
        Bit 6 - Not used
        Bit 5 - P15 Select Button Keys      (0=Select)
        Bit 4 - P14 Select Direction Keys   (0=Select)
        Bit 3 - P13 Input Down  or Start    (0=Pressed) (Read Only)
        Bit 2 - P12 Input Up    or Select   (0=Pressed) (Read Only)
        Bit 1 - P11 Input Left  or Button B (0=Pressed) (Read Only)
        Bit 0 - P10 Input Right or Button A (0=Pressed) (Read Only)
        */
        uint8_t action_buttons = 0x0F;      // Lower 4 bits hold A, B, Select, Start
        uint8_t dpad_buttons = 0x0F;        // Lower 4 bits hold Right, Left, Up, Down
        uint8_t joypad_state = 0x3F;        // What the CPU has written to 0xFF00
    };
}
