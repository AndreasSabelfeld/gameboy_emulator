//
// Created by Andreas Sabelfeld on 29.04.2026.
//

#include "SerialCable.h"
#include <iostream>

namespace gb::core {
    SerialCable::SerialCable() = default;

    uint8_t SerialCable::read(uint16_t address) const {
        if (address == 0xFF01) {
            return serial_transfer_data;
        } if (address == 0xFF02) {
            return serial_transfer_control | 0x7E;      // guarantees that the unused bits are floating high
        }

        return 0xFF;
    }

    void SerialCable::write(uint16_t address, uint8_t value) {
        if (address == 0xFF01) {
            serial_transfer_data = value;
        } if (address == 0xFF02) {
            serial_transfer_control = value;

            // --- THE BLARGG TEST HACK ---
            // If Bit 7 (0x80) is 1, and Bit 0 (0x01) is 1,
            // the game is asking to start a transfer using the internal clock.
            if (value == 0x81) {
                std::cout << (char)serial_transfer_data << std::flush;
                serial_transfer_control &= 0x7F; // Turn off bit 7

                // todo: signal MMU to trigger the Serial Interrupt here!
            }
        }
    }
}