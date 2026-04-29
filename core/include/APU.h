//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <array>
#include <cstdint>

namespace gb::core {
    class APU {
    public:
        APU();
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

    private:
        std::array<uint8_t, 5> sound_channel1;     // 0xFF10 - 0xFF14: Tone & Sweep
        std::array<uint8_t, 4> sound_channel2;     // 0xFF16 - 0xFF19: Tone
        std::array<uint8_t, 5> sound_channel3;     // 0xFF1A - 0xFF1E: Wave Output
        std::array<uint8_t, 4> sound_channel4;     // 0xFF20 - 0xFF23: Noise
        std::array<uint8_t, 3> sound_control_reg;  // 0xFF24 - 0xFF26
        std::array<uint8_t, 16> wave_pattern_ram;  // 0xFF30 - 0xFF3F
    };
}