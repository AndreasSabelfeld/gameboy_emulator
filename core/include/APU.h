//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <array>
#include <vector>
#include <cstdint>

namespace gb::core {
    class APU {
    public:
        APU();
        uint8_t read(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

        void tick(uint8_t cycles);
        std::vector<float> get_audio_buffer();
        void clear_audio_buffer();

    private:
        int audio_cycles = 0;
        // Output Buffer for SDL2
        std::vector<float> audio_buffer;
        int downsample_timer = 0;

        int frame_sequencer_timer = 0;
        int frame_sequencer_step = 0;

        // --- Channel 1 ---
        bool ch1_enabled = false;
        int ch1_timer = 0;
        uint8_t ch1_duty_step = 0;
        uint8_t ch1_current_volume = 0;
        uint16_t ch1_shadow_frequency = 0;
        int ch1_envelope_timer = 0;
        int ch1_length_counter = 0;

        // --- Channel 2 ---
        bool ch2_enabled = false;
        int ch2_timer = 0;
        int ch1_sweep_timer = 0;
        uint8_t ch2_duty_step = 0;
        uint8_t ch2_current_volume = 0;
        int ch2_envelope_timer = 0;
        int ch2_length_counter = 0;

        // --- Channel 3 ---
        bool ch3_enabled = false;
        int ch3_timer = 0;
        int ch3_length_counter = 0;
        uint8_t ch3_wave_position = 0; // Goes from 0 to 31

        // --- Channel 4 ---
        bool ch4_enabled = false;
        int ch4_timer = 0;
        int ch4_length_counter = 0;
        uint8_t ch4_current_volume = 0;
        int ch4_envelope_timer = 0;
        uint16_t lfsr = 0x7FFF; // Shift register starts all 1s

        std::array<uint8_t, 5> sound_channel1;     // 0xFF10 - 0xFF14: Tone & Sweep
        std::array<uint8_t, 4> sound_channel2;     // 0xFF16 - 0xFF19: Tone
        std::array<uint8_t, 5> sound_channel3;     // 0xFF1A - 0xFF1E: Wave Output
        std::array<uint8_t, 4> sound_channel4;     // 0xFF20 - 0xFF23: Noise
        std::array<uint8_t, 3> sound_control_reg;  // 0xFF24 - 0xFF26
        std::array<uint8_t, 16> wave_pattern_ram;  // 0xFF30 - 0xFF3F

        void clock_frame_sequencer();
        void generate_sample();

        void trigger_channel_1();
        void trigger_channel_2();
        void trigger_channel_3();
        void trigger_channel_4();
    };
}