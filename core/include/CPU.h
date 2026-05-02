//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <cstdint>
#include <array>
#include "MMU.h"


namespace gb::core {
    struct Instruction {
        const char* mnemonic;       // name of instruction
        uint8_t length;             // how many bytes
    };

    union Register {
        uint16_t word;
        struct {
            uint8_t low;
            uint8_t high;
        };
    };

    class CPU {
    public:
        CPU(MMU* mmu);

        uint8_t step();
        uint8_t execute(const Instruction& inst, uint8_t opcode);
        void reset();

    private:
        MMU* mmu;

        Register AF = { .word = 0x01B0 };
        Register BC = { .word = 0x0013 };
        Register DE = { .word = 0x00D8 };
        Register HL = { .word = 0x014D };

        // Aliases:
        uint8_t& A = AF.high;
        uint8_t& F = AF.low;
        // F layout:
        // Bit 7:       (Z) Zero Flag
        // Bit 6:       (N) Subtract Flag
        // Bit 5:       (H) Half-Carry Flag
        // Bit 4:       (C) Carry Flag
        // Bits 3-0 unused

        uint8_t& B = BC.high;
        uint8_t& C = BC.low;

        uint8_t& D = DE.high;
        uint8_t& E = DE.low;

        uint8_t& H = HL.high;
        uint8_t& L = HL.low;

        uint16_t PC = 0x0100;        // program counter TODO: initialize at 0x0000 to emulate boot-up sequence once ready
        uint16_t SP = 0xFFFE;        // stack pointer

        bool IME = false;            // Interrupt Master Enable
        int EI_delay = -1;           // -1: not scheduled, 0 signal EI, >0: delay

        std::array<Instruction, 256> opcode_table;
        std::array<Instruction, 256> cb_opcode_table;

        void init_opcodes();

        uint8_t fetch_byte();
        uint16_t fetch_word();

        void set_flag_z(bool value);
        void set_flag_n(bool value);
        void set_flag_h(bool value);
        void set_flag_c(bool value);

        bool get_flag_z() const;
        bool get_flag_n() const;
        bool get_flag_h() const;
        bool get_flag_c() const;

        uint8_t handle_interrupts();
        uint8_t execute_cb();

        // =========================================================================
        // Helper Functions
        // =========================================================================
        uint8_t ADD(uint8_t& to, uint8_t value);
        uint8_t ADD_HL(uint16_t value);
        uint8_t ADC(uint8_t& to, uint8_t value);
        uint8_t SUB(uint8_t& to, uint8_t value);
        uint8_t SBC(uint8_t& to, uint8_t value);

        uint8_t AND_A(uint8_t value);
        uint8_t XOR_A(uint8_t value);
        uint8_t OR_A(uint8_t value);
        uint8_t CP_A(uint8_t value);

        uint8_t INC(uint8_t& to);
        uint8_t DEC(uint8_t& to);

        uint8_t RLC(uint8_t& to);
        uint8_t RRC(uint8_t& to);
        uint8_t RL(uint8_t& to);
        uint8_t RR(uint8_t& to);
        uint8_t SLA(uint8_t& to);
        uint8_t SRA(uint8_t& to);
        uint8_t SRL(uint8_t& to);
        uint8_t SWAP(uint8_t& to);

        uint8_t BIT(uint8_t bit, uint8_t& reg);
        uint8_t RES(uint8_t bit, uint8_t& reg);
        uint8_t SET(uint8_t bit, uint8_t &reg);

        uint16_t pop_16bit();
        void push_16bit(uint16_t value);
        inline uint16_t read_16bit(uint16_t address);

        // =========================================================================
        // STANDARD OPCODES (0x00 - 0xFF)
        // =========================================================================

        // the returned integer represents the delta of the

        // --- Row 0x0_ ---
        uint8_t instr_NOP();               uint8_t instr_LD_BC_n16();         uint8_t instr_LD_mBC_A();          uint8_t instr_INC_BC();
        uint8_t instr_INC_B();             uint8_t instr_DEC_B();             uint8_t instr_LD_B_n8();           uint8_t instr_RLCA();
        uint8_t instr_LD_mn16_SP();        uint8_t instr_ADD_HL_BC();         uint8_t instr_LD_A_mBC();          uint8_t instr_DEC_BC();
        uint8_t instr_INC_C();             uint8_t instr_DEC_C();             uint8_t instr_LD_C_n8();           uint8_t instr_RRCA();

        // --- Row 0x1_ ---
        uint8_t instr_STOP();              uint8_t instr_LD_DE_n16();         uint8_t instr_LD_mDE_A();          uint8_t instr_INC_DE();
        uint8_t instr_INC_D();             uint8_t instr_DEC_D();             uint8_t instr_LD_D_n8();           uint8_t instr_RLA();
        uint8_t instr_JR_n8();             uint8_t instr_ADD_HL_DE();         uint8_t instr_LD_A_mDE();          uint8_t instr_DEC_DE();
        uint8_t instr_INC_E();             uint8_t instr_DEC_E();             uint8_t instr_LD_E_n8();           uint8_t instr_RRA();

        // --- Row 0x2_ ---
        uint8_t instr_JR_NZ_n8();          uint8_t instr_LD_HL_n16();         uint8_t instr_LD_mHL_plus_A();     uint8_t instr_INC_HL();
        uint8_t instr_INC_H();             uint8_t instr_DEC_H();             uint8_t instr_LD_H_n8();           uint8_t instr_DAA();
        uint8_t instr_JR_Z_n8();           uint8_t instr_ADD_HL_HL();         uint8_t instr_LD_A_mHL_plus();     uint8_t instr_DEC_HL();
        uint8_t instr_INC_L();             uint8_t instr_DEC_L();             uint8_t instr_LD_L_n8();           uint8_t instr_CPL();

        // --- Row 0x3_ ---
        uint8_t instr_JR_NC_n8();          uint8_t instr_LD_SP_n16();         uint8_t instr_LD_mHL_minus_A();    uint8_t instr_INC_SP();
        uint8_t instr_INC_mHL();           uint8_t instr_DEC_mHL();           uint8_t instr_LD_mHL_n8();         uint8_t instr_SCF();
        uint8_t instr_JR_C_n8();           uint8_t instr_ADD_HL_SP();         uint8_t instr_LD_A_mHL_minus();    uint8_t instr_DEC_SP();
        uint8_t instr_INC_A();             uint8_t instr_DEC_A();             uint8_t instr_LD_A_n8();           uint8_t instr_CCF();

        // --- Row 0x4_ ---
        uint8_t instr_LD_B_B();            uint8_t instr_LD_B_C();            uint8_t instr_LD_B_D();            uint8_t instr_LD_B_E();
        uint8_t instr_LD_B_H();            uint8_t instr_LD_B_L();            uint8_t instr_LD_B_mHL();          uint8_t instr_LD_B_A();
        uint8_t instr_LD_C_B();            uint8_t instr_LD_C_C();            uint8_t instr_LD_C_D();            uint8_t instr_LD_C_E();
        uint8_t instr_LD_C_H();            uint8_t instr_LD_C_L();            uint8_t instr_LD_C_mHL();          uint8_t instr_LD_C_A();

        // --- Row 0x5_ ---
        uint8_t instr_LD_D_B();            uint8_t instr_LD_D_C();            uint8_t instr_LD_D_D();            uint8_t instr_LD_D_E();
        uint8_t instr_LD_D_H();            uint8_t instr_LD_D_L();            uint8_t instr_LD_D_mHL();          uint8_t instr_LD_D_A();
        uint8_t instr_LD_E_B();            uint8_t instr_LD_E_C();            uint8_t instr_LD_E_D();            uint8_t instr_LD_E_E();
        uint8_t instr_LD_E_H();            uint8_t instr_LD_E_L();            uint8_t instr_LD_E_mHL();          uint8_t instr_LD_E_A();

        // --- Row 0x6_ ---
        uint8_t instr_LD_H_B();            uint8_t instr_LD_H_C();            uint8_t instr_LD_H_D();            uint8_t instr_LD_H_E();
        uint8_t instr_LD_H_H();            uint8_t instr_LD_H_L();            uint8_t instr_LD_H_mHL();          uint8_t instr_LD_H_A();
        uint8_t instr_LD_L_B();            uint8_t instr_LD_L_C();            uint8_t instr_LD_L_D();            uint8_t instr_LD_L_E();
        uint8_t instr_LD_L_H();            uint8_t instr_LD_L_L();            uint8_t instr_LD_L_mHL();          uint8_t instr_LD_L_A();

        // --- Row 0x7_ ---
        uint8_t instr_LD_mHL_B();          uint8_t instr_LD_mHL_C();          uint8_t instr_LD_mHL_D();          uint8_t instr_LD_mHL_E();
        uint8_t instr_LD_mHL_H();          uint8_t instr_LD_mHL_L();          uint8_t instr_HALT();              uint8_t instr_LD_mHL_A();
        uint8_t instr_LD_A_B();            uint8_t instr_LD_A_C();            uint8_t instr_LD_A_D();            uint8_t instr_LD_A_E();
        uint8_t instr_LD_A_H();            uint8_t instr_LD_A_L();            uint8_t instr_LD_A_mHL();          uint8_t instr_LD_A_A();

        // --- Row 0x8_ ---
        uint8_t instr_ADD_A_B();           uint8_t instr_ADD_A_C();           uint8_t instr_ADD_A_D();       uint8_t instr_ADD_A_E();
        uint8_t instr_ADD_A_H();           uint8_t instr_ADD_A_L();           uint8_t instr_ADD_A_mHL();     uint8_t instr_ADD_A_A();
        uint8_t instr_ADC_A_B();           uint8_t instr_ADC_A_C();           uint8_t instr_ADC_A_D();       uint8_t instr_ADC_A_E();
        uint8_t instr_ADC_A_H();           uint8_t instr_ADC_A_L();           uint8_t instr_ADC_A_mHL();     uint8_t instr_ADC_A_A();

        // --- Row 0x9_ ---
        uint8_t instr_SUB_A_B();             uint8_t instr_SUB_A_C();             uint8_t instr_SUB_A_D();         uint8_t instr_SUB_A_E();
        uint8_t instr_SUB_A_H();             uint8_t instr_SUB_A_L();             uint8_t instr_SUB_A_mHL();       uint8_t instr_SUB_A_A();
        uint8_t instr_SBC_A_B();           uint8_t instr_SBC_A_C();           uint8_t instr_SBC_A_D();       uint8_t instr_SBC_A_E();
        uint8_t instr_SBC_A_H();           uint8_t instr_SBC_A_L();           uint8_t instr_SBC_A_mHL();     uint8_t instr_SBC_A_A();

        // --- Row 0xA_ ---
        uint8_t instr_AND_A_B();             uint8_t instr_AND_A_C();             uint8_t instr_AND_A_D();         uint8_t instr_AND_A_E();
        uint8_t instr_AND_A_H();             uint8_t instr_AND_A_L();             uint8_t instr_AND_A_mHL();       uint8_t instr_AND_A_A();
        uint8_t instr_XOR_A_B();             uint8_t instr_XOR_A_C();             uint8_t instr_XOR_A_D();         uint8_t instr_XOR_A_E();
        uint8_t instr_XOR_A_H();             uint8_t instr_XOR_A_L();             uint8_t instr_XOR_A_mHL();       uint8_t instr_XOR_A_A();

        // --- Row 0xB_ ---
        uint8_t instr_OR_A_B();              uint8_t instr_OR_A_C();              uint8_t instr_OR_A_D();          uint8_t instr_OR_A_E();
        uint8_t instr_OR_A_H();              uint8_t instr_OR_A_L();              uint8_t instr_OR_A_mHL();        uint8_t instr_OR_A_A();
        uint8_t instr_CP_A_B();              uint8_t instr_CP_A_C();              uint8_t instr_CP_A_D();          uint8_t instr_CP_A_E();
        uint8_t instr_CP_A_H();              uint8_t instr_CP_A_L();              uint8_t instr_CP_A_mHL();        uint8_t instr_CP_A_A();

        // --- Row 0xC_ ---
        uint8_t instr_RET_NZ();            uint8_t instr_POP_BC();            uint8_t instr_JP_NZ_n16();     uint8_t instr_JP_n16();
        uint8_t instr_CALL_NZ_n16();       uint8_t instr_PUSH_BC();           uint8_t instr_ADD_A_n8();      uint8_t instr_RST_00H();
        uint8_t instr_RET_Z();             uint8_t instr_RET();               uint8_t instr_JP_Z_n16();      uint8_t instr_PREFIX_CB();
        uint8_t instr_CALL_Z_n16();        uint8_t instr_CALL_n16();          uint8_t instr_ADC_A_n8();      uint8_t instr_RST_08H();

        // --- Row 0xD_ ---
        uint8_t instr_RET_NC();            uint8_t instr_POP_DE();            uint8_t instr_JP_NC_n16();     uint8_t instr_UNUSED_D3();
        uint8_t instr_CALL_NC_n16();       uint8_t instr_PUSH_DE();           uint8_t instr_SUB_A_n8();        uint8_t instr_RST_10H();
        uint8_t instr_RET_C();             uint8_t instr_RETI();              uint8_t instr_JP_C_n16();      uint8_t instr_UNUSED_DB();
        uint8_t instr_CALL_C_n16();        uint8_t instr_UNUSED_DD();         uint8_t instr_SBC_A_n8();      uint8_t instr_RST_18H();

        // --- Row 0xE_ ---
        uint8_t instr_LDH_mn8_A();         uint8_t instr_POP_HL();            uint8_t instr_LD_mC_A();       uint8_t instr_UNUSED_E3();
        uint8_t instr_UNUSED_E4();         uint8_t instr_PUSH_HL();           uint8_t instr_AND_A_n8();        uint8_t instr_RST_20H();
        uint8_t instr_ADD_SP_e8();         uint8_t instr_JP_HL();             uint8_t instr_LD_mn16_A();     uint8_t instr_UNUSED_EB();
        uint8_t instr_UNUSED_EC();         uint8_t instr_UNUSED_ED();         uint8_t instr_XOR_A_n8();        uint8_t instr_RST_28H();

        // --- Row 0xF_ ---
        uint8_t instr_LDH_A_mn8();         uint8_t instr_POP_AF();            uint8_t instr_LD_A_mC();       uint8_t instr_DI();
        uint8_t instr_UNUSED_F4();         uint8_t instr_PUSH_AF();           uint8_t instr_OR_A_n8();         uint8_t instr_RST_30H();
        uint8_t instr_LD_HL_SP_plus_e8();  uint8_t instr_LD_SP_HL();          uint8_t instr_LD_A_mn16();     uint8_t instr_EI();
        uint8_t instr_UNUSED_FC();         uint8_t instr_UNUSED_FD();         uint8_t instr_CP_A_n8();         uint8_t instr_RST_38H();


        // =========================================================================
        // PREFIX CB OPCODES (0xCB 0x00 - 0xCB 0xFF)
        // =========================================================================

        // --- Row 0x0_ ---
        uint8_t instr_cb_RLC_B(); uint8_t instr_cb_RLC_C(); uint8_t instr_cb_RLC_D(); uint8_t instr_cb_RLC_E();
        uint8_t instr_cb_RLC_H(); uint8_t instr_cb_RLC_L(); uint8_t instr_cb_RLC_mHL(); uint8_t instr_cb_RLC_A();
        uint8_t instr_cb_RRC_B(); uint8_t instr_cb_RRC_C(); uint8_t instr_cb_RRC_D(); uint8_t instr_cb_RRC_E();
        uint8_t instr_cb_RRC_H(); uint8_t instr_cb_RRC_L(); uint8_t instr_cb_RRC_mHL(); uint8_t instr_cb_RRC_A();

        // --- Row 0x1_ ---
        uint8_t instr_cb_RL_B(); uint8_t instr_cb_RL_C(); uint8_t instr_cb_RL_D(); uint8_t instr_cb_RL_E();
        uint8_t instr_cb_RL_H(); uint8_t instr_cb_RL_L(); uint8_t instr_cb_RL_mHL(); uint8_t instr_cb_RL_A();
        uint8_t instr_cb_RR_B(); uint8_t instr_cb_RR_C(); uint8_t instr_cb_RR_D(); uint8_t instr_cb_RR_E();
        uint8_t instr_cb_RR_H(); uint8_t instr_cb_RR_L(); uint8_t instr_cb_RR_mHL(); uint8_t instr_cb_RR_A();

        // --- Row 0x2_ ---
        uint8_t instr_cb_SLA_B(); uint8_t instr_cb_SLA_C(); uint8_t instr_cb_SLA_D(); uint8_t instr_cb_SLA_E();
        uint8_t instr_cb_SLA_H(); uint8_t instr_cb_SLA_L(); uint8_t instr_cb_SLA_mHL(); uint8_t instr_cb_SLA_A();
        uint8_t instr_cb_SRA_B(); uint8_t instr_cb_SRA_C(); uint8_t instr_cb_SRA_D(); uint8_t instr_cb_SRA_E();
        uint8_t instr_cb_SRA_H(); uint8_t instr_cb_SRA_L(); uint8_t instr_cb_SRA_mHL(); uint8_t instr_cb_SRA_A();

        // --- Row 0x3_ ---
        uint8_t instr_cb_SWAP_B(); uint8_t instr_cb_SWAP_C(); uint8_t instr_cb_SWAP_D(); uint8_t instr_cb_SWAP_E();
        uint8_t instr_cb_SWAP_H(); uint8_t instr_cb_SWAP_L(); uint8_t instr_cb_SWAP_mHL(); uint8_t instr_cb_SWAP_A();
        uint8_t instr_cb_SRL_B(); uint8_t instr_cb_SRL_C(); uint8_t instr_cb_SRL_D(); uint8_t instr_cb_SRL_E();
        uint8_t instr_cb_SRL_H(); uint8_t instr_cb_SRL_L(); uint8_t instr_cb_SRL_mHL(); uint8_t instr_cb_SRL_A();

        // --- Row 0x4_ ---
        uint8_t instr_cb_BIT_0_B(); uint8_t instr_cb_BIT_0_C(); uint8_t instr_cb_BIT_0_D(); uint8_t instr_cb_BIT_0_E();
        uint8_t instr_cb_BIT_0_H(); uint8_t instr_cb_BIT_0_L(); uint8_t instr_cb_BIT_0_mHL(); uint8_t instr_cb_BIT_0_A();
        uint8_t instr_cb_BIT_1_B(); uint8_t instr_cb_BIT_1_C(); uint8_t instr_cb_BIT_1_D(); uint8_t instr_cb_BIT_1_E();
        uint8_t instr_cb_BIT_1_H(); uint8_t instr_cb_BIT_1_L(); uint8_t instr_cb_BIT_1_mHL(); uint8_t instr_cb_BIT_1_A();

        // --- Row 0x5_ ---
        uint8_t instr_cb_BIT_2_B(); uint8_t instr_cb_BIT_2_C(); uint8_t instr_cb_BIT_2_D(); uint8_t instr_cb_BIT_2_E();
        uint8_t instr_cb_BIT_2_H(); uint8_t instr_cb_BIT_2_L(); uint8_t instr_cb_BIT_2_mHL(); uint8_t instr_cb_BIT_2_A();
        uint8_t instr_cb_BIT_3_B(); uint8_t instr_cb_BIT_3_C(); uint8_t instr_cb_BIT_3_D(); uint8_t instr_cb_BIT_3_E();
        uint8_t instr_cb_BIT_3_H(); uint8_t instr_cb_BIT_3_L(); uint8_t instr_cb_BIT_3_mHL(); uint8_t instr_cb_BIT_3_A();

        // --- Row 0x6_ ---
        uint8_t instr_cb_BIT_4_B(); uint8_t instr_cb_BIT_4_C(); uint8_t instr_cb_BIT_4_D(); uint8_t instr_cb_BIT_4_E();
        uint8_t instr_cb_BIT_4_H(); uint8_t instr_cb_BIT_4_L(); uint8_t instr_cb_BIT_4_mHL(); uint8_t instr_cb_BIT_4_A();
        uint8_t instr_cb_BIT_5_B(); uint8_t instr_cb_BIT_5_C(); uint8_t instr_cb_BIT_5_D(); uint8_t instr_cb_BIT_5_E();
        uint8_t instr_cb_BIT_5_H(); uint8_t instr_cb_BIT_5_L(); uint8_t instr_cb_BIT_5_mHL(); uint8_t instr_cb_BIT_5_A();

        // --- Row 0x7_ ---
        uint8_t instr_cb_BIT_6_B(); uint8_t instr_cb_BIT_6_C(); uint8_t instr_cb_BIT_6_D(); uint8_t instr_cb_BIT_6_E();
        uint8_t instr_cb_BIT_6_H(); uint8_t instr_cb_BIT_6_L(); uint8_t instr_cb_BIT_6_mHL(); uint8_t instr_cb_BIT_6_A();
        uint8_t instr_cb_BIT_7_B(); uint8_t instr_cb_BIT_7_C(); uint8_t instr_cb_BIT_7_D(); uint8_t instr_cb_BIT_7_E();
        uint8_t instr_cb_BIT_7_H(); uint8_t instr_cb_BIT_7_L(); uint8_t instr_cb_BIT_7_mHL(); uint8_t instr_cb_BIT_7_A();

        // --- Row 0x8_ ---
        uint8_t instr_cb_RES_0_B(); uint8_t instr_cb_RES_0_C(); uint8_t instr_cb_RES_0_D(); uint8_t instr_cb_RES_0_E();
        uint8_t instr_cb_RES_0_H(); uint8_t instr_cb_RES_0_L(); uint8_t instr_cb_RES_0_mHL(); uint8_t instr_cb_RES_0_A();
        uint8_t instr_cb_RES_1_B(); uint8_t instr_cb_RES_1_C(); uint8_t instr_cb_RES_1_D(); uint8_t instr_cb_RES_1_E();
        uint8_t instr_cb_RES_1_H(); uint8_t instr_cb_RES_1_L(); uint8_t instr_cb_RES_1_mHL(); uint8_t instr_cb_RES_1_A();

        // --- Row 0x9_ ---
        uint8_t instr_cb_RES_2_B(); uint8_t instr_cb_RES_2_C(); uint8_t instr_cb_RES_2_D(); uint8_t instr_cb_RES_2_E();
        uint8_t instr_cb_RES_2_H(); uint8_t instr_cb_RES_2_L(); uint8_t instr_cb_RES_2_mHL(); uint8_t instr_cb_RES_2_A();
        uint8_t instr_cb_RES_3_B(); uint8_t instr_cb_RES_3_C(); uint8_t instr_cb_RES_3_D(); uint8_t instr_cb_RES_3_E();
        uint8_t instr_cb_RES_3_H(); uint8_t instr_cb_RES_3_L(); uint8_t instr_cb_RES_3_mHL(); uint8_t instr_cb_RES_3_A();

        // --- Row 0xA_ ---
        uint8_t instr_cb_RES_4_B(); uint8_t instr_cb_RES_4_C(); uint8_t instr_cb_RES_4_D(); uint8_t instr_cb_RES_4_E();
        uint8_t instr_cb_RES_4_H(); uint8_t instr_cb_RES_4_L(); uint8_t instr_cb_RES_4_mHL(); uint8_t instr_cb_RES_4_A();
        uint8_t instr_cb_RES_5_B(); uint8_t instr_cb_RES_5_C(); uint8_t instr_cb_RES_5_D(); uint8_t instr_cb_RES_5_E();
        uint8_t instr_cb_RES_5_H(); uint8_t instr_cb_RES_5_L(); uint8_t instr_cb_RES_5_mHL(); uint8_t instr_cb_RES_5_A();

        // --- Row 0xB_ ---
        uint8_t instr_cb_RES_6_B(); uint8_t instr_cb_RES_6_C(); uint8_t instr_cb_RES_6_D(); uint8_t instr_cb_RES_6_E();
        uint8_t instr_cb_RES_6_H(); uint8_t instr_cb_RES_6_L(); uint8_t instr_cb_RES_6_mHL(); uint8_t instr_cb_RES_6_A();
        uint8_t instr_cb_RES_7_B(); uint8_t instr_cb_RES_7_C(); uint8_t instr_cb_RES_7_D(); uint8_t instr_cb_RES_7_E();
        uint8_t instr_cb_RES_7_H(); uint8_t instr_cb_RES_7_L(); uint8_t instr_cb_RES_7_mHL(); uint8_t instr_cb_RES_7_A();

        // --- Row 0xC_ ---
        uint8_t instr_cb_SET_0_B(); uint8_t instr_cb_SET_0_C(); uint8_t instr_cb_SET_0_D(); uint8_t instr_cb_SET_0_E();
        uint8_t instr_cb_SET_0_H(); uint8_t instr_cb_SET_0_L(); uint8_t instr_cb_SET_0_mHL(); uint8_t instr_cb_SET_0_A();
        uint8_t instr_cb_SET_1_B(); uint8_t instr_cb_SET_1_C(); uint8_t instr_cb_SET_1_D(); uint8_t instr_cb_SET_1_E();
        uint8_t instr_cb_SET_1_H(); uint8_t instr_cb_SET_1_L(); uint8_t instr_cb_SET_1_mHL(); uint8_t instr_cb_SET_1_A();

        // --- Row 0xD_ ---
        uint8_t instr_cb_SET_2_B(); uint8_t instr_cb_SET_2_C(); uint8_t instr_cb_SET_2_D(); uint8_t instr_cb_SET_2_E();
        uint8_t instr_cb_SET_2_H(); uint8_t instr_cb_SET_2_L(); uint8_t instr_cb_SET_2_mHL(); uint8_t instr_cb_SET_2_A();
        uint8_t instr_cb_SET_3_B(); uint8_t instr_cb_SET_3_C(); uint8_t instr_cb_SET_3_D(); uint8_t instr_cb_SET_3_E();
        uint8_t instr_cb_SET_3_H(); uint8_t instr_cb_SET_3_L(); uint8_t instr_cb_SET_3_mHL(); uint8_t instr_cb_SET_3_A();

        // --- Row 0xE_ ---
        uint8_t instr_cb_SET_4_B(); uint8_t instr_cb_SET_4_C(); uint8_t instr_cb_SET_4_D(); uint8_t instr_cb_SET_4_E();
        uint8_t instr_cb_SET_4_H(); uint8_t instr_cb_SET_4_L(); uint8_t instr_cb_SET_4_mHL(); uint8_t instr_cb_SET_4_A();
        uint8_t instr_cb_SET_5_B(); uint8_t instr_cb_SET_5_C(); uint8_t instr_cb_SET_5_D(); uint8_t instr_cb_SET_5_E();
        uint8_t instr_cb_SET_5_H(); uint8_t instr_cb_SET_5_L(); uint8_t instr_cb_SET_5_mHL(); uint8_t instr_cb_SET_5_A();

        // --- Row 0xF_ ---
        uint8_t instr_cb_SET_6_B(); uint8_t instr_cb_SET_6_C(); uint8_t instr_cb_SET_6_D(); uint8_t instr_cb_SET_6_E();
        uint8_t instr_cb_SET_6_H(); uint8_t instr_cb_SET_6_L(); uint8_t instr_cb_SET_6_mHL(); uint8_t instr_cb_SET_6_A();
        uint8_t instr_cb_SET_7_B(); uint8_t instr_cb_SET_7_C(); uint8_t instr_cb_SET_7_D(); uint8_t instr_cb_SET_7_E();
        uint8_t instr_cb_SET_7_H(); uint8_t instr_cb_SET_7_L(); uint8_t instr_cb_SET_7_mHL(); uint8_t instr_cb_SET_7_A();
    };
}