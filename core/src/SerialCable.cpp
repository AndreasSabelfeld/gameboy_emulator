//
// Created by Andreas Sabelfeld on 29.04.2026.
//

#include "SerialCable.h"
#include <iostream>

namespace gb::core {
    SerialCable::SerialCable() {
        has_passed_test = false;
    }


    std::string serial_buffer;

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
        } else if (address == 0xFF02) {
            serial_transfer_control = value;

            // --- BLARGG TEST ---
            // If Bit 7 (0x80) is 1, and Bit 0 (0x01) is 1,
            // the game is asking to start a transfer using the internal clock.
            if (value == 0x81) {
                std::cout << static_cast<char>(serial_transfer_data) << std::flush;
                serial_buffer += static_cast<char>(serial_transfer_data);
                serial_transfer_control &= 0x7F; // Turn off bit 7

                // todo: signal MMU to trigger the Serial Interrupt here!
            }
            if (!has_passed_test && serial_buffer.find("Passed") != std::string::npos) {
                std::cout << "\nTest ROM passed!";
                has_passed_test = true;
            }
        }
    }
}