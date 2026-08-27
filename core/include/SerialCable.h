//
// Created by Andreas Sabelfeld on 29.04.2026.
//

#pragma once
#include <cstdint>

namespace gb::core {
    class SerialCable {
    public:
        SerialCable();

        bool has_passed_test = false;

        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

    private:
        uint8_t serial_transfer_data = 0x00;       // 0xFF01: 8 Bits of data to be read/written

        /*
        Bit 7 - Transfer Start Flag (0=No Transfer, 1=Start)
        Bit 1 - Clock Speed (0=Normal, 1=Fast) ** CGB Mode Only **
        Bit 0 - Shift Clock (0=External Clock, 1=Internal Clock)
        */
        uint8_t serial_transfer_control = 0x7E;    // 0xFF02
    };
}
