//
// Created by Andreas Sabelfeld on 24.04.2026.
//
// Audio Processing Unit

#include "APU.h"

namespace gb::core {
    APU::APU() = default;

    uint8_t APU::read(uint16_t address) const {
        if (address >= 0xFF10 && address <= 0xFF14) {
            return sound_channel1[address-0xFF10];
        } if (address >= 0xFF16 && address <= 0xFF19) {
            return sound_channel2[address-0xFF16];
        } if (address >= 0xFF1A && address <= 0xFF1E) {
            return sound_channel3[address-0xFF1A];
        } if (address >= 0xFF20 && address <= 0xFF23) {
            return sound_channel4[address-0xFF20];
        } if (address >= 0xFF24 && address <= 0xFF26) {
            return sound_control_reg[address-0xFF24];
        } if (address >= 0xFF30 && address <= 0xFF3F) {
            return wave_pattern_ram[address-0xFF30];
        }

        return 0xFF;
    }

    void APU::write(uint16_t address, uint8_t value) {
        if (address >= 0xFF10 && address <= 0xFF14) {
            sound_channel1[address-0xFF10] = value;
        } if (address >= 0xFF16 && address <= 0xFF19) {
            sound_channel2[address-0xFF16] = value;
        } if (address >= 0xFF1A && address <= 0xFF1E) {
            sound_channel3[address-0xFF1A] = value;
        } if (address >= 0xFF20 && address <= 0xFF23) {
            sound_channel4[address-0xFF20] = value;
        } if (address >= 0xFF24 && address <= 0xFF26) {
            sound_control_reg[address-0xFF24] = value;
        } if (address >= 0xFF30 && address <= 0xFF3F) {
            wave_pattern_ram[address-0xFF30] = value;
        }
    }
}
