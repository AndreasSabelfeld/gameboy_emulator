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
        CPU(MMU* mmu, Timer* timer);

        void tick();

        void step();
        void execute(const Instruction& inst, uint8_t opcode);
        void reset();
        int frame_cycles = 0;

    private:
        MMU* mmu;
        Timer* timer;

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
        bool is_halted = false;

        std::array<Instruction, 256> opcode_table;
        std::array<Instruction, 256> cb_opcode_table;

        void init_opcodes();

        void write_byte(uint16_t address, uint8_t value);

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

        void handle_interrupts();

        uint8_t read_byte(uint16_t address);

        void execute_cb();

        // =========================================================================
        // Helper Functions
        // =========================================================================
        void ADD(uint8_t& to, uint8_t value);
        void ADD_HL(uint16_t value);
        void ADC(uint8_t& to, uint8_t value);
        void SUB(uint8_t& to, uint8_t value);
        void SBC(uint8_t& to, uint8_t value);

        void AND_A(uint8_t value);
        void XOR_A(uint8_t value);
        void OR_A(uint8_t value);
        void CP_A(uint8_t value);

        void INC(uint8_t& to);
        void DEC(uint8_t& to);

        void RLC(uint8_t& to);
        void RRC(uint8_t& to);
        void RL(uint8_t& to);
        void RR(uint8_t& to);
        void SLA(uint8_t& to);
        void SRA(uint8_t& to);
        void SRL(uint8_t& to);
        void SWAP(uint8_t& to);

        void BIT(uint8_t bit, uint8_t& reg);
        void RES(uint8_t bit, uint8_t& reg);
        void SET(uint8_t bit, uint8_t &reg);

        uint16_t pop_16bit();
        void push_16bit(uint16_t value);
        inline uint16_t read_16bit(uint16_t address);

        // =========================================================================
        // STANDARD OPCODES (0x00 - 0xFF)
        // =========================================================================

        // the returned integer represents the delta of the

        // --- Row 0x0_ ---
        void instr_NOP();               void instr_LD_BC_n16();         void instr_LD_mBC_A();          void instr_INC_BC();
        void instr_INC_B();             void instr_DEC_B();             void instr_LD_B_n8();           void instr_RLCA();
        void instr_LD_mn16_SP();        void instr_ADD_HL_BC();         void instr_LD_A_mBC();          void instr_DEC_BC();
        void instr_INC_C();             void instr_DEC_C();             void instr_LD_C_n8();           void instr_RRCA();

        // --- Row 0x1_ ---
        void instr_STOP();              void instr_LD_DE_n16();         void instr_LD_mDE_A();          void instr_INC_DE();
        void instr_INC_D();             void instr_DEC_D();             void instr_LD_D_n8();           void instr_RLA();
        void instr_JR_n8();             void instr_ADD_HL_DE();         void instr_LD_A_mDE();          void instr_DEC_DE();
        void instr_INC_E();             void instr_DEC_E();             void instr_LD_E_n8();           void instr_RRA();

        // --- Row 0x2_ ---
        void instr_JR_NZ_n8();          void instr_LD_HL_n16();         void instr_LD_mHL_plus_A();     void instr_INC_HL();
        void instr_INC_H();             void instr_DEC_H();             void instr_LD_H_n8();           void instr_DAA();
        void instr_JR_Z_n8();           void instr_ADD_HL_HL();         void instr_LD_A_mHL_plus();     void instr_DEC_HL();
        void instr_INC_L();             void instr_DEC_L();             void instr_LD_L_n8();           void instr_CPL();

        // --- Row 0x3_ ---
        void instr_JR_NC_n8();          void instr_LD_SP_n16();         void instr_LD_mHL_minus_A();    void instr_INC_SP();
        void instr_INC_mHL();           void instr_DEC_mHL();           void instr_LD_mHL_n8();         void instr_SCF();
        void instr_JR_C_n8();           void instr_ADD_HL_SP();         void instr_LD_A_mHL_minus();    void instr_DEC_SP();
        void instr_INC_A();             void instr_DEC_A();             void instr_LD_A_n8();           void instr_CCF();

        // --- Row 0x4_ ---
        void instr_LD_B_B();            void instr_LD_B_C();            void instr_LD_B_D();            void instr_LD_B_E();
        void instr_LD_B_H();            void instr_LD_B_L();            void instr_LD_B_mHL();          void instr_LD_B_A();
        void instr_LD_C_B();            void instr_LD_C_C();            void instr_LD_C_D();            void instr_LD_C_E();
        void instr_LD_C_H();            void instr_LD_C_L();            void instr_LD_C_mHL();          void instr_LD_C_A();

        // --- Row 0x5_ ---
        void instr_LD_D_B();            void instr_LD_D_C();            void instr_LD_D_D();            void instr_LD_D_E();
        void instr_LD_D_H();            void instr_LD_D_L();            void instr_LD_D_mHL();          void instr_LD_D_A();
        void instr_LD_E_B();            void instr_LD_E_C();            void instr_LD_E_D();            void instr_LD_E_E();
        void instr_LD_E_H();            void instr_LD_E_L();            void instr_LD_E_mHL();          void instr_LD_E_A();

        // --- Row 0x6_ ---
        void instr_LD_H_B();            void instr_LD_H_C();            void instr_LD_H_D();            void instr_LD_H_E();
        void instr_LD_H_H();            void instr_LD_H_L();            void instr_LD_H_mHL();          void instr_LD_H_A();
        void instr_LD_L_B();            void instr_LD_L_C();            void instr_LD_L_D();            void instr_LD_L_E();
        void instr_LD_L_H();            void instr_LD_L_L();            void instr_LD_L_mHL();          void instr_LD_L_A();

        // --- Row 0x7_ ---
        void instr_LD_mHL_B();          void instr_LD_mHL_C();          void instr_LD_mHL_D();          void instr_LD_mHL_E();
        void instr_LD_mHL_H();          void instr_LD_mHL_L();          void instr_HALT();              void instr_LD_mHL_A();
        void instr_LD_A_B();            void instr_LD_A_C();            void instr_LD_A_D();            void instr_LD_A_E();
        void instr_LD_A_H();            void instr_LD_A_L();            void instr_LD_A_mHL();          void instr_LD_A_A();

        // --- Row 0x8_ ---
        void instr_ADD_A_B();           void instr_ADD_A_C();           void instr_ADD_A_D();       void instr_ADD_A_E();
        void instr_ADD_A_H();           void instr_ADD_A_L();           void instr_ADD_A_mHL();     void instr_ADD_A_A();
        void instr_ADC_A_B();           void instr_ADC_A_C();           void instr_ADC_A_D();       void instr_ADC_A_E();
        void instr_ADC_A_H();           void instr_ADC_A_L();           void instr_ADC_A_mHL();     void instr_ADC_A_A();

        // --- Row 0x9_ ---
        void instr_SUB_A_B();             void instr_SUB_A_C();             void instr_SUB_A_D();         void instr_SUB_A_E();
        void instr_SUB_A_H();             void instr_SUB_A_L();             void instr_SUB_A_mHL();       void instr_SUB_A_A();
        void instr_SBC_A_B();           void instr_SBC_A_C();           void instr_SBC_A_D();       void instr_SBC_A_E();
        void instr_SBC_A_H();           void instr_SBC_A_L();           void instr_SBC_A_mHL();     void instr_SBC_A_A();

        // --- Row 0xA_ ---
        void instr_AND_A_B();             void instr_AND_A_C();             void instr_AND_A_D();         void instr_AND_A_E();
        void instr_AND_A_H();             void instr_AND_A_L();             void instr_AND_A_mHL();       void instr_AND_A_A();
        void instr_XOR_A_B();             void instr_XOR_A_C();             void instr_XOR_A_D();         void instr_XOR_A_E();
        void instr_XOR_A_H();             void instr_XOR_A_L();             void instr_XOR_A_mHL();       void instr_XOR_A_A();

        // --- Row 0xB_ ---
        void instr_OR_A_B();              void instr_OR_A_C();              void instr_OR_A_D();          void instr_OR_A_E();
        void instr_OR_A_H();              void instr_OR_A_L();              void instr_OR_A_mHL();        void instr_OR_A_A();
        void instr_CP_A_B();              void instr_CP_A_C();              void instr_CP_A_D();          void instr_CP_A_E();
        void instr_CP_A_H();              void instr_CP_A_L();              void instr_CP_A_mHL();        void instr_CP_A_A();

        // --- Row 0xC_ ---
        void instr_RET_NZ();            void instr_POP_BC();            void instr_JP_NZ_n16();     void instr_JP_n16();
        void instr_CALL_NZ_n16();       void instr_PUSH_BC();           void instr_ADD_A_n8();      void instr_RST_00H();
        void instr_RET_Z();             void instr_RET();               void instr_JP_Z_n16();      void instr_PREFIX_CB();
        void instr_CALL_Z_n16();        void instr_CALL_n16();          void instr_ADC_A_n8();      void instr_RST_08H();

        // --- Row 0xD_ ---
        void instr_RET_NC();            void instr_POP_DE();            void instr_JP_NC_n16();     void instr_UNUSED_D3();
        void instr_CALL_NC_n16();       void instr_PUSH_DE();           void instr_SUB_A_n8();        void instr_RST_10H();
        void instr_RET_C();             void instr_RETI();              void instr_JP_C_n16();      void instr_UNUSED_DB();
        void instr_CALL_C_n16();        void instr_UNUSED_DD();         void instr_SBC_A_n8();      void instr_RST_18H();

        // --- Row 0xE_ ---
        void instr_LDH_mn8_A();         void instr_POP_HL();            void instr_LD_mC_A();       void instr_UNUSED_E3();
        void instr_UNUSED_E4();         void instr_PUSH_HL();           void instr_AND_A_n8();        void instr_RST_20H();
        void instr_ADD_SP_e8();         void instr_JP_HL();             void instr_LD_mn16_A();     void instr_UNUSED_EB();
        void instr_UNUSED_EC();         void instr_UNUSED_ED();         void instr_XOR_A_n8();        void instr_RST_28H();

        // --- Row 0xF_ ---
        void instr_LDH_A_mn8();         void instr_POP_AF();            void instr_LD_A_mC();       void instr_DI();
        void instr_UNUSED_F4();         void instr_PUSH_AF();           void instr_OR_A_n8();         void instr_RST_30H();
        void instr_LD_HL_SP_plus_e8();  void instr_LD_SP_HL();          void instr_LD_A_mn16();     void instr_EI();
        void instr_UNUSED_FC();         void instr_UNUSED_FD();         void instr_CP_A_n8();         void instr_RST_38H();


        // =========================================================================
        // PREFIX CB OPCODES (0xCB 0x00 - 0xCB 0xFF)
        // =========================================================================

        // --- Row 0x0_ ---
        void instr_cb_RLC_B(); void instr_cb_RLC_C(); void instr_cb_RLC_D(); void instr_cb_RLC_E();
        void instr_cb_RLC_H(); void instr_cb_RLC_L(); void instr_cb_RLC_mHL(); void instr_cb_RLC_A();
        void instr_cb_RRC_B(); void instr_cb_RRC_C(); void instr_cb_RRC_D(); void instr_cb_RRC_E();
        void instr_cb_RRC_H(); void instr_cb_RRC_L(); void instr_cb_RRC_mHL(); void instr_cb_RRC_A();

        // --- Row 0x1_ ---
        void instr_cb_RL_B(); void instr_cb_RL_C(); void instr_cb_RL_D(); void instr_cb_RL_E();
        void instr_cb_RL_H(); void instr_cb_RL_L(); void instr_cb_RL_mHL(); void instr_cb_RL_A();
        void instr_cb_RR_B(); void instr_cb_RR_C(); void instr_cb_RR_D(); void instr_cb_RR_E();
        void instr_cb_RR_H(); void instr_cb_RR_L(); void instr_cb_RR_mHL(); void instr_cb_RR_A();

        // --- Row 0x2_ ---
        void instr_cb_SLA_B(); void instr_cb_SLA_C(); void instr_cb_SLA_D(); void instr_cb_SLA_E();
        void instr_cb_SLA_H(); void instr_cb_SLA_L(); void instr_cb_SLA_mHL(); void instr_cb_SLA_A();
        void instr_cb_SRA_B(); void instr_cb_SRA_C(); void instr_cb_SRA_D(); void instr_cb_SRA_E();
        void instr_cb_SRA_H(); void instr_cb_SRA_L(); void instr_cb_SRA_mHL(); void instr_cb_SRA_A();

        // --- Row 0x3_ ---
        void instr_cb_SWAP_B(); void instr_cb_SWAP_C(); void instr_cb_SWAP_D(); void instr_cb_SWAP_E();
        void instr_cb_SWAP_H(); void instr_cb_SWAP_L(); void instr_cb_SWAP_mHL(); void instr_cb_SWAP_A();
        void instr_cb_SRL_B(); void instr_cb_SRL_C(); void instr_cb_SRL_D(); void instr_cb_SRL_E();
        void instr_cb_SRL_H(); void instr_cb_SRL_L(); void instr_cb_SRL_mHL(); void instr_cb_SRL_A();

        // --- Row 0x4_ ---
        void instr_cb_BIT_0_B(); void instr_cb_BIT_0_C(); void instr_cb_BIT_0_D(); void instr_cb_BIT_0_E();
        void instr_cb_BIT_0_H(); void instr_cb_BIT_0_L(); void instr_cb_BIT_0_mHL(); void instr_cb_BIT_0_A();
        void instr_cb_BIT_1_B(); void instr_cb_BIT_1_C(); void instr_cb_BIT_1_D(); void instr_cb_BIT_1_E();
        void instr_cb_BIT_1_H(); void instr_cb_BIT_1_L(); void instr_cb_BIT_1_mHL(); void instr_cb_BIT_1_A();

        // --- Row 0x5_ ---
        void instr_cb_BIT_2_B(); void instr_cb_BIT_2_C(); void instr_cb_BIT_2_D(); void instr_cb_BIT_2_E();
        void instr_cb_BIT_2_H(); void instr_cb_BIT_2_L(); void instr_cb_BIT_2_mHL(); void instr_cb_BIT_2_A();
        void instr_cb_BIT_3_B(); void instr_cb_BIT_3_C(); void instr_cb_BIT_3_D(); void instr_cb_BIT_3_E();
        void instr_cb_BIT_3_H(); void instr_cb_BIT_3_L(); void instr_cb_BIT_3_mHL(); void instr_cb_BIT_3_A();

        // --- Row 0x6_ ---
        void instr_cb_BIT_4_B(); void instr_cb_BIT_4_C(); void instr_cb_BIT_4_D(); void instr_cb_BIT_4_E();
        void instr_cb_BIT_4_H(); void instr_cb_BIT_4_L(); void instr_cb_BIT_4_mHL(); void instr_cb_BIT_4_A();
        void instr_cb_BIT_5_B(); void instr_cb_BIT_5_C(); void instr_cb_BIT_5_D(); void instr_cb_BIT_5_E();
        void instr_cb_BIT_5_H(); void instr_cb_BIT_5_L(); void instr_cb_BIT_5_mHL(); void instr_cb_BIT_5_A();

        // --- Row 0x7_ ---
        void instr_cb_BIT_6_B(); void instr_cb_BIT_6_C(); void instr_cb_BIT_6_D(); void instr_cb_BIT_6_E();
        void instr_cb_BIT_6_H(); void instr_cb_BIT_6_L(); void instr_cb_BIT_6_mHL(); void instr_cb_BIT_6_A();
        void instr_cb_BIT_7_B(); void instr_cb_BIT_7_C(); void instr_cb_BIT_7_D(); void instr_cb_BIT_7_E();
        void instr_cb_BIT_7_H(); void instr_cb_BIT_7_L(); void instr_cb_BIT_7_mHL(); void instr_cb_BIT_7_A();

        // --- Row 0x8_ ---
        void instr_cb_RES_0_B(); void instr_cb_RES_0_C(); void instr_cb_RES_0_D(); void instr_cb_RES_0_E();
        void instr_cb_RES_0_H(); void instr_cb_RES_0_L(); void instr_cb_RES_0_mHL(); void instr_cb_RES_0_A();
        void instr_cb_RES_1_B(); void instr_cb_RES_1_C(); void instr_cb_RES_1_D(); void instr_cb_RES_1_E();
        void instr_cb_RES_1_H(); void instr_cb_RES_1_L(); void instr_cb_RES_1_mHL(); void instr_cb_RES_1_A();

        // --- Row 0x9_ ---
        void instr_cb_RES_2_B(); void instr_cb_RES_2_C(); void instr_cb_RES_2_D(); void instr_cb_RES_2_E();
        void instr_cb_RES_2_H(); void instr_cb_RES_2_L(); void instr_cb_RES_2_mHL(); void instr_cb_RES_2_A();
        void instr_cb_RES_3_B(); void instr_cb_RES_3_C(); void instr_cb_RES_3_D(); void instr_cb_RES_3_E();
        void instr_cb_RES_3_H(); void instr_cb_RES_3_L(); void instr_cb_RES_3_mHL(); void instr_cb_RES_3_A();

        // --- Row 0xA_ ---
        void instr_cb_RES_4_B(); void instr_cb_RES_4_C(); void instr_cb_RES_4_D(); void instr_cb_RES_4_E();
        void instr_cb_RES_4_H(); void instr_cb_RES_4_L(); void instr_cb_RES_4_mHL(); void instr_cb_RES_4_A();
        void instr_cb_RES_5_B(); void instr_cb_RES_5_C(); void instr_cb_RES_5_D(); void instr_cb_RES_5_E();
        void instr_cb_RES_5_H(); void instr_cb_RES_5_L(); void instr_cb_RES_5_mHL(); void instr_cb_RES_5_A();

        // --- Row 0xB_ ---
        void instr_cb_RES_6_B(); void instr_cb_RES_6_C(); void instr_cb_RES_6_D(); void instr_cb_RES_6_E();
        void instr_cb_RES_6_H(); void instr_cb_RES_6_L(); void instr_cb_RES_6_mHL(); void instr_cb_RES_6_A();
        void instr_cb_RES_7_B(); void instr_cb_RES_7_C(); void instr_cb_RES_7_D(); void instr_cb_RES_7_E();
        void instr_cb_RES_7_H(); void instr_cb_RES_7_L(); void instr_cb_RES_7_mHL(); void instr_cb_RES_7_A();

        // --- Row 0xC_ ---
        void instr_cb_SET_0_B(); void instr_cb_SET_0_C(); void instr_cb_SET_0_D(); void instr_cb_SET_0_E();
        void instr_cb_SET_0_H(); void instr_cb_SET_0_L(); void instr_cb_SET_0_mHL(); void instr_cb_SET_0_A();
        void instr_cb_SET_1_B(); void instr_cb_SET_1_C(); void instr_cb_SET_1_D(); void instr_cb_SET_1_E();
        void instr_cb_SET_1_H(); void instr_cb_SET_1_L(); void instr_cb_SET_1_mHL(); void instr_cb_SET_1_A();

        // --- Row 0xD_ ---
        void instr_cb_SET_2_B(); void instr_cb_SET_2_C(); void instr_cb_SET_2_D(); void instr_cb_SET_2_E();
        void instr_cb_SET_2_H(); void instr_cb_SET_2_L(); void instr_cb_SET_2_mHL(); void instr_cb_SET_2_A();
        void instr_cb_SET_3_B(); void instr_cb_SET_3_C(); void instr_cb_SET_3_D(); void instr_cb_SET_3_E();
        void instr_cb_SET_3_H(); void instr_cb_SET_3_L(); void instr_cb_SET_3_mHL(); void instr_cb_SET_3_A();

        // --- Row 0xE_ ---
        void instr_cb_SET_4_B(); void instr_cb_SET_4_C(); void instr_cb_SET_4_D(); void instr_cb_SET_4_E();
        void instr_cb_SET_4_H(); void instr_cb_SET_4_L(); void instr_cb_SET_4_mHL(); void instr_cb_SET_4_A();
        void instr_cb_SET_5_B(); void instr_cb_SET_5_C(); void instr_cb_SET_5_D(); void instr_cb_SET_5_E();
        void instr_cb_SET_5_H(); void instr_cb_SET_5_L(); void instr_cb_SET_5_mHL(); void instr_cb_SET_5_A();

        // --- Row 0xF_ ---
        void instr_cb_SET_6_B(); void instr_cb_SET_6_C(); void instr_cb_SET_6_D(); void instr_cb_SET_6_E();
        void instr_cb_SET_6_H(); void instr_cb_SET_6_L(); void instr_cb_SET_6_mHL(); void instr_cb_SET_6_A();
        void instr_cb_SET_7_B(); void instr_cb_SET_7_C(); void instr_cb_SET_7_D(); void instr_cb_SET_7_E();
        void instr_cb_SET_7_H(); void instr_cb_SET_7_L(); void instr_cb_SET_7_mHL(); void instr_cb_SET_7_A();
    };
}