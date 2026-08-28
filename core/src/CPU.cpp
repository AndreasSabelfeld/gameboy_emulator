//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "CPU.h"

#include <iostream>
#include <ostream>

#include "MMU.h"
#include "PPU.h"
#include "Timer.h"
#include "APU.h"

namespace gb::core {
    CPU::CPU(MMU* mmu, Timer* timer, PPU* ppu, APU* apu) {
        this->mmu = mmu;
        this->timer = timer;
        this->ppu = ppu;
        this->apu = apu;

        init_opcodes();
#ifdef SKIP_BOOT_ROM
        // skip boot-up sequence
        this->mmu->boot_rom_active = false;
#endif
        reset();
    };

    void CPU::tick() {
        timer->tick(4);
        ppu->tick(4);
        apu->tick(4);
        frame_cycles += 4;
    }

    void CPU::step() {
        uint8_t req = mmu->read(0xFF0F);            // IF
        uint8_t en = mmu->read(0xFFFF);             // IE
        uint8_t pending_interrupts = req & en & 0x1F;      // IF & IE is non-zero

        if (is_halted) {
            if (pending_interrupts > 0) {
                is_halted = false;
            } else {
                tick();
                return;
            }
        }

        if (IME && pending_interrupts > 0) {
            handle_interrupts();
            return;
        }

        uint8_t opcode = fetch_byte();                     // automatically ticks 4
        Instruction& instr = opcode_table[opcode];
        execute(instr, opcode);

        if (EI_delay == 0) {
            IME = true;
            EI_delay = -1;
        }

        if (EI_delay > 0) EI_delay--;
    }

    void CPU::handle_interrupts() {
        if (!IME) return;

        uint8_t req = mmu->read(0xFF0F); // IF register (Requested)
        uint8_t en = mmu->read(0xFFFF);  // IE register (Enabled)

        // Check bits 0-4 in priority order
        for (int i = 0; i <= 4; i++) {
            if ((req & (1 << i)) && (en & (1 << i))) {
                IME = false;
                // acknowledge the interrupt by clearing its specific bit in IF
                mmu->write(0xFF0F, req & ~(1 << i));

                // hardware interrupt dispatch delay
                tick();
                tick();

                // push current Program Counter to the stack
                push_16bit(PC);

                // jump to the appropriate hardware vector (ROM handles the interrupt)
                switch (i) {
                    case 0: PC = 0x0040; break; // Bit 0: VBlank
                    case 1: PC = 0x0048; break; // Bit 1: LCD STAT
                    case 2: PC = 0x0050; break; // Bit 2: Timer
                    case 3: PC = 0x0058; break; // Bit 3: Serial
                    case 4: PC = 0x0060; break; // Bit 4: Joypad
                }

                return;
            }
        }
    }

    void CPU::reset() {
        frame_cycles = 0;
        if (mmu->boot_rom_active) {
            AF = { .word = 0x0000 };
            BC = { .word = 0x0000 };
            DE = { .word = 0x0000 };
            HL = { .word = 0x0000 };

            PC = 0x0000;            // program counter
            SP = 0x0000;            // stack pointer
        } else {
            AF = { .word = 0x01B0 };
            BC = { .word = 0x0013 };
            DE = { .word = 0x00D8 };
            HL = { .word = 0x014D };

            PC = 0x0100;            // program counter
            SP = 0xFFFE;            // stack pointer
        }

        IME = false;            // Interrupt Master Enable
        EI_delay = -1;          // -1: not scheduled, 0 signal EI, >0: delay
        is_halted = false;
    }

    uint8_t CPU::read_byte(uint16_t address) {
        tick(); // Time passes during the read
        return mmu->read(address);
    }

    void CPU::write_byte(uint16_t address, uint8_t value) {
        tick(); // Time passes during the write
        mmu->write(address, value);
    }

    uint8_t CPU::fetch_byte() {
        return read_byte(PC++);
    }

    uint16_t CPU::fetch_word() {
        uint16_t lo = fetch_byte();
        uint16_t hi = fetch_byte();
        return static_cast<uint16_t>((hi << 8) | lo);
    }

    uint16_t CPU::pop_16bit() {
        uint8_t lower = read_byte(SP++);
        uint8_t upper = read_byte(SP++);
        return static_cast<uint16_t>((upper << 8) | lower);
    }

    void CPU::push_16bit(uint16_t value) {
        tick(); // Internal CPU delay before writing to stack (1 M-cycle)
        write_byte(--SP, static_cast<uint8_t>(value >> 8));
        write_byte(--SP, static_cast<uint8_t>(value & 0xFF));
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
