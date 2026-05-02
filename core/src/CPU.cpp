//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "CPU.h"

#include <iostream>
#include <ostream>

#include "MMU.h"

namespace gb::core {
    CPU::CPU(MMU* mmu) {
        this->mmu = mmu;

        init_opcodes();
    };

    uint8_t CPU::step() {
        if (IME && (mmu->read(0xFFFF) & mmu->read(0xFF0F))) {
            return handle_interrupts();
        }

        uint8_t opcode = fetch_byte();
        Instruction& instr = opcode_table[opcode];
        uint8_t cycles = execute(instr, opcode);

        if (EI_delay == 0) {
            IME = true;
            EI_delay = -1;
        }

        if (EI_delay > 0) EI_delay--;
        return cycles;
    }

    uint8_t CPU::handle_interrupts() {
        // todo
    }

    uint8_t CPU::fetch_byte() {
        return mmu->read(PC++);
    }

    uint16_t CPU::fetch_word() {
        uint16_t lo = fetch_byte();
        uint16_t hi = fetch_byte();

        return static_cast<uint16_t>((hi << 8) | lo);
    }

    void CPU::set_flag_z(bool value) {
        if (value) F |= (1 << 7);
        else       F &= ~(1 << 7);
    }

    bool CPU::get_flag_z() const {
        return (F & (1 << 7)) > 0;
    }

    void CPU::set_flag_n(bool value) {
        if (value) F |= (1 << 6);
        else       F &= ~(1 << 6);
    }

    bool CPU::get_flag_n() const {
        return (F & (1 << 6)) > 0;
    }

    void CPU::set_flag_h(bool value) {
        if (value) F |= (1 << 5);
        else       F &= ~(1 << 5);
    }

    bool CPU::get_flag_h() const {
        return (F & (1 << 5)) > 0;
    }

    void CPU::set_flag_c(bool value) {
        if (value) F |= (1 << 4);
        else       F &= ~(1 << 4);
    }

    bool CPU::get_flag_c() const {
        return (F & (1 << 4)) > 0;
    }
}