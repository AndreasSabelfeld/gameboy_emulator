//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Timer.h"
#include "MMU.h"

namespace gb::core {
    Timer::Timer() = default;

    void Timer::tick(uint8_t cycles) {
        while (cycles >= 4) {
            if (overflow_delay > 0) {
                overflow_delay--;
                if (overflow_delay == 0) {
                    TIMA = TMA;
                    mmu->write(0xFF0F, mmu->read(0xFF0F) | 0x04);
                }
            }

            uint16_t old_clk = SYS_CLK;

            SYS_CLK += 4;
            cycles -= 4;

            bool timer_enabled = (TAC & 0x04) != 0;
            if (!timer_enabled) continue;

            uint16_t bit_mask = 0;
            switch (TAC & 0x03) {
                case 0b00: bit_mask = (1 << 9); break;
                case 0b01: bit_mask = (1 << 3); break;
                case 0b10: bit_mask = (1 << 5); break;
                case 0b11: bit_mask = (1 << 7); break;
            }

            bool old_bit = (old_clk & bit_mask) != 0;
            bool new_bit = (SYS_CLK & bit_mask) != 0;

            if (old_bit && !new_bit) {
                if (TIMA == 0xFF) {
                    TIMA = 0x00;
                    overflow_delay = 1; // Delay the TMA load and interrupt by 1 M-cycle
                } else {
                    TIMA++;
                }
            }
        }
    }

    uint8_t Timer::read_DIV() const {
        return static_cast<uint8_t>(SYS_CLK >> 8);
    }

    void Timer::write_DIV() {
        uint16_t old_clk = SYS_CLK;
        SYS_CLK = 0;

        bool timer_enabled = (TAC & 0x04) != 0;
        if (timer_enabled) {
            uint16_t bit_mask = 0;
            switch (TAC & 0x03) {
                case 0b00: bit_mask = (1 << 9); break;
                case 0b01: bit_mask = (1 << 3); break;
                case 0b10: bit_mask = (1 << 5); break;
                case 0b11: bit_mask = (1 << 7); break;
            }

            // If the bit was 1, and is now 0
            if ((old_clk & bit_mask) != 0) {
                TIMA++;
                if (TIMA == 0x00) {
                    TIMA = TMA;
                    mmu->write(0xFF0F, mmu->read(0xFF0F) | 0x04);
                }
            }
        }
    }

    void Timer::set_mmu(MMU* mmu) {
        this->mmu = mmu;
    };

    uint8_t Timer::read(uint16_t address) const {
        if (address == 0xFF04)
            return read_DIV();
        if (address == 0xFF05)
            return TIMA;
        if (address == 0xFF06)
            return TMA;
        if (address == 0xFF07)
            return TAC | 0xF8;  // The top 5 bits of TAC are physically hardwired to 1

        return 0xFF;
    }

    void Timer::write(uint16_t address, uint8_t value) {
        if (address == 0xFF04)
            write_DIV();
        else if (address == 0xFF05)
            TIMA = value;
        else if (address == 0xFF06)
            TMA = value;
        else if (address == 0xFF07)
            TAC = value | 0xF8; // The top 5 bits of TAC are physically hardwired to 1
    }
}