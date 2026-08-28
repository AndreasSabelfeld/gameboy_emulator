//
// Created by Andreas Sabelfeld on 24.04.2026.
//
// Audio Processing Unit

#include "APU.h"

namespace gb::core {
    APU::APU() = default;

    void APU::tick(uint8_t cycles) {
        frame_sequencer_timer += cycles;
        if (frame_sequencer_timer >= 8192) {
            frame_sequencer_timer -= 8192;
            clock_frame_sequencer();
        }

        // Step Channel 1's Frequency Timer
        if (ch1_enabled) {
            ch1_timer -= cycles;
            if (ch1_timer <= 0) {
                // Calculate frequency from registers (NR13 and lower 3 bits of NR14)
                uint16_t frequency = sound_channel1[3] | ((sound_channel1[4] & 0x07) << 8);
                ch1_timer += (2048 - frequency) * 4;

                // Advance the square wave duty step (0-7)
                ch1_duty_step = (ch1_duty_step + 1) % 8;
            }
        }

        if (ch2_enabled) {
            ch2_timer -= cycles;
            if (ch2_timer <= 0) {
                uint16_t frequency = sound_channel2[2] | ((sound_channel2[3] & 0x07) << 8);
                ch2_timer += (2048 - frequency) * 4;

                ch2_duty_step = (ch2_duty_step + 1) % 8;
            }
        }

        if (ch3_enabled) {
            ch3_timer -= cycles;
            if (ch3_timer <= 0) {
                uint16_t frequency = sound_channel3[3] | ((sound_channel3[4] & 0x07) << 8);
                ch3_timer += (2048 - frequency) * 2;

                // Advance through the 32 wave samples
                ch3_wave_position = (ch3_wave_position + 1) % 32;
            }
        }

        if (ch4_enabled) {
            ch4_timer -= cycles;
            if (ch4_timer <= 0) {
                // Change sound_channel4[3] to sound_channel4[2]
                uint8_t divisor_code = sound_channel4[2] & 0x07;
                uint8_t shift_clock = sound_channel4[2] >> 4;

                int divisor = (divisor_code == 0) ? 8 : (divisor_code * 16);
                ch4_timer += divisor << shift_clock;

                uint8_t xor_result = (lfsr & 0x01) ^ ((lfsr >> 1) & 0x01);
                lfsr >>= 1;
                lfsr |= (xor_result << 14);

                // Change sound_channel4[3] to sound_channel4[2] here too
                if (sound_channel4[2] & 0x08) {
                    lfsr &= ~(1 << 6);
                    lfsr |= (xor_result << 6);
                }
            }
        }

        // resample for the Output Buffer (44100 Hz = Every ~95 CPU cycles)
        downsample_timer += cycles;
        if (downsample_timer >= 95) {
            downsample_timer -= 95;
            generate_sample();
        }
    }

    void APU::clock_frame_sequencer() {
        frame_sequencer_step = (frame_sequencer_step + 1) % 8;

        // Clock Length Counters (Steps 0, 2, 4, 6)
        if (frame_sequencer_step % 2 == 0) {
            if (ch1_length_counter > 0 && (sound_channel1[4] & 0x40)) {
                if (--ch1_length_counter == 0) ch1_enabled = false;
            }
            if (ch2_length_counter > 0 && (sound_channel2[3] & 0x40)) {
                if (--ch2_length_counter == 0) ch2_enabled = false;
            }
            if (ch3_length_counter > 0 && (sound_channel3[4] & 0x40)) {
                if (--ch3_length_counter == 0) ch3_enabled = false;
            }
            if (ch4_length_counter > 0 && (sound_channel4[3] & 0x40)) {
                if (--ch4_length_counter == 0) ch4_enabled = false;
            }
        }

        // Clock Frequency Sweep (Steps 2, 6) for Channel 1
        if (frame_sequencer_step == 2 || frame_sequencer_step == 6) {
            if (ch1_sweep_timer > 0) {
                ch1_sweep_timer--;
                if (ch1_sweep_timer == 0) {
                    uint8_t sweep_period = (sound_channel1[0] >> 4) & 0x07;
                    ch1_sweep_timer = sweep_period > 0 ? sweep_period : 8;

                    uint8_t sweep_shift = sound_channel1[0] & 0x07;
                    if (sweep_period > 0 && sweep_shift > 0) {
                        uint16_t offset = ch1_shadow_frequency >> sweep_shift;
                        bool subtract = (sound_channel1[0] & 0x08) != 0;
                        uint16_t new_frequency = subtract ? (ch1_shadow_frequency - offset) : (ch1_shadow_frequency + offset);

                        if (new_frequency > 2047) {
                            ch1_enabled = false;
                        } else {
                            ch1_shadow_frequency = new_frequency;
                            sound_channel1[3] = new_frequency & 0xFF;
                            sound_channel1[4] = (sound_channel1[4] & 0xF8) | (new_frequency >> 8);
                        }
                    }
                }
            }
        }

        // Clock Volume Envelopes (Step 7)
        if (frame_sequencer_step == 7) {
            // Channel 1 Envelope
            if (ch1_envelope_timer > 0) {
                if (--ch1_envelope_timer == 0) {
                    uint8_t envelope_period = sound_channel1[2] & 0x07;
                    if (envelope_period > 0) {
                        ch1_envelope_timer = envelope_period;
                        bool envelope_increase = (sound_channel1[2] & 0x08) != 0;
                        if (envelope_increase && ch1_current_volume < 15) ch1_current_volume++;
                        else if (!envelope_increase && ch1_current_volume > 0) ch1_current_volume--;
                    }
                }
            }
            // Channel 2 Envelope
            if (ch2_envelope_timer > 0) {
                if (--ch2_envelope_timer == 0) {
                    uint8_t envelope_period = sound_channel2[1] & 0x07;
                    if (envelope_period > 0) {
                        ch2_envelope_timer = envelope_period;
                        bool envelope_increase = (sound_channel2[2] & 0x08) != 0;
                        if (envelope_increase && ch2_current_volume < 15) ch2_current_volume++;
                        else if (!envelope_increase && ch2_current_volume > 0) ch2_current_volume--;
                    }
                }
            }
            // Channel 4 Envelope
            if (ch4_envelope_timer > 0) {
                if (--ch4_envelope_timer == 0) {
                    uint8_t envelope_period = sound_channel4[1] & 0x07; // Note: Ch4 volume is in NR42 (index 1)
                    if (envelope_period > 0) {
                        ch4_envelope_timer = envelope_period;
                        bool envelope_increase = (sound_channel4[1] & 0x08) != 0;
                        if (envelope_increase && ch4_current_volume < 15) ch4_current_volume++;
                        else if (!envelope_increase && ch4_current_volume > 0) ch4_current_volume--;
                    }
                }
            }
        }
    }

    void APU::generate_sample() {
        float ch1_output = 0.0f;
        if (ch1_enabled) {
            // The 4 duty cycles (12.5%, 25%, 50%, 75%)
            const uint8_t duty_table[4][8] = {
                {0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,1},
                {1,0,0,0,0,1,1,1},
                {0,1,1,1,1,1,1,0}
            };

            uint8_t duty_pattern = sound_channel1[1] >> 6;
            uint8_t amplitude = duty_table[duty_pattern][ch1_duty_step];

            // Apply the current volume envelope
            if (amplitude) {
                // Normalize 0-15 volume to a 0.0 - 1.0 float, scaled down to avoid clipping
                ch1_output = (ch1_current_volume / 15.0f) * 0.2f;
            }
        }

        float ch2_output = 0.0f;
        if (ch2_enabled) {
            // The 4 duty cycles (12.5%, 25%, 50%, 75%)
            const uint8_t duty_table[4][8] = {
                {0,0,0,0,0,0,0,1},
                {1,0,0,0,0,0,0,1},
                {1,0,0,0,0,1,1,1},
                {0,1,1,1,1,1,1,0}
            };

            uint8_t duty_pattern = sound_channel2[0] >> 6;
            uint8_t amplitude = duty_table[duty_pattern][ch2_duty_step];

            // Apply the current volume envelope
            if (amplitude) {
                // Normalize 0-15 volume to a 0.0 - 1.0 float, scaled down to avoid clipping
                ch2_output = (ch2_current_volume / 15.0f) * 0.2f;
            }
        }

        float ch3_output = 0.0f;
        if (ch3_enabled) {
            // 16 bytes = 32 samples (2 per byte)
            uint8_t wave_byte = wave_pattern_ram[ch3_wave_position / 2];

            // If even index, grab high 4 bits. If odd, grab low 4 bits.
            uint8_t sample = (ch3_wave_position % 2 == 0) ? (wave_byte >> 4) : (wave_byte & 0x0F);

            // Volume shift (0=Mute, 1=100%, 2=50%, 3=25%)
            uint8_t volume_shift = (sound_channel3[2] >> 5) & 0x03;
            if (volume_shift > 0) {
                sample >>= (volume_shift - 1);
                ch3_output = (sample / 15.0f) * 0.2f;
            }
        }

        float ch4_output = 0.0f;
        if (ch4_enabled) {
            // Bit 0 of the LFSR being 0 means HIGH amplitude (inverted)
            if ((lfsr & 0x01) == 0) {
                ch4_output = (ch4_current_volume / 15.0f) * 0.2f;
            }
        }

        float total = ch1_output + ch2_output + ch3_output + ch4_output;

        // Output to both Left and Right channels (Stereo)
        // Note: Real hardware reads 0xFF25 for L/R panning, but we will output center for now
        audio_buffer.push_back(total); // Left
        audio_buffer.push_back(total); // Right
    }

    std::vector<float> APU::get_audio_buffer() {
        return audio_buffer;
    }

    void APU::clear_audio_buffer() {
        audio_buffer.clear();
    }

    void APU::trigger_channel_1() {
        ch1_enabled = true;
        if (ch1_length_counter == 0) ch1_length_counter = 64;

        // Reload volume and envelope timer
        ch1_current_volume = sound_channel1[2] >> 4;
        ch1_envelope_timer = sound_channel1[2] & 0x07;

        // Reload frequency timer
        uint16_t frequency = sound_channel1[3] | ((sound_channel1[4] & 0x07) << 8);
        ch1_timer = (2048 - frequency) * 4;

        // --- Sweep specific resets for Channel 1 ---
        ch1_shadow_frequency = frequency;
        uint8_t sweep_period = (sound_channel1[0] >> 4) & 0x07;
        ch1_sweep_timer = sweep_period > 0 ? sweep_period : 8;
    }

    void APU::trigger_channel_2() {
        ch2_enabled = true;
        if (ch2_length_counter == 0) ch2_length_counter = 64;

        // Reload volume and envelope timer
        ch2_current_volume = sound_channel2[1] >> 4;
        ch2_envelope_timer = sound_channel2[2] & 0x07;

        // Reload frequency timer
        uint16_t frequency = sound_channel2[2] | ((sound_channel2[3] & 0x07) << 8);
        ch2_timer = (2048 - frequency) * 4;
    }

    void APU::trigger_channel_3() {
        ch3_enabled = true;
        if (ch3_length_counter == 0) ch3_length_counter = 256;

        uint16_t frequency = sound_channel3[3] | ((sound_channel3[4] & 0x07) << 8);
        ch3_timer = (2048 - frequency) * 2;
        ch3_wave_position = 0; // Restart wave from the beginning
    }

    void APU::trigger_channel_4() {
        ch4_enabled = true;
        if (ch4_length_counter == 0) ch4_length_counter = 64;

        // Reload volume and envelope timer (NR42 is index 1)
        ch4_current_volume = sound_channel4[1] >> 4;
        ch4_envelope_timer = sound_channel4[1] & 0x07;

        // Reset the LFSR to all 1s
        lfsr = 0x7FFF;

        uint8_t divisor_code = sound_channel4[2] & 0x07;
        uint8_t shift_clock = sound_channel4[2] >> 4;
        int divisor = (divisor_code == 0) ? 8 : (divisor_code * 16);
        ch4_timer = divisor << shift_clock;
    }

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
            // If writing to NR11 (Length Load), reset the length counter
            if (address == 0xFF11) {
                ch1_length_counter = 64 - (value & 0x3F);
            }
            // If writing to NR14, check the trigger bit (Bit 7)
            if (address == 0xFF14 && (value & 0x80)) {
                trigger_channel_1();
            }
        } if (address >= 0xFF16 && address <= 0xFF19) {
            sound_channel2[address-0xFF16] = value;
            // If writing to NR21 (Length Load), reset the length counter
            if (address == 0xFF16) {
                ch2_length_counter = 64 - (value & 0x3F);
            }
            // If writing to NR24, check the trigger bit (Bit 7)
            if (address == 0xFF19 && (value & 0x80)) {
                trigger_channel_2();
            }
        } if (address >= 0xFF1A && address <= 0xFF1E) {
            sound_channel3[address-0xFF1A] = value;
            // NR31 (0xFF1B): Length load (Max 256 for Ch3)
            if (address == 0xFF1B) {
                ch3_length_counter = 256 - value;
            }
            // NR34 (0xFF1E): Trigger
            if (address == 0xFF1E && (value & 0x80)) {
                trigger_channel_3();
            }
        } if (address >= 0xFF20 && address <= 0xFF23) {
            sound_channel4[address-0xFF20] = value;
            // NR41 (0xFF20): Length load
            if (address == 0xFF20) {
                ch4_length_counter = 64 - (value & 0x3F);
            }
            // NR44 (0xFF23): Trigger
            if (address == 0xFF23 && (value & 0x80)) {
                trigger_channel_4();
            }
        } if (address >= 0xFF24 && address <= 0xFF26) {
            sound_control_reg[address-0xFF24] = value;
        } if (address >= 0xFF30 && address <= 0xFF3F) {
            wave_pattern_ram[address-0xFF30] = value;
        }
    }
}
