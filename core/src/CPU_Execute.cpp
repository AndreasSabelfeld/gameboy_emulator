//
// Created by Andreas Sabelfeld on 27.04.2026.
//

#include <ios>
#include <iostream>
#include <ostream>

#include "CPU.h"

// #define EMULATOR_DEBUG

namespace gb::core {
    uint8_t CPU::execute(const Instruction &inst, uint8_t opcode) {
#ifdef EMULATOR_DEBUG
        std::cout << "Executing: " << inst.mnemonic
              << " at PC: " << std::hex << PC
              << " | DE: " << std::hex << DE.word
              << " | Z: " << get_flag_z() << std::endl;
#endif

        switch (opcode) {
            // --- Row 0x0_ ---
            case 0x00: return instr_NOP();
            case 0x01: return instr_LD_BC_n16();
            case 0x02: return instr_LD_mBC_A();
            case 0x03: return instr_INC_BC();
            case 0x04: return instr_INC_B();
            case 0x05: return instr_DEC_B();
            case 0x06: return instr_LD_B_n8();
            case 0x07: return instr_RLCA();
            case 0x08: return instr_LD_mn16_SP();
            case 0x09: return instr_ADD_HL_BC();
            case 0x0A: return instr_LD_A_mBC();
            case 0x0B: return instr_DEC_BC();
            case 0x0C: return instr_INC_C();
            case 0x0D: return instr_DEC_C();
            case 0x0E: return instr_LD_C_n8();
            case 0x0F: return instr_RRCA();

            // --- Row 0x1_ ---
            case 0x10: return instr_STOP();
            case 0x11: return instr_LD_DE_n16();
            case 0x12: return instr_LD_mDE_A();
            case 0x13: return instr_INC_DE();
            case 0x14: return instr_INC_D();
            case 0x15: return instr_DEC_D();
            case 0x16: return instr_LD_D_n8();
            case 0x17: return instr_RLA();
            case 0x18: return instr_JR_n8();
            case 0x19: return instr_ADD_HL_DE();
            case 0x1A: return instr_LD_A_mDE();
            case 0x1B: return instr_DEC_DE();
            case 0x1C: return instr_INC_E();
            case 0x1D: return instr_DEC_E();
            case 0x1E: return instr_LD_E_n8();
            case 0x1F: return instr_RRA();

            // --- Row 0x2_ ---
            case 0x20: return instr_JR_NZ_n8();
            case 0x21: return instr_LD_HL_n16();
            case 0x22: return instr_LD_mHL_plus_A();
            case 0x23: return instr_INC_HL();
            case 0x24: return instr_INC_H();
            case 0x25: return instr_DEC_H();
            case 0x26: return instr_LD_H_n8();
            case 0x27: return instr_DAA();
            case 0x28: return instr_JR_Z_n8();
            case 0x29: return instr_ADD_HL_HL();
            case 0x2A: return instr_LD_A_mHL_plus();
            case 0x2B: return instr_DEC_HL();
            case 0x2C: return instr_INC_L();
            case 0x2D: return instr_DEC_L();
            case 0x2E: return instr_LD_L_n8();
            case 0x2F: return instr_CPL();

            // --- Row 0x3_ ---
            case 0x30: return instr_JR_NC_n8();
            case 0x31: return instr_LD_SP_n16();
            case 0x32: return instr_LD_mHL_minus_A();
            case 0x33: return instr_INC_SP();
            case 0x34: return instr_INC_mHL();
            case 0x35: return instr_DEC_mHL();
            case 0x36: return instr_LD_mHL_n8();
            case 0x37: return instr_SCF();
            case 0x38: return instr_JR_C_n8();
            case 0x39: return instr_ADD_HL_SP();
            case 0x3A: return instr_LD_A_mHL_minus();
            case 0x3B: return instr_DEC_SP();
            case 0x3C: return instr_INC_A();
            case 0x3D: return instr_DEC_A();
            case 0x3E: return instr_LD_A_n8();
            case 0x3F: return instr_CCF();

            // --- Row 0x4_ ---
            case 0x40: return instr_LD_B_B();
            case 0x41: return instr_LD_B_C();
            case 0x42: return instr_LD_B_D();
            case 0x43: return instr_LD_B_E();
            case 0x44: return instr_LD_B_H();
            case 0x45: return instr_LD_B_L();
            case 0x46: return instr_LD_B_mHL();
            case 0x47: return instr_LD_B_A();
            case 0x48: return instr_LD_C_B();
            case 0x49: return instr_LD_C_C();
            case 0x4A: return instr_LD_C_D();
            case 0x4B: return instr_LD_C_E();
            case 0x4C: return instr_LD_C_H();
            case 0x4D: return instr_LD_C_L();
            case 0x4E: return instr_LD_C_mHL();
            case 0x4F: return instr_LD_C_A();

            // --- Row 0x5_ ---
            case 0x50: return instr_LD_D_B();
            case 0x51: return instr_LD_D_C();
            case 0x52: return instr_LD_D_D();
            case 0x53: return instr_LD_D_E();
            case 0x54: return instr_LD_D_H();
            case 0x55: return instr_LD_D_L();
            case 0x56: return instr_LD_D_mHL();
            case 0x57: return instr_LD_D_A();
            case 0x58: return instr_LD_E_B();
            case 0x59: return instr_LD_E_C();
            case 0x5A: return instr_LD_E_D();
            case 0x5B: return instr_LD_E_E();
            case 0x5C: return instr_LD_E_H();
            case 0x5D: return instr_LD_E_L();
            case 0x5E: return instr_LD_E_mHL();
            case 0x5F: return instr_LD_E_A();

            // --- Row 0x6_ ---
            case 0x60: return instr_LD_H_B();
            case 0x61: return instr_LD_H_C();
            case 0x62: return instr_LD_H_D();
            case 0x63: return instr_LD_H_E();
            case 0x64: return instr_LD_H_H();
            case 0x65: return instr_LD_H_L();
            case 0x66: return instr_LD_H_mHL();
            case 0x67: return instr_LD_H_A();
            case 0x68: return instr_LD_L_B();
            case 0x69: return instr_LD_L_C();
            case 0x6A: return instr_LD_L_D();
            case 0x6B: return instr_LD_L_E();
            case 0x6C: return instr_LD_L_H();
            case 0x6D: return instr_LD_L_L();
            case 0x6E: return instr_LD_L_mHL();
            case 0x6F: return instr_LD_L_A();

            // --- Row 0x7_ ---
            case 0x70: return instr_LD_mHL_B();
            case 0x71: return instr_LD_mHL_C();
            case 0x72: return instr_LD_mHL_D();
            case 0x73: return instr_LD_mHL_E();
            case 0x74: return instr_LD_mHL_H();
            case 0x75: return instr_LD_mHL_L();
            case 0x76: return instr_HALT();
            case 0x77: return instr_LD_mHL_A();
            case 0x78: return instr_LD_A_B();
            case 0x79: return instr_LD_A_C();
            case 0x7A: return instr_LD_A_D();
            case 0x7B: return instr_LD_A_E();
            case 0x7C: return instr_LD_A_H();
            case 0x7D: return instr_LD_A_L();
            case 0x7E: return instr_LD_A_mHL();
            case 0x7F: return instr_LD_A_A();

            // --- Row 0x8_ ---
            case 0x80: return instr_ADD_A_B();
            case 0x81: return instr_ADD_A_C();
            case 0x82: return instr_ADD_A_D();
            case 0x83: return instr_ADD_A_E();
            case 0x84: return instr_ADD_A_H();
            case 0x85: return instr_ADD_A_L();
            case 0x86: return instr_ADD_A_mHL();
            case 0x87: return instr_ADD_A_A();
            case 0x88: return instr_ADC_A_B();
            case 0x89: return instr_ADC_A_C();
            case 0x8A: return instr_ADC_A_D();
            case 0x8B: return instr_ADC_A_E();
            case 0x8C: return instr_ADC_A_H();
            case 0x8D: return instr_ADC_A_L();
            case 0x8E: return instr_ADC_A_mHL();
            case 0x8F: return instr_ADC_A_A();

            // --- Row 0x9_ ---
            case 0x90: return instr_SUB_A_B();
            case 0x91: return instr_SUB_A_C();
            case 0x92: return instr_SUB_A_D();
            case 0x93: return instr_SUB_A_E();
            case 0x94: return instr_SUB_A_H();
            case 0x95: return instr_SUB_A_L();
            case 0x96: return instr_SUB_A_mHL();
            case 0x97: return instr_SUB_A_A();
            case 0x98: return instr_SBC_A_B();
            case 0x99: return instr_SBC_A_C();
            case 0x9A: return instr_SBC_A_D();
            case 0x9B: return instr_SBC_A_E();
            case 0x9C: return instr_SBC_A_H();
            case 0x9D: return instr_SBC_A_L();
            case 0x9E: return instr_SBC_A_mHL();
            case 0x9F: return instr_SBC_A_A();

            // --- Row 0xA_ ---
            case 0xA0: return instr_AND_A_B();
            case 0xA1: return instr_AND_A_C();
            case 0xA2: return instr_AND_A_D();
            case 0xA3: return instr_AND_A_E();
            case 0xA4: return instr_AND_A_H();
            case 0xA5: return instr_AND_A_L();
            case 0xA6: return instr_AND_A_mHL();
            case 0xA7: return instr_AND_A_A();
            case 0xA8: return instr_XOR_A_B();
            case 0xA9: return instr_XOR_A_C();
            case 0xAA: return instr_XOR_A_D();
            case 0xAB: return instr_XOR_A_E();
            case 0xAC: return instr_XOR_A_H();
            case 0xAD: return instr_XOR_A_L();
            case 0xAE: return instr_XOR_A_mHL();
            case 0xAF: return instr_XOR_A_A();

            // --- Row 0xB_ ---
            case 0xB0: return instr_OR_A_B();
            case 0xB1: return instr_OR_A_C();
            case 0xB2: return instr_OR_A_D();
            case 0xB3: return instr_OR_A_E();
            case 0xB4: return instr_OR_A_H();
            case 0xB5: return instr_OR_A_L();
            case 0xB6: return instr_OR_A_mHL();
            case 0xB7: return instr_OR_A_A();
            case 0xB8: return instr_CP_A_B();
            case 0xB9: return instr_CP_A_C();
            case 0xBA: return instr_CP_A_D();
            case 0xBB: return instr_CP_A_E();
            case 0xBC: return instr_CP_A_H();
            case 0xBD: return instr_CP_A_L();
            case 0xBE: return instr_CP_A_mHL();
            case 0xBF: return instr_CP_A_A();

            // --- Row 0xC_ ---
            case 0xC0: return instr_RET_NZ();
            case 0xC1: return instr_POP_BC();
            case 0xC2: return instr_JP_NZ_n16();
            case 0xC3: return instr_JP_n16();
            case 0xC4: return instr_CALL_NZ_n16();
            case 0xC5: return instr_PUSH_BC();
            case 0xC6: return instr_ADD_A_n8();
            case 0xC7: return instr_RST_00H();
            case 0xC8: return instr_RET_Z();
            case 0xC9: return instr_RET();
            case 0xCA: return instr_JP_Z_n16();
            case 0xCB: return instr_PREFIX_CB();
            case 0xCC: return instr_CALL_Z_n16();
            case 0xCD: return instr_CALL_n16();
            case 0xCE: return instr_ADC_A_n8();
            case 0xCF: return instr_RST_08H();

            // --- Row 0xD_ ---
            case 0xD0: return instr_RET_NC();
            case 0xD1: return instr_POP_DE();
            case 0xD2: return instr_JP_NC_n16();
            case 0xD3: return instr_UNUSED_D3();
            case 0xD4: return instr_CALL_NC_n16();
            case 0xD5: return instr_PUSH_DE();
            case 0xD6: return instr_SUB_A_n8();
            case 0xD7: return instr_RST_10H();
            case 0xD8: return instr_RET_C();
            case 0xD9: return instr_RETI();
            case 0xDA: return instr_JP_C_n16();
            case 0xDB: return instr_UNUSED_DB();
            case 0xDC: return instr_CALL_C_n16();
            case 0xDD: return instr_UNUSED_DD();
            case 0xDE: return instr_SBC_A_n8();
            case 0xDF: return instr_RST_18H();

            // --- Row 0xE_ ---
            case 0xE0: return instr_LDH_mn8_A();
            case 0xE1: return instr_POP_HL();
            case 0xE2: return instr_LD_mC_A();
            case 0xE3: return instr_UNUSED_E3();
            case 0xE4: return instr_UNUSED_E4();
            case 0xE5: return instr_PUSH_HL();
            case 0xE6: return instr_AND_A_n8();
            case 0xE7: return instr_RST_20H();
            case 0xE8: return instr_ADD_SP_e8();
            case 0xE9: return instr_JP_HL();
            case 0xEA: return instr_LD_mn16_A();
            case 0xEB: return instr_UNUSED_EB();
            case 0xEC: return instr_UNUSED_EC();
            case 0xED: return instr_UNUSED_ED();
            case 0xEE: return instr_XOR_A_n8();
            case 0xEF: return instr_RST_28H();

            // --- Row 0xF_ ---
            case 0xF0: return instr_LDH_A_mn8();
            case 0xF1: return instr_POP_AF();
            case 0xF2: return instr_LD_A_mC();
            case 0xF3: return instr_DI();
            case 0xF4: return instr_UNUSED_F4();
            case 0xF5: return instr_PUSH_AF();
            case 0xF6: return instr_OR_A_n8();
            case 0xF7: return instr_RST_30H();
            case 0xF8: return instr_LD_HL_SP_plus_e8();
            case 0xF9: return instr_LD_SP_HL();
            case 0xFA: return instr_LD_A_mn16();
            case 0xFB: return instr_EI();
            case 0xFC: return instr_UNUSED_FC();
            case 0xFD: return instr_UNUSED_FD();
            case 0xFE: return instr_CP_A_n8();
            case 0xFF: return instr_RST_38H();
            default:
                // It should be mathematically impossible to hit this default;
                return 0;
        }
    }

    uint8_t CPU::execute_cb() {
        uint8_t opcode = fetch_byte();

        switch (opcode) {
            // --- Row 0x0_ ---
            case 0x00: return instr_cb_RLC_B();
            case 0x01: return instr_cb_RLC_C();
            case 0x02: return instr_cb_RLC_D();
            case 0x03: return instr_cb_RLC_E();
            case 0x04: return instr_cb_RLC_H();
            case 0x05: return instr_cb_RLC_L();
            case 0x06: return instr_cb_RLC_mHL();
            case 0x07: return instr_cb_RLC_A();
            case 0x08: return instr_cb_RRC_B();
            case 0x09: return instr_cb_RRC_C();
            case 0x0A: return instr_cb_RRC_D();
            case 0x0B: return instr_cb_RRC_E();
            case 0x0C: return instr_cb_RRC_H();
            case 0x0D: return instr_cb_RRC_L();
            case 0x0E: return instr_cb_RRC_mHL();
            case 0x0F: return instr_cb_RRC_A();

            // --- Row 0x1_ ---
            case 0x10: return instr_cb_RL_B();
            case 0x11: return instr_cb_RL_C();
            case 0x12: return instr_cb_RL_D();
            case 0x13: return instr_cb_RL_E();
            case 0x14: return instr_cb_RL_H();
            case 0x15: return instr_cb_RL_L();
            case 0x16: return instr_cb_RL_mHL();
            case 0x17: return instr_cb_RL_A();
            case 0x18: return instr_cb_RR_B();
            case 0x19: return instr_cb_RR_C();
            case 0x1A: return instr_cb_RR_D();
            case 0x1B: return instr_cb_RR_E();
            case 0x1C: return instr_cb_RR_H();
            case 0x1D: return instr_cb_RR_L();
            case 0x1E: return instr_cb_RR_mHL();
            case 0x1F: return instr_cb_RR_A();

            // --- Row 0x2_ ---
            case 0x20: return instr_cb_SLA_B();
            case 0x21: return instr_cb_SLA_C();
            case 0x22: return instr_cb_SLA_D();
            case 0x23: return instr_cb_SLA_E();
            case 0x24: return instr_cb_SLA_H();
            case 0x25: return instr_cb_SLA_L();
            case 0x26: return instr_cb_SLA_mHL();
            case 0x27: return instr_cb_SLA_A();
            case 0x28: return instr_cb_SRA_B();
            case 0x29: return instr_cb_SRA_C();
            case 0x2A: return instr_cb_SRA_D();
            case 0x2B: return instr_cb_SRA_E();
            case 0x2C: return instr_cb_SRA_H();
            case 0x2D: return instr_cb_SRA_L();
            case 0x2E: return instr_cb_SRA_mHL();
            case 0x2F: return instr_cb_SRA_A();

            // --- Row 0x3_ ---
            case 0x30: return instr_cb_SWAP_B();
            case 0x31: return instr_cb_SWAP_C();
            case 0x32: return instr_cb_SWAP_D();
            case 0x33: return instr_cb_SWAP_E();
            case 0x34: return instr_cb_SWAP_H();
            case 0x35: return instr_cb_SWAP_L();
            case 0x36: return instr_cb_SWAP_mHL();
            case 0x37: return instr_cb_SWAP_A();
            case 0x38: return instr_cb_SRL_B();
            case 0x39: return instr_cb_SRL_C();
            case 0x3A: return instr_cb_SRL_D();
            case 0x3B: return instr_cb_SRL_E();
            case 0x3C: return instr_cb_SRL_H();
            case 0x3D: return instr_cb_SRL_L();
            case 0x3E: return instr_cb_SRL_mHL();
            case 0x3F: return instr_cb_SRL_A();

            // --- Row 0x4_ ---
            case 0x40: return instr_cb_BIT_0_B();
            case 0x41: return instr_cb_BIT_0_C();
            case 0x42: return instr_cb_BIT_0_D();
            case 0x43: return instr_cb_BIT_0_E();
            case 0x44: return instr_cb_BIT_0_H();
            case 0x45: return instr_cb_BIT_0_L();
            case 0x46: return instr_cb_BIT_0_mHL();
            case 0x47: return instr_cb_BIT_0_A();
            case 0x48: return instr_cb_BIT_1_B();
            case 0x49: return instr_cb_BIT_1_C();
            case 0x4A: return instr_cb_BIT_1_D();
            case 0x4B: return instr_cb_BIT_1_E();
            case 0x4C: return instr_cb_BIT_1_H();
            case 0x4D: return instr_cb_BIT_1_L();
            case 0x4E: return instr_cb_BIT_1_mHL();
            case 0x4F: return instr_cb_BIT_1_A();

            // --- Row 0x5_ ---
            case 0x50: return instr_cb_BIT_2_B();
            case 0x51: return instr_cb_BIT_2_C();
            case 0x52: return instr_cb_BIT_2_D();
            case 0x53: return instr_cb_BIT_2_E();
            case 0x54: return instr_cb_BIT_2_H();
            case 0x55: return instr_cb_BIT_2_L();
            case 0x56: return instr_cb_BIT_2_mHL();
            case 0x57: return instr_cb_BIT_2_A();
            case 0x58: return instr_cb_BIT_3_B();
            case 0x59: return instr_cb_BIT_3_C();
            case 0x5A: return instr_cb_BIT_3_D();
            case 0x5B: return instr_cb_BIT_3_E();
            case 0x5C: return instr_cb_BIT_3_H();
            case 0x5D: return instr_cb_BIT_3_L();
            case 0x5E: return instr_cb_BIT_3_mHL();
            case 0x5F: return instr_cb_BIT_3_A();

            // --- Row 0x6_ ---
            case 0x60: return instr_cb_BIT_4_B();
            case 0x61: return instr_cb_BIT_4_C();
            case 0x62: return instr_cb_BIT_4_D();
            case 0x63: return instr_cb_BIT_4_E();
            case 0x64: return instr_cb_BIT_4_H();
            case 0x65: return instr_cb_BIT_4_L();
            case 0x66: return instr_cb_BIT_4_mHL();
            case 0x67: return instr_cb_BIT_4_A();
            case 0x68: return instr_cb_BIT_5_B();
            case 0x69: return instr_cb_BIT_5_C();
            case 0x6A: return instr_cb_BIT_5_D();
            case 0x6B: return instr_cb_BIT_5_E();
            case 0x6C: return instr_cb_BIT_5_H();
            case 0x6D: return instr_cb_BIT_5_L();
            case 0x6E: return instr_cb_BIT_5_mHL();
            case 0x6F: return instr_cb_BIT_5_A();

            // --- Row 0x7_ ---
            case 0x70: return instr_cb_BIT_6_B();
            case 0x71: return instr_cb_BIT_6_C();
            case 0x72: return instr_cb_BIT_6_D();
            case 0x73: return instr_cb_BIT_6_E();
            case 0x74: return instr_cb_BIT_6_H();
            case 0x75: return instr_cb_BIT_6_L();
            case 0x76: return instr_cb_BIT_6_mHL();
            case 0x77: return instr_cb_BIT_6_A();
            case 0x78: return instr_cb_BIT_7_B();
            case 0x79: return instr_cb_BIT_7_C();
            case 0x7A: return instr_cb_BIT_7_D();
            case 0x7B: return instr_cb_BIT_7_E();
            case 0x7C: return instr_cb_BIT_7_H();
            case 0x7D: return instr_cb_BIT_7_L();
            case 0x7E: return instr_cb_BIT_7_mHL();
            case 0x7F: return instr_cb_BIT_7_A();

            // --- Row 0x8_ ---
            case 0x80: return instr_cb_RES_0_B();
            case 0x81: return instr_cb_RES_0_C();
            case 0x82: return instr_cb_RES_0_D();
            case 0x83: return instr_cb_RES_0_E();
            case 0x84: return instr_cb_RES_0_H();
            case 0x85: return instr_cb_RES_0_L();
            case 0x86: return instr_cb_RES_0_mHL();
            case 0x87: return instr_cb_RES_0_A();
            case 0x88: return instr_cb_RES_1_B();
            case 0x89: return instr_cb_RES_1_C();
            case 0x8A: return instr_cb_RES_1_D();
            case 0x8B: return instr_cb_RES_1_E();
            case 0x8C: return instr_cb_RES_1_H();
            case 0x8D: return instr_cb_RES_1_L();
            case 0x8E: return instr_cb_RES_1_mHL();
            case 0x8F: return instr_cb_RES_1_A();

            // --- Row 0x9_ ---
            case 0x90: return instr_cb_RES_2_B();
            case 0x91: return instr_cb_RES_2_C();
            case 0x92: return instr_cb_RES_2_D();
            case 0x93: return instr_cb_RES_2_E();
            case 0x94: return instr_cb_RES_2_H();
            case 0x95: return instr_cb_RES_2_L();
            case 0x96: return instr_cb_RES_2_mHL();
            case 0x97: return instr_cb_RES_2_A();
            case 0x98: return instr_cb_RES_3_B();
            case 0x99: return instr_cb_RES_3_C();
            case 0x9A: return instr_cb_RES_3_D();
            case 0x9B: return instr_cb_RES_3_E();
            case 0x9C: return instr_cb_RES_3_H();
            case 0x9D: return instr_cb_RES_3_L();
            case 0x9E: return instr_cb_RES_3_mHL();
            case 0x9F: return instr_cb_RES_3_A();

            // --- Row 0xA_ ---
            case 0xA0: return instr_cb_RES_4_B();
            case 0xA1: return instr_cb_RES_4_C();
            case 0xA2: return instr_cb_RES_4_D();
            case 0xA3: return instr_cb_RES_4_E();
            case 0xA4: return instr_cb_RES_4_H();
            case 0xA5: return instr_cb_RES_4_L();
            case 0xA6: return instr_cb_RES_4_mHL();
            case 0xA7: return instr_cb_RES_4_A();
            case 0xA8: return instr_cb_RES_5_B();
            case 0xA9: return instr_cb_RES_5_C();
            case 0xAA: return instr_cb_RES_5_D();
            case 0xAB: return instr_cb_RES_5_E();
            case 0xAC: return instr_cb_RES_5_H();
            case 0xAD: return instr_cb_RES_5_L();
            case 0xAE: return instr_cb_RES_5_mHL();
            case 0xAF: return instr_cb_RES_5_A();

            // --- Row 0xB_ ---
            case 0xB0: return instr_cb_RES_6_B();
            case 0xB1: return instr_cb_RES_6_C();
            case 0xB2: return instr_cb_RES_6_D();
            case 0xB3: return instr_cb_RES_6_E();
            case 0xB4: return instr_cb_RES_6_H();
            case 0xB5: return instr_cb_RES_6_L();
            case 0xB6: return instr_cb_RES_6_mHL();
            case 0xB7: return instr_cb_RES_6_A();
            case 0xB8: return instr_cb_RES_7_B();
            case 0xB9: return instr_cb_RES_7_C();
            case 0xBA: return instr_cb_RES_7_D();
            case 0xBB: return instr_cb_RES_7_E();
            case 0xBC: return instr_cb_RES_7_H();
            case 0xBD: return instr_cb_RES_7_L();
            case 0xBE: return instr_cb_RES_7_mHL();
            case 0xBF: return instr_cb_RES_7_A();

            // --- Row 0xC_ ---
            case 0xC0: return instr_cb_SET_0_B();
            case 0xC1: return instr_cb_SET_0_C();
            case 0xC2: return instr_cb_SET_0_D();
            case 0xC3: return instr_cb_SET_0_E();
            case 0xC4: return instr_cb_SET_0_H();
            case 0xC5: return instr_cb_SET_0_L();
            case 0xC6: return instr_cb_SET_0_mHL();
            case 0xC7: return instr_cb_SET_0_A();
            case 0xC8: return instr_cb_SET_1_B();
            case 0xC9: return instr_cb_SET_1_C();
            case 0xCA: return instr_cb_SET_1_D();
            case 0xCB: return instr_cb_SET_1_E();
            case 0xCC: return instr_cb_SET_1_H();
            case 0xCD: return instr_cb_SET_1_L();
            case 0xCE: return instr_cb_SET_1_mHL();
            case 0xCF: return instr_cb_SET_1_A();

            // --- Row 0xD_ ---
            case 0xD0: return instr_cb_SET_2_B();
            case 0xD1: return instr_cb_SET_2_C();
            case 0xD2: return instr_cb_SET_2_D();
            case 0xD3: return instr_cb_SET_2_E();
            case 0xD4: return instr_cb_SET_2_H();
            case 0xD5: return instr_cb_SET_2_L();
            case 0xD6: return instr_cb_SET_2_mHL();
            case 0xD7: return instr_cb_SET_2_A();
            case 0xD8: return instr_cb_SET_3_B();
            case 0xD9: return instr_cb_SET_3_C();
            case 0xDA: return instr_cb_SET_3_D();
            case 0xDB: return instr_cb_SET_3_E();
            case 0xDC: return instr_cb_SET_3_H();
            case 0xDD: return instr_cb_SET_3_L();
            case 0xDE: return instr_cb_SET_3_mHL();
            case 0xDF: return instr_cb_SET_3_A();

            // --- Row 0xE_ ---
            case 0xE0: return instr_cb_SET_4_B();
            case 0xE1: return instr_cb_SET_4_C();
            case 0xE2: return instr_cb_SET_4_D();
            case 0xE3: return instr_cb_SET_4_E();
            case 0xE4: return instr_cb_SET_4_H();
            case 0xE5: return instr_cb_SET_4_L();
            case 0xE6: return instr_cb_SET_4_mHL();
            case 0xE7: return instr_cb_SET_4_A();
            case 0xE8: return instr_cb_SET_5_B();
            case 0xE9: return instr_cb_SET_5_C();
            case 0xEA: return instr_cb_SET_5_D();
            case 0xEB: return instr_cb_SET_5_E();
            case 0xEC: return instr_cb_SET_5_H();
            case 0xED: return instr_cb_SET_5_L();
            case 0xEE: return instr_cb_SET_5_mHL();
            case 0xEF: return instr_cb_SET_5_A();

            // --- Row 0xF_ ---
            case 0xF0: return instr_cb_SET_6_B();
            case 0xF1: return instr_cb_SET_6_C();
            case 0xF2: return instr_cb_SET_6_D();
            case 0xF3: return instr_cb_SET_6_E();
            case 0xF4: return instr_cb_SET_6_H();
            case 0xF5: return instr_cb_SET_6_L();
            case 0xF6: return instr_cb_SET_6_mHL();
            case 0xF7: return instr_cb_SET_6_A();
            case 0xF8: return instr_cb_SET_7_B();
            case 0xF9: return instr_cb_SET_7_C();
            case 0xFA: return instr_cb_SET_7_D();
            case 0xFB: return instr_cb_SET_7_E();
            case 0xFC: return instr_cb_SET_7_H();
            case 0xFD: return instr_cb_SET_7_L();
            case 0xFE: return instr_cb_SET_7_mHL();
            case 0xFF: return instr_cb_SET_7_A();

            default:
                return 0; // Should never be hit
        }
    }

    // Helper Functions:
    uint8_t CPU::INC(uint8_t &to) {
        // If the lower 4 bits are 1111 (0x0F), adding 1 will carry over.
        bool half_carry = (to & 0x0F) == 0x0F;
        to++;
        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(half_carry);
        return 4;
    }

    uint8_t CPU::DEC(uint8_t &to) {
        // If the lower 4 bits are 0000, subtracting 1 will borrow from bit 4.
        bool half_carry = (to & 0x0F) == 0x00;
        to--;
        set_flag_z(to == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        return 4;
    }

    uint8_t CPU::ADD(uint8_t &to, uint8_t value) {
        uint16_t result = to + value;

        bool half_carry = ((to & 0x0F) + (value & 0x0F)) > 0x0F;
        to = static_cast<uint8_t>(result);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(result > 0xFF);
        return 4;
    }

    uint8_t CPU::ADD_HL(uint16_t value) {
        bool half_carry = ((HL.word & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF;
        bool carry = (static_cast<uint32_t>(HL.word) + static_cast<uint32_t>(value)) > 0xFFFF;

        HL.word += value;

        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(carry);
        return 8;
    }

    uint8_t CPU::ADC(uint8_t &to, uint8_t value) {
        uint8_t carry = get_flag_c() ? 1 : 0;
        uint16_t result = to + value + carry;

        bool half_carry = ((to & 0x0F) + (value & 0x0F) + carry) > 0x0F;
        to = static_cast<uint8_t>(result);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(result > 0xFF);
        return 4;
    }

    uint8_t CPU::SUB(uint8_t &to, uint8_t value) {
        bool half_carry = (to & 0x0F) < (value & 0x0F);
        bool carry = to < value;
        to = static_cast<uint8_t>(to - value);

        set_flag_z(to == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        set_flag_c(carry);
        return 4;
    }

    uint8_t CPU::SBC(uint8_t &to, uint8_t value) {
        uint8_t carry_bit = get_flag_c() ? 1 : 0;

        uint16_t result = to - value - carry_bit;
        bool half_carry = (to & 0x0F) < ((value & 0x0F) + carry_bit);
        bool carry = static_cast<uint16_t>(to) < (static_cast<uint16_t>(value) + carry_bit);
        to = static_cast<uint8_t>(result);

        set_flag_z(to == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        set_flag_c(carry);
        return 4;
    }

    uint8_t CPU::AND_A(uint8_t value) {
        A &= value;

        set_flag_z(A == 0);
        set_flag_n(false);
        set_flag_h(true);
        set_flag_c(false);

        return 4;
    }

    uint8_t CPU::XOR_A(uint8_t value) {
        A ^= value;

        set_flag_z(A == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(false);

        return 4;
    }

    uint8_t CPU::OR_A(uint8_t value) {
        A |= value;

        set_flag_z(A == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(false);

        return 4;
    }

    uint8_t CPU::CP_A(uint8_t value) {
        bool half_carry = (A & 0x0F) < (value & 0x0F);
        bool carry = A < value;
        uint8_t result = static_cast<uint8_t>(A - value);

        set_flag_z(result == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        set_flag_c(carry);
        return 4;
    }

    uint16_t CPU::pop_16bit() {
        uint8_t lower = mmu->read(SP);
        uint8_t upper = mmu->read(SP + 1);

        SP += 2;

        return static_cast<uint16_t>((upper << 8) | lower);
    }

    void CPU::push_16bit(uint16_t value) {
        mmu->write(--SP, static_cast<uint8_t>(value >> 8));
        mmu->write(--SP, static_cast<uint8_t>(value & 0xFF));
    }

    inline uint16_t CPU::read_16bit(uint16_t address) {
        uint16_t lower = mmu->read(address);
        uint16_t higher = mmu->read(address + 1);
        return static_cast<uint16_t>((higher << 8) | lower);
    }

    // --- Row 0x0_ ---
    uint8_t CPU::instr_NOP() {             // 0x00
        // no operation
        return 4;
    }

    uint8_t CPU::instr_LD_BC_n16() {       // 0x01
        C = fetch_byte();
        B = fetch_byte();
        return 12;
    }

    uint8_t CPU::instr_LD_mBC_A() {        // 0x02
        mmu->write(BC.word, A);
        return 8;
    }

    uint8_t CPU::instr_INC_BC() {          // 0x03
        BC.word++;
        return 8;
    }

    uint8_t CPU::instr_INC_B() {           // 0x04
        return INC(B);
    }

    uint8_t CPU::instr_DEC_B() {           // 0x05
        return DEC(B);
    }

    uint8_t CPU::instr_LD_B_n8() {         // 0x06
        B = fetch_byte();
        return 8;
    }

    uint8_t CPU::instr_RLCA() {            // 0x07: Rotate Left Circular Accumulator
        uint8_t b7 = (A & 0x80) >> 7;
        A = static_cast<uint8_t>((A << 1) | b7);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
        return 4;
    }

    uint8_t CPU::instr_LD_mn16_SP() {      // 0x08
        uint16_t address = fetch_word();

        uint8_t sp_low = SP & 0xFF;             // top 8 bits
        uint8_t sp_high = (SP >> 8) & 0xFF;     // bottom 8 bits

        mmu->write(address, sp_low);
        mmu->write(address + 1, sp_high);
        return 20;
    }

    uint8_t CPU::instr_ADD_HL_BC() {       // 0x09
        return ADD_HL(BC.word);
    }

    uint8_t CPU::instr_LD_A_mBC() {        // 0x0A
        A = mmu->read(BC.word);
        return 8;
    }

    uint8_t CPU::instr_DEC_BC() {          // 0x0B
        BC.word--;
        return 8;
    }

    uint8_t CPU::instr_INC_C() {           // 0x0C
        return INC(C);
    }

    uint8_t CPU::instr_DEC_C() {           // 0x0D
        return DEC(C);
    }

    uint8_t CPU::instr_LD_C_n8() {         // 0x0E
        C = fetch_byte();
        return 8;
    }

    uint8_t CPU::instr_RRCA() {            // 0x0F: Rotate Right Circular Accumulator
        uint8_t b0 = static_cast<uint8_t>((A & 0x01) << 7);
        A = b0 | (A >> 1);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
        return 4;
    }


    // --- Row 0x1_ ---
    uint8_t CPU::instr_STOP() {            // 0x10
        // TODO: Implement actual 'is_stopped' CPU state flag to halt execution until a Joypad interrupt fires.
        fetch_byte(); // Consume the 0x00 byte
        return 4;
    }
    uint8_t CPU::instr_LD_DE_n16() {       // 0x11
        E = fetch_byte();
        D = fetch_byte();
        return 12;
    }
    uint8_t CPU::instr_LD_mDE_A() {        // 0x12
        mmu->write(DE.word, A);
        return 8;
    }
    uint8_t CPU::instr_INC_DE() {          // 0x13
        DE.word++;
        return 8;
    }
    uint8_t CPU::instr_INC_D() {           // 0x14
        return INC(D);
    }
    uint8_t CPU::instr_DEC_D() {           // 0x15
        return DEC(D);
    }
    uint8_t CPU::instr_LD_D_n8() {         // 0x16
        D = fetch_byte();
        return 8;
    }
    uint8_t CPU::instr_RLA() {             // 0x17
        uint8_t b7 = (A & 0x80) >> 7;
        A = static_cast<uint8_t>((A << 1) | static_cast<uint8_t>(get_flag_c()));

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
        return 4;
    }
    uint8_t CPU::instr_JR_n8() {           // 0x18
        int8_t offset = fetch_byte();
        PC += offset;
        return 12;
    }
    uint8_t CPU::instr_ADD_HL_DE() {       // 0x19
        return ADD_HL(DE.word);
    }
    uint8_t CPU::instr_LD_A_mDE() {        // 0x1A
        A = mmu->read(DE.word);
        return 8;
    }
    uint8_t CPU::instr_DEC_DE() {          // 0x1B
        DE.word--;
        return 8;
    }
    uint8_t CPU::instr_INC_E() {           // 0x1C
        return INC(E);
    }
    uint8_t CPU::instr_DEC_E() {           // 0x1D
        return DEC(E);
    }
    uint8_t CPU::instr_LD_E_n8() {         // 0x1E
        E = fetch_byte();
        return 8;
    }
    uint8_t CPU::instr_RRA() {             // 0x1F
        bool b0 = (A & 0x01) != 0;
        uint8_t old_carry = get_flag_c() ? 1 : 0;
        A = static_cast<uint8_t>(old_carry << 7) | (A >> 1);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0);
        return 4;
    }

    // --- Row 0x2_ ---
    uint8_t CPU::instr_JR_NZ_n8() {        // 0x20
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (!get_flag_z()) {
            PC += offset;
            return 12;
        }
        return 8;
    }
    uint8_t CPU::instr_LD_HL_n16() {        // 0x21
        L = fetch_byte();
        H = fetch_byte();
        return 12;
    }
    uint8_t CPU::instr_LD_mHL_plus_A() {    // 0x22
        mmu->write(HL.word++, A);
        return 8;
    }
    uint8_t CPU::instr_INC_HL() {           // 0x23
        HL.word++;
        return 8;
    }
    uint8_t CPU::instr_INC_H() {            // 0x24
        return INC(H);
    }
    uint8_t CPU::instr_DEC_H() {            // 0x25
        return DEC(H);
    }
    uint8_t CPU::instr_LD_H_n8() {          // 0x26
        H = fetch_byte();
        return 8;
    }
    uint8_t CPU::instr_DAA() {              // 0x27: Decimal Adjust Accumulator
        /* We adjust the binary representation of numbers to the decimal representation*/

        uint8_t correction = 0;
        bool set_c = false;

        // If we previously subtracted (N=1), we only adjust if H was set.
        // If we previously added (N=0), we adjust if H was set OR if the lower nibble is > 9.
        if (get_flag_h() || (!get_flag_n() && (A & 0x0F) > 0x09)) {
            correction |= 0x06;
        }

        // If we previously subtracted (N=1), we only adjust if C was set.
        // If we previously added (N=0), we adjust if C was set OR if the full value is > 0x99.
        if (get_flag_c() || (!get_flag_n() && A > 0x99)) {
            correction |= 0x60;
            set_c = true; // This will become our new Carry flag
        }

        if (get_flag_n()) {
            A -= correction;
        } else {
            A += correction;
        }

        set_flag_z(A == 0);
        set_flag_h(false);
        set_flag_c(set_c);

        return 4;
    }
    uint8_t CPU::instr_JR_Z_n8() {          // 0x28
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (get_flag_z()) {
            PC += offset;
            return 12;
        }
        return 8;
    }
    uint8_t CPU::instr_ADD_HL_HL() {        // 0x29
        return ADD_HL(HL.word);
    }
    uint8_t CPU::instr_LD_A_mHL_plus() {    // 0x2A
        A = mmu->read(HL.word++);
        return 8;
    }
    uint8_t CPU::instr_DEC_HL() {           // 0x2B
        HL.word--;
        return 8;
    }
    uint8_t CPU::instr_INC_L() {            // 0x2C
        return INC(L);
    }
    uint8_t CPU::instr_DEC_L() {            // 0x2D
        return DEC(L);
    }
    uint8_t CPU::instr_LD_L_n8() {          // 0x2E
        L = fetch_byte();
        return 8;
    }
    uint8_t CPU::instr_CPL() {              // 0x2F
        A = static_cast<uint8_t>(~A);

        set_flag_n(true);
        set_flag_h(true);

        return 4;
    }

    // --- Row 0x3_ ---
    uint8_t CPU::instr_JR_NC_n8() {         // 0x30
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (!get_flag_c()) {
            PC += offset;
            return 12;
        }
        return 8;
    }
    uint8_t CPU::instr_LD_SP_n16() {        // 0x31
        SP = fetch_word();
        return 12;
    }
    uint8_t CPU::instr_LD_mHL_minus_A() {   // 0x32
        mmu->write(HL.word--, A);
        return 8;
    }
    uint8_t CPU::instr_INC_SP() {           // 0x33
        SP++;
        return 8;
    }
    uint8_t CPU::instr_INC_mHL() {          // 0x34
        uint8_t value = mmu->read(HL.word);
        INC(value);
        mmu->write(HL.word, value);

        return 12;
    }
    uint8_t CPU::instr_DEC_mHL() {          // 0x35
        uint8_t value = mmu->read(HL.word);
        DEC(value);
        mmu->write(HL.word, value);

        return 12;
    }
    uint8_t CPU::instr_LD_mHL_n8() {        // 0x36
        mmu->write(HL.word, fetch_byte());
        return 12;
    }
    uint8_t CPU::instr_SCF() {              // 0x37
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(true);

        return 4;
    }
    uint8_t CPU::instr_JR_C_n8() {          // 0x38
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (get_flag_c()) {
            PC += offset;
            return 12;
        }
        return 8;
    }
    uint8_t CPU::instr_ADD_HL_SP() {        // 0x39
        return ADD_HL(SP);
    }
    uint8_t CPU::instr_LD_A_mHL_minus() {   // 0x3A
        A = mmu->read(HL.word--);
        return 8;
    }
    uint8_t CPU::instr_DEC_SP() {           // 0x3B
        SP--;
        return 8;
    }
    uint8_t CPU::instr_INC_A() {            // 0x3C
        return INC(A);
    }
    uint8_t CPU::instr_DEC_A() {            // 0x3D
        return DEC(A);
    }
    uint8_t CPU::instr_LD_A_n8() {          // 0x3E
        A = fetch_byte();
        return 8;
    }
    uint8_t CPU::instr_CCF() {              // 0x3F
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(!get_flag_c());
        return 4;
    }

    // --- Row 0x4_ ---
    uint8_t CPU::instr_LD_B_B() {        return 4; }                    // 0x40
    uint8_t CPU::instr_LD_B_C() { B = C; return 4; }                    // 0x41
    uint8_t CPU::instr_LD_B_D() { B = D; return 4; }                    // 0x42
    uint8_t CPU::instr_LD_B_E() { B = E; return 4; }                    // 0x43
    uint8_t CPU::instr_LD_B_H() { B = H; return 4; }                    // 0x44
    uint8_t CPU::instr_LD_B_L() { B = L; return 4; }                    // 0x45
    uint8_t CPU::instr_LD_B_mHL() { B = mmu->read(HL.word); return 8; } // 0x46
    uint8_t CPU::instr_LD_B_A() { B = A; return 4; }                    // 0x47
    uint8_t CPU::instr_LD_C_B() { C = B; return 4; }                    // 0x48
    uint8_t CPU::instr_LD_C_C() {        return 4; }                    // 0x49
    uint8_t CPU::instr_LD_C_D() { C = D; return 4; }                    // 0x4A
    uint8_t CPU::instr_LD_C_E() { C = E; return 4; }                    // 0x4B
    uint8_t CPU::instr_LD_C_H() { C = H; return 4; }                    // 0x4C
    uint8_t CPU::instr_LD_C_L() { C = L; return 4; }                    // 0x4D
    uint8_t CPU::instr_LD_C_mHL() { C = mmu->read(HL.word); return 8; } // 0x4E
    uint8_t CPU::instr_LD_C_A() { C = A; return 4; }                    // 0x4F

    // --- Row 0x5_ ---
    uint8_t CPU::instr_LD_D_B() { D = B; return 4; }                    // 0x50
    uint8_t CPU::instr_LD_D_C() { D = C; return 4; }                    // 0x51
    uint8_t CPU::instr_LD_D_D() {        return 4; }                    // 0x52
    uint8_t CPU::instr_LD_D_E() { D = E; return 4; }                    // 0x53
    uint8_t CPU::instr_LD_D_H() { D = H; return 4; }                    // 0x54
    uint8_t CPU::instr_LD_D_L() { D = L; return 4; }                    // 0x55
    uint8_t CPU::instr_LD_D_mHL() { D = mmu->read(HL.word); return 8; } // 0x56
    uint8_t CPU::instr_LD_D_A() { D = A; return 4; }                    // 0x57
    uint8_t CPU::instr_LD_E_B() { E = B; return 4; }                    // 0x58
    uint8_t CPU::instr_LD_E_C() { E = C; return 4; }                    // 0x59
    uint8_t CPU::instr_LD_E_D() { E = D; return 4; }                    // 0x5A
    uint8_t CPU::instr_LD_E_E() {        return 4; }                    // 0x5B
    uint8_t CPU::instr_LD_E_H() { E = H; return 4; }                    // 0x5C
    uint8_t CPU::instr_LD_E_L() { E = L; return 4; }                    // 0x5D
    uint8_t CPU::instr_LD_E_mHL() { E = mmu->read(HL.word); return 8; } // 0x5E
    uint8_t CPU::instr_LD_E_A() { E = A; return 4; }                    // 0x5F

    // --- Row 0x6_ ---
    uint8_t CPU::instr_LD_H_B() { H = B; return 4; }                    // 0x60
    uint8_t CPU::instr_LD_H_C() { H = C; return 4; }                    // 0x61
    uint8_t CPU::instr_LD_H_D() { H = D; return 4; }                    // 0x62
    uint8_t CPU::instr_LD_H_E() { H = E; return 4; }                    // 0x63
    uint8_t CPU::instr_LD_H_H() {        return 4; }                    // 0x64
    uint8_t CPU::instr_LD_H_L() { H = L; return 4; }                    // 0x65
    uint8_t CPU::instr_LD_H_mHL() { H = mmu->read(HL.word); return 8; } // 0x66
    uint8_t CPU::instr_LD_H_A() { H = A; return 4; }                    // 0x67
    uint8_t CPU::instr_LD_L_B() { L = B; return 4; }                    // 0x68
    uint8_t CPU::instr_LD_L_C() { L = C; return 4; }                    // 0x69
    uint8_t CPU::instr_LD_L_D() { L = D; return 4; }                    // 0x6A
    uint8_t CPU::instr_LD_L_E() { L = E; return 4; }                    // 0x6B
    uint8_t CPU::instr_LD_L_H() { L = H; return 4; }                    // 0x6C
    uint8_t CPU::instr_LD_L_L() {        return 4; }                    // 0x6D
    uint8_t CPU::instr_LD_L_mHL() { L = mmu->read(HL.word); return 8; } // 0x6E
    uint8_t CPU::instr_LD_L_A() { L = A; return 4; }                    // 0x6F

    // --- Row 0x7_ ---
    uint8_t CPU::instr_LD_mHL_B() { mmu->write(HL.word, B); return 8; } // 0x70
    uint8_t CPU::instr_LD_mHL_C() { mmu->write(HL.word, C); return 8; } // 0x71
    uint8_t CPU::instr_LD_mHL_D() { mmu->write(HL.word, D); return 8; } // 0x72
    uint8_t CPU::instr_LD_mHL_E() { mmu->write(HL.word, E); return 8; } // 0x73
    uint8_t CPU::instr_LD_mHL_H() { mmu->write(HL.word, H); return 8; } // 0x74
    uint8_t CPU::instr_LD_mHL_L() { mmu->write(HL.word, L); return 8; } // 0x75
    uint8_t CPU::instr_HALT() {
        // TODO: Ensure CPU class has a `bool halted` or similar state variable.
        // halted = true;
        return 4;
    }                                                                   // 0x76
    uint8_t CPU::instr_LD_mHL_A() { mmu->write(HL.word, A); return 8; } // 0x77
    uint8_t CPU::instr_LD_A_B() { A = B; return 4; }                    // 0x78
    uint8_t CPU::instr_LD_A_C() { A = C; return 4; }                    // 0x79
    uint8_t CPU::instr_LD_A_D() { A = D; return 4; }                    // 0x7A
    uint8_t CPU::instr_LD_A_E() { A = E; return 4; }                    // 0x7B
    uint8_t CPU::instr_LD_A_H() { A = H; return 4; }                    // 0x7C
    uint8_t CPU::instr_LD_A_L() { A = L; return 4; }                    // 0x7D
    uint8_t CPU::instr_LD_A_mHL() { A = mmu->read(HL.word); return 8; } // 0x7E
    uint8_t CPU::instr_LD_A_A() {        return 4; }                    // 0x7F

    // --- Row 0x8_ ---
    uint8_t CPU::instr_ADD_A_B() { return ADD(A, B); }                  // 0x80
    uint8_t CPU::instr_ADD_A_C() { return ADD(A, C); }                  // 0x81
    uint8_t CPU::instr_ADD_A_D() { return ADD(A, D); }                  // 0x82
    uint8_t CPU::instr_ADD_A_E() { return ADD(A, E); }                  // 0x83
    uint8_t CPU::instr_ADD_A_H() { return ADD(A, H); }                  // 0x84
    uint8_t CPU::instr_ADD_A_L() { return ADD(A, L); }                  // 0x85
    uint8_t CPU::instr_ADD_A_mHL() {                                               // 0x86
        ADD(A, mmu->read(HL.word));
        return 8;
    }
    uint8_t CPU::instr_ADD_A_A() { return ADD(A, A); }                  // 0x87
    uint8_t CPU::instr_ADC_A_B() { return ADC(A, B); }                  // 0x88
    uint8_t CPU::instr_ADC_A_C() { return ADC(A, C); }                  // 0x89
    uint8_t CPU::instr_ADC_A_D() { return ADC(A, D); }                  // 0x8A
    uint8_t CPU::instr_ADC_A_E() { return ADC(A, E); }                  // 0x8B
    uint8_t CPU::instr_ADC_A_H() { return ADC(A, H); }                  // 0x8C
    uint8_t CPU::instr_ADC_A_L() { return ADC(A, L); }                  // 0x8D
    uint8_t CPU::instr_ADC_A_mHL() {                                               // 0x8E
        ADC(A, mmu->read(HL.word));
        return 8;
    }
    uint8_t CPU::instr_ADC_A_A() { return ADC(A, A); }                  // 0x8F

    // --- Row 0x9_ ---
    uint8_t CPU::instr_SUB_A_B() { return SUB(A, B); }                    // 0x90
    uint8_t CPU::instr_SUB_A_C() { return SUB(A, C); }                    // 0x91
    uint8_t CPU::instr_SUB_A_D() { return SUB(A, D); }                    // 0x92
    uint8_t CPU::instr_SUB_A_E() { return SUB(A, E); }                    // 0x93
    uint8_t CPU::instr_SUB_A_H() { return SUB(A, H); }                    // 0x94
    uint8_t CPU::instr_SUB_A_L() { return SUB(A, L); }                    // 0x95
    uint8_t CPU::instr_SUB_A_mHL() {                                                 // 0x96
        SUB(A, mmu->read(HL.word));
        return 8;
    }
    uint8_t CPU::instr_SUB_A_A() { return SUB(A, A); }                  // 0x97
    uint8_t CPU::instr_SBC_A_B() { return SBC(A, B); }                  // 0x98
    uint8_t CPU::instr_SBC_A_C() { return SBC(A, C); }                  // 0x99
    uint8_t CPU::instr_SBC_A_D() { return SBC(A, D); }                  // 0x9A
    uint8_t CPU::instr_SBC_A_E() { return SBC(A, E); }                  // 0x9B
    uint8_t CPU::instr_SBC_A_H() { return SBC(A, H); }                  // 0x9C
    uint8_t CPU::instr_SBC_A_L() { return SBC(A, L); }                  // 0x9D
    uint8_t CPU::instr_SBC_A_mHL() {
        SBC(A, mmu->read(HL.word));
        return 8;
    }                                                                               // 0x9E
    uint8_t CPU::instr_SBC_A_A() { return SBC(A, A); }                  // 0x9F

    // --- Row 0xA_ ---
    uint8_t CPU::instr_AND_A_B() { return AND_A(B); }              // 0xA0
    uint8_t CPU::instr_AND_A_C() { return AND_A(C); }              // 0xA1
    uint8_t CPU::instr_AND_A_D() { return AND_A(D); }              // 0xA2
    uint8_t CPU::instr_AND_A_E() { return AND_A(E); }              // 0xA3
    uint8_t CPU::instr_AND_A_H() { return AND_A(H); }              // 0xA4
    uint8_t CPU::instr_AND_A_L() { return AND_A(L); }              // 0xA5
    uint8_t CPU::instr_AND_A_mHL() {
        AND_A(mmu->read(HL.word));
        return 8;
    }                                                              // 0xA6
    uint8_t CPU::instr_AND_A_A() { return AND_A(A); }              // 0xA7

    uint8_t CPU::instr_XOR_A_B() { return XOR_A(B); }              // 0xA8
    uint8_t CPU::instr_XOR_A_C() { return XOR_A(C); }              // 0xA9
    uint8_t CPU::instr_XOR_A_D() { return XOR_A(D); }              // 0xAA
    uint8_t CPU::instr_XOR_A_E() { return XOR_A(E); }              // 0xAB
    uint8_t CPU::instr_XOR_A_H() { return XOR_A(H); }              // 0xAC
    uint8_t CPU::instr_XOR_A_L() { return XOR_A(L); }              // 0xAD
    uint8_t CPU::instr_XOR_A_mHL() {
        XOR_A(mmu->read(HL.word));
        return 8;
    }                                                              // 0xAE
    uint8_t CPU::instr_XOR_A_A() { return XOR_A(A); }              // 0xAF

    // --- Row 0xB_ ---
    uint8_t CPU::instr_OR_A_B() { return OR_A(B); }                // 0xB0
    uint8_t CPU::instr_OR_A_C() { return OR_A(C); }                // 0xB1
    uint8_t CPU::instr_OR_A_D() { return OR_A(D); }                // 0xB2
    uint8_t CPU::instr_OR_A_E() { return OR_A(E); }                // 0xB3
    uint8_t CPU::instr_OR_A_H() { return OR_A(H); }                // 0xB4
    uint8_t CPU::instr_OR_A_L() { return OR_A(L); }                // 0xB5
    uint8_t CPU::instr_OR_A_mHL() {
        OR_A(mmu->read(HL.word));
        return 8;
    }                                                              // 0xB6
    uint8_t CPU::instr_OR_A_A() { return OR_A(A); }                // 0xB7

    uint8_t CPU::instr_CP_A_B() { return CP_A(B); }                // 0xB8
    uint8_t CPU::instr_CP_A_C() { return CP_A(C); }                // 0xB9
    uint8_t CPU::instr_CP_A_D() { return CP_A(D); }                // 0xBA
    uint8_t CPU::instr_CP_A_E() { return CP_A(E); }                // 0xBB
    uint8_t CPU::instr_CP_A_H() { return CP_A(H); }                // 0xBC
    uint8_t CPU::instr_CP_A_L() { return CP_A(L); }                // 0xBD
    uint8_t CPU::instr_CP_A_mHL() {
        CP_A(mmu->read(HL.word));
        return 8;
    }                                                              // 0xBE
    uint8_t CPU::instr_CP_A_A() { return CP_A(A); }                // 0xBF

    // --- Row 0xC_ ---
    uint8_t CPU::instr_RET_NZ() {           // 0xC0
        if (!get_flag_z()) {
            PC = pop_16bit();
            return 20;
        }
        return 8;
    }
    uint8_t CPU::instr_POP_BC() {           // 0xC1
        BC.word = pop_16bit();
        return 12;
    }
    uint8_t CPU::instr_JP_NZ_n16() {        // 0xC2
        uint16_t address = fetch_word();
        if (!get_flag_z()) {
            PC = address; 
            return 16;
        }
        return 12;
    }
    uint8_t CPU::instr_JP_n16() {           // 0xC3
        uint16_t address = fetch_word();
        PC = address;
        return 16;
    }
    uint8_t CPU::instr_CALL_NZ_n16() {      // 0xC4
        uint16_t address = fetch_word();
        if (!get_flag_z()) {
            push_16bit(PC);
            PC = address;

            return 24;
        }

        return 12;
    }
    uint8_t CPU::instr_PUSH_BC() {              // 0xC5
        push_16bit(BC.word);
        return 16;
    }
    uint8_t CPU::instr_ADD_A_n8() {             // 0xC6
        ADD(A, fetch_byte());
        return 8;
    }
    uint8_t CPU::instr_RST_00H() {              // 0xC7
        push_16bit(PC);
        PC = 0x0000;

        return 16;
    }
    uint8_t CPU::instr_RET_Z() {                // 0xC8
        if (get_flag_z()) {
            PC = pop_16bit();
            return 20;
        }
        return 8;
    }
    uint8_t CPU::instr_RET() {                  // 0xC9
        PC = pop_16bit();
        return 16;
    }
    uint8_t CPU::instr_JP_Z_n16() {             // 0xCA
        uint16_t address = fetch_word();
        if (get_flag_z()) {
            PC = address;
            return 16;
        }
        return 12;
    }
    uint8_t CPU::instr_PREFIX_CB() {            // 0xCB
        return execute_cb();
    }
    uint8_t CPU::instr_CALL_Z_n16() {           // 0xCC
        uint16_t address = fetch_word();
        if (get_flag_z()) {
            push_16bit(PC);
            PC = address;

            return 24;
        }

        return 12;
    }
    uint8_t CPU::instr_CALL_n16() {             // 0xCD
        uint16_t address = fetch_word();
        push_16bit(PC);
        PC = address;
        return 24;
    }
    uint8_t CPU::instr_ADC_A_n8() {             // 0xCE
        return ADC(A, fetch_byte());
    }
    uint8_t CPU::instr_RST_08H() {              // 0xCF
        push_16bit(PC);
        PC = 0x0008;

        return 16;
    }

    // --- Row 0xD_ ---
    uint8_t CPU::instr_RET_NC() {               // 0xD0
        if (!get_flag_c()) {
            PC = pop_16bit();
            return 20;
        }
        return 8;
    }
    uint8_t CPU::instr_POP_DE() {               // 0xD1
        DE.word = pop_16bit();
        return 12;
    }
    uint8_t CPU::instr_JP_NC_n16() {            // 0xD2
        uint16_t address = fetch_word();
        if (!get_flag_c()) {
            PC = address;
            return 16;
        }
        return 12;
    }
    uint8_t CPU::instr_UNUSED_D3() { return 0; }// 0xD3
    uint8_t CPU::instr_CALL_NC_n16() {          // 0xD4
        uint16_t address = fetch_word();
        if (!get_flag_c()) {
            push_16bit(PC);
            PC = address;

            return 24;
        }

        return 12;
    }
    uint8_t CPU::instr_PUSH_DE() {              // 0xD5
        push_16bit(DE.word);
        return 16;
    }
    uint8_t CPU::instr_SUB_A_n8() {             // 0xD6
        SUB(A, fetch_byte());
        return 8;
    }
    uint8_t CPU::instr_RST_10H() {              // 0xD7
        push_16bit(PC);
        PC = 0x0010;

        return 16;
    }
    uint8_t CPU::instr_RET_C() {                // 0xD8
        if (get_flag_c()) {
            PC = pop_16bit();
            return 20;
        }
        return 8;
    }
    uint8_t CPU::instr_RETI() {                 // 0xD9
        IME = true;
        uint16_t target_address = pop_16bit();
        PC = target_address;
        return 16;
    }
    uint8_t CPU::instr_JP_C_n16() {             // 0xDA
        uint16_t address = fetch_word();
        if (get_flag_c()) {
            PC = address;
            return 16;
        }
        return 12;
    }
    uint8_t CPU::instr_UNUSED_DB() { return 0;} // 0xDB
    uint8_t CPU::instr_CALL_C_n16() {           // 0xDC
        uint16_t address = fetch_word();
        if (get_flag_c()) {
            push_16bit(PC);
            PC = address;

            return 24;
        }

        return 12;
    }
    uint8_t CPU::instr_UNUSED_DD() { return 0;} // 0xDD
    uint8_t CPU::instr_SBC_A_n8() {             // 0xDE
        SBC(A, fetch_byte());
        return 8;
    }
    uint8_t CPU::instr_RST_18H() {              // 0xDF
        push_16bit(PC);
        PC = 0x0018;
        return 16;
    }

    // --- Row 0xE_ ---
    uint8_t CPU::instr_LDH_mn8_A() {            // 0xE0
        uint8_t offset = fetch_byte();

        mmu->write(static_cast<uint16_t>(0xFF00 | offset), A);
        return 12;
    }
    uint8_t CPU::instr_POP_HL() {               // 0xE1
        HL.word = pop_16bit();
        return 12;
    }
    uint8_t CPU::instr_LD_mC_A() {              // 0xE2
        mmu->write(0xFF00 | C, A);
        return 8;
    }
    uint8_t CPU::instr_UNUSED_E3() { return 0;}          // 0xE3
    uint8_t CPU::instr_UNUSED_E4() { return 0;}          // 0xE4
    uint8_t CPU::instr_PUSH_HL() {              // 0xE5
        push_16bit(HL.word);
        return 16;
    }
    uint8_t CPU::instr_AND_A_n8() {             // 0xE6
        AND_A(fetch_byte());
        return 8;
    }
    uint8_t CPU::instr_RST_20H() {              // 0xE7
        push_16bit(PC);
        PC = 0x0020;

        return 16;
    }
    uint8_t CPU::instr_ADD_SP_e8() {            // 0xE8
        int8_t value = static_cast<int8_t>(fetch_byte());

        bool half_carry = ((SP & 0x0F) + (value & 0x0F)) > 0x0F;
        bool carry = ((SP & 0xFF) + (value & 0xFF)) > 0xFF;

        SP += value;

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(carry);
        return 16;
    }
    uint8_t CPU::instr_JP_HL() {                // 0xE9
        PC = HL.word;

        return 4;
    }
    uint8_t CPU::instr_LD_mn16_A() {            // 0xEA
        uint16_t address = fetch_word();

        mmu->write(address, A);

        return 16;
    }
    uint8_t CPU::instr_UNUSED_EB() { return 0; } // 0xEB
    uint8_t CPU::instr_UNUSED_EC() { return 0; } // 0xEC
    uint8_t CPU::instr_UNUSED_ED() { return 0; } // 0xED
    uint8_t CPU::instr_XOR_A_n8() {             // 0xEE
        return XOR_A(fetch_byte());
    }
    uint8_t CPU::instr_RST_28H() {              // 0xEF
        push_16bit(PC);
        PC = 0x0028;

        return 16;
    }

    // --- Row 0xF_ ---
    uint8_t CPU::instr_LDH_A_mn8() {            // 0xF0
        uint8_t offset = fetch_byte();

        A = mmu->read(static_cast<uint16_t>(0xFF00 | offset));
        return 12;
    }
    uint8_t CPU::instr_POP_AF() {               // 0xF1
        AF.word = pop_16bit() & 0xFFF0;

        return 12;
    }
    uint8_t CPU::instr_LD_A_mC() {              // 0xF2
        A = mmu->read(static_cast<uint16_t>(0xFF00 | C));
        return 8;
    }
    uint8_t CPU::instr_DI() {                   // 0xF3
        EI_delay = -1;
        IME = false;
        return 4;
    }
    uint8_t CPU::instr_UNUSED_F4() { return 0; }// 0xF4
    uint8_t CPU::instr_PUSH_AF() {              // 0xF5
        push_16bit(AF.word);
        return 16;
    }
    uint8_t CPU::instr_OR_A_n8() {              // 0xF6
        OR_A(fetch_byte());
        return 8;
    }
    uint8_t CPU::instr_RST_30H() {              // 0xF7
        push_16bit(PC);
        PC = 0x0030;

        return 16;
    }
    uint8_t CPU::instr_LD_HL_SP_plus_e8() {     // 0xF8
        int8_t offset = static_cast<int8_t>(fetch_byte());

        bool half_carry = ((SP & 0x0F) + (offset & 0x0F)) > 0x0F;
        bool carry = ((SP & 0xFF) + (offset & 0xFF)) > 0xFF;

        HL.word = static_cast<uint16_t>(SP + offset);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(carry);
        return 12;
    }
    uint8_t CPU::instr_LD_SP_HL() {             // 0xF9
        SP = HL.word;
        return 8;
    }
    uint8_t CPU::instr_LD_A_mn16() {            // 0xFA
        uint16_t address = fetch_word();
        A = mmu->read(address);

        return 16;
    }
    uint8_t CPU::instr_EI() {                   // 0xFB
        EI_delay = 1;
        return 4;
    }
    uint8_t CPU::instr_UNUSED_FC() { return 0; }// 0xFC
    uint8_t CPU::instr_UNUSED_FD() { return 0; }// 0xFD
    uint8_t CPU::instr_CP_A_n8() {              // 0xFE
        return CP_A(fetch_byte());
    }
    uint8_t CPU::instr_RST_38H() {              // 0xFF
        push_16bit(PC);
        PC = 0x0038;

        return 16;
    }

    // =========================================================================
    // PREFIX CB OPCODES IMPLEMENTATION (0xCB 0x00 - 0xCB 0xFF)
    // =========================================================================

    uint8_t CPU::RLC(uint8_t& to) {
        uint8_t b7 = (to & 0x80) >> 7;
        to = static_cast<uint8_t>((to << 1) | b7);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
        return 8;
    }

    uint8_t CPU::RRC(uint8_t& to) {
        uint8_t b0 = static_cast<uint8_t>((to & 0x01) << 7);
        to = b0 | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
        return 8;
    }

    uint8_t CPU::RL(uint8_t& to) {
        uint8_t b7 = (to & 0x80) >> 7;
        to = static_cast<uint8_t>((to << 1) | static_cast<uint8_t>(get_flag_c()));

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
        return 8;
    }

    uint8_t CPU::RR(uint8_t& to) {
        bool b0 = (to & 0x01) != 0;
        uint8_t old_carry = get_flag_c() ? 1 : 0;
        to = static_cast<uint8_t>(old_carry << 7) | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0);
        return 8;
    }

    uint8_t CPU::SLA(uint8_t& to) {
        uint8_t b7 = (to & 0x80) >> 7;
        to = static_cast<uint8_t>((to << 1) | static_cast<uint8_t>(0));

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
        return 8;
    }

    uint8_t CPU::SRA(uint8_t& to) {
        uint8_t b7 = (to & 0x80);
        uint8_t b0 = static_cast<uint8_t>((to & 0x01) << 7);
        to = b7 | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
        return 8;
    }

    uint8_t CPU::SRL(uint8_t& to) {
        uint8_t b0 = static_cast<uint8_t>((to & 0x01) << 7);
        to = static_cast<uint8_t>(0) | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
        return 8;
    }

    uint8_t CPU::SWAP(uint8_t& to) {
        uint8_t lower = to & 0xF0;
        uint8_t higher = to & 0x0F;

        to = static_cast<uint8_t>((higher >> 4) | (lower << 4));

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(false);
        return 8;
    }

    uint8_t CPU::BIT(uint8_t bit, uint8_t &reg) {
        bool is_set = (reg & (1 << bit)) != 0;

        set_flag_z(!is_set);
        set_flag_n(false);
        set_flag_h(true);

        return 8;
    }

    uint8_t CPU::RES(uint8_t bit, uint8_t &reg) {
        reg &= ~(1 << bit);

        return 8;
    }

    uint8_t CPU::SET(uint8_t bit, uint8_t &reg) {
        reg |= (1 << bit);

        return 8;
    }

    // =========================================================================
    // PREFIX CB OPCODES IMPLEMENTATION (0xCB 0x00 - 0xCB 0xFF)
    // =========================================================================

    // --- Row 0x0_ (RLC & RRC) ---
    uint8_t CPU::instr_cb_RLC_B() { RLC(B); return 8; }
    uint8_t CPU::instr_cb_RLC_C() { RLC(C); return 8; }
    uint8_t CPU::instr_cb_RLC_D() { RLC(D); return 8; }
    uint8_t CPU::instr_cb_RLC_E() { RLC(E); return 8; }
    uint8_t CPU::instr_cb_RLC_H() { RLC(H); return 8; }
    uint8_t CPU::instr_cb_RLC_L() { RLC(L); return 8; }
    uint8_t CPU::instr_cb_RLC_mHL() {
        uint8_t v = mmu->read(HL.word);
        RLC(v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RLC_A() { RLC(A); return 8; }
    uint8_t CPU::instr_cb_RRC_B() { RRC(B); return 8; }
    uint8_t CPU::instr_cb_RRC_C() { RRC(C); return 8; }
    uint8_t CPU::instr_cb_RRC_D() { RRC(D); return 8; }
    uint8_t CPU::instr_cb_RRC_E() { RRC(E); return 8; }
    uint8_t CPU::instr_cb_RRC_H() { RRC(H); return 8; }
    uint8_t CPU::instr_cb_RRC_L() { RRC(L); return 8; }
    uint8_t CPU::instr_cb_RRC_mHL() {
        uint8_t v = mmu->read(HL.word);
        RRC(v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RRC_A() { RRC(A); return 8; }

    // --- Row 0x1_ (RL & RR) ---
    uint8_t CPU::instr_cb_RL_B() { RL(B); return 8; }
    uint8_t CPU::instr_cb_RL_C() { RL(C); return 8; }
    uint8_t CPU::instr_cb_RL_D() { RL(D); return 8; }
    uint8_t CPU::instr_cb_RL_E() { RL(E); return 8; }
    uint8_t CPU::instr_cb_RL_H() { RL(H); return 8; }
    uint8_t CPU::instr_cb_RL_L() { RL(L); return 8; }
    uint8_t CPU::instr_cb_RL_mHL() {
        uint8_t v = mmu->read(HL.word);
        RL(v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RL_A() { RL(A); return 8; }
    uint8_t CPU::instr_cb_RR_B() { RR(B); return 8; }
    uint8_t CPU::instr_cb_RR_C() { RR(C); return 8; }
    uint8_t CPU::instr_cb_RR_D() { RR(D); return 8; }
    uint8_t CPU::instr_cb_RR_E() { RR(E); return 8; }
    uint8_t CPU::instr_cb_RR_H() { RR(H); return 8; }
    uint8_t CPU::instr_cb_RR_L() { RR(L); return 8; }
    uint8_t CPU::instr_cb_RR_mHL() {
        uint8_t v = mmu->read(HL.word);
        RR(v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RR_A() { RR(A); return 8; }

    // --- Row 0x2_ (SLA & SRA) ---
    uint8_t CPU::instr_cb_SLA_B() { SLA(B); return 8; }
    uint8_t CPU::instr_cb_SLA_C() { SLA(C); return 8; }
    uint8_t CPU::instr_cb_SLA_D() { SLA(D); return 8; }
    uint8_t CPU::instr_cb_SLA_E() { SLA(E); return 8; }
    uint8_t CPU::instr_cb_SLA_H() { SLA(H); return 8; }
    uint8_t CPU::instr_cb_SLA_L() { SLA(L); return 8; }
    uint8_t CPU::instr_cb_SLA_mHL() {
         uint8_t v = mmu->read(HL.word);
         SLA(v);
         mmu->write(HL.word, v);
         return 16;
    }
    uint8_t CPU::instr_cb_SLA_A() { SLA(A); return 8; }
    uint8_t CPU::instr_cb_SRA_B() { SRA(B); return 8; }
    uint8_t CPU::instr_cb_SRA_C() { SRA(C); return 8; }
    uint8_t CPU::instr_cb_SRA_D() { SRA(D); return 8; }
    uint8_t CPU::instr_cb_SRA_E() { SRA(E); return 8; }
    uint8_t CPU::instr_cb_SRA_H() { SRA(H); return 8; }
    uint8_t CPU::instr_cb_SRA_L() { SRA(L); return 8; }
    uint8_t CPU::instr_cb_SRA_mHL() {
         uint8_t v = mmu->read(HL.word);
         SRA(v);
         mmu->write(HL.word, v);
         return 16;
    }
    uint8_t CPU::instr_cb_SRA_A() { SRA(A); return 8; }

    // --- Row 0x3_ (SWAP & SRL) ---
    uint8_t CPU::instr_cb_SWAP_B() { SWAP(B); return 8; }
    uint8_t CPU::instr_cb_SWAP_C() { SWAP(C); return 8; }
    uint8_t CPU::instr_cb_SWAP_D() { SWAP(D); return 8; }
    uint8_t CPU::instr_cb_SWAP_E() { SWAP(E); return 8; }
    uint8_t CPU::instr_cb_SWAP_H() { SWAP(H); return 8; }
    uint8_t CPU::instr_cb_SWAP_L() { SWAP(L); return 8; }
    uint8_t CPU::instr_cb_SWAP_mHL() {
         uint8_t v = mmu->read(HL.word);
         SWAP(v);
         mmu->write(HL.word, v);
         return 16;
    }
    uint8_t CPU::instr_cb_SWAP_A() { SWAP(A); return 8; }
    uint8_t CPU::instr_cb_SRL_B() { SRL(B); return 8; }
    uint8_t CPU::instr_cb_SRL_C() { SRL(C); return 8; }
    uint8_t CPU::instr_cb_SRL_D() { SRL(D); return 8; }
    uint8_t CPU::instr_cb_SRL_E() { SRL(E); return 8; }
    uint8_t CPU::instr_cb_SRL_H() { SRL(H); return 8; }
    uint8_t CPU::instr_cb_SRL_L() { SRL(L); return 8; }
    uint8_t CPU::instr_cb_SRL_mHL() {
         uint8_t v = mmu->read(HL.word);
         SRL(v);
         mmu->write(HL.word, v);
         return 16;
    }
    uint8_t CPU::instr_cb_SRL_A() { SRL(A); return 8; }

    // --- Row 0x4_ (BIT 0 & BIT 1) ---
    uint8_t CPU::instr_cb_BIT_0_B() { BIT(0, B); return 8; }
    uint8_t CPU::instr_cb_BIT_0_C() { BIT(0, C); return 8; }
    uint8_t CPU::instr_cb_BIT_0_D() { BIT(0, D); return 8; }
    uint8_t CPU::instr_cb_BIT_0_E() { BIT(0, E); return 8; }
    uint8_t CPU::instr_cb_BIT_0_H() { BIT(0, H); return 8; }
    uint8_t CPU::instr_cb_BIT_0_L() { BIT(0, L); return 8; }
    uint8_t CPU::instr_cb_BIT_0_mHL() {
        uint8_t v = mmu->read(HL.word);
        BIT(0, v);
        return 12;
    }
    uint8_t CPU::instr_cb_BIT_0_A() { BIT(0, A); return 8; }
    uint8_t CPU::instr_cb_BIT_1_B() { BIT(1, B); return 8; }
    uint8_t CPU::instr_cb_BIT_1_C() { BIT(1, C); return 8; }
    uint8_t CPU::instr_cb_BIT_1_D() { BIT(1, D); return 8; }
    uint8_t CPU::instr_cb_BIT_1_E() { BIT(1, E); return 8; }
    uint8_t CPU::instr_cb_BIT_1_H() { BIT(1, H); return 8; }
    uint8_t CPU::instr_cb_BIT_1_L() { BIT(1, L); return 8; }
    uint8_t CPU::instr_cb_BIT_1_mHL() {
         uint8_t v = mmu->read(HL.word);
         BIT(1, v);
         return 12;
    }
    uint8_t CPU::instr_cb_BIT_1_A() { BIT(1, A); return 8; }

    // --- Row 0x5_ (BIT 2 & BIT 3) ---
    uint8_t CPU::instr_cb_BIT_2_B() { BIT(2, B); return 8; }
    uint8_t CPU::instr_cb_BIT_2_C() { BIT(2, C); return 8; }
    uint8_t CPU::instr_cb_BIT_2_D() { BIT(2, D); return 8; }
    uint8_t CPU::instr_cb_BIT_2_E() { BIT(2, E); return 8; }
    uint8_t CPU::instr_cb_BIT_2_H() { BIT(2, H); return 8; }
    uint8_t CPU::instr_cb_BIT_2_L() { BIT(2, L); return 8; }
    uint8_t CPU::instr_cb_BIT_2_mHL() {
         uint8_t v = mmu->read(HL.word);
         BIT(2, v);
         return 12;
    }
    uint8_t CPU::instr_cb_BIT_2_A() { BIT(2, A); return 8; }
    uint8_t CPU::instr_cb_BIT_3_B() { BIT(3, B); return 8; }
    uint8_t CPU::instr_cb_BIT_3_C() { BIT(3, C); return 8; }
    uint8_t CPU::instr_cb_BIT_3_D() { BIT(3, D); return 8; }
    uint8_t CPU::instr_cb_BIT_3_E() { BIT(3, E); return 8; }
    uint8_t CPU::instr_cb_BIT_3_H() { BIT(3, H); return 8; }
    uint8_t CPU::instr_cb_BIT_3_L() { BIT(3, L); return 8; }
    uint8_t CPU::instr_cb_BIT_3_mHL() {
         uint8_t v = mmu->read(HL.word);
         BIT(3, v);
         return 12;
    }
    uint8_t CPU::instr_cb_BIT_3_A() { BIT(3, A); return 8; }

    // --- Row 0x6_ (BIT 4 & BIT 5) ---
    uint8_t CPU::instr_cb_BIT_4_B() { BIT(4, B); return 8; }
    uint8_t CPU::instr_cb_BIT_4_C() { BIT(4, C); return 8; }
    uint8_t CPU::instr_cb_BIT_4_D() { BIT(4, D); return 8; }
    uint8_t CPU::instr_cb_BIT_4_E() { BIT(4, E); return 8; }
    uint8_t CPU::instr_cb_BIT_4_H() { BIT(4, H); return 8; }
    uint8_t CPU::instr_cb_BIT_4_L() { BIT(4, L); return 8; }
    uint8_t CPU::instr_cb_BIT_4_mHL() {
         uint8_t v = mmu->read(HL.word);
         BIT(4, v);
         return 12;
    }
    uint8_t CPU::instr_cb_BIT_4_A() { BIT(4, A); return 8; }
    uint8_t CPU::instr_cb_BIT_5_B() { BIT(5, B); return 8; }
    uint8_t CPU::instr_cb_BIT_5_C() { BIT(5, C); return 8; }
    uint8_t CPU::instr_cb_BIT_5_D() { BIT(5, D); return 8; }
    uint8_t CPU::instr_cb_BIT_5_E() { BIT(5, E); return 8; }
    uint8_t CPU::instr_cb_BIT_5_H() { BIT(5, H); return 8; }
    uint8_t CPU::instr_cb_BIT_5_L() { BIT(5, L); return 8; }
    uint8_t CPU::instr_cb_BIT_5_mHL() {
        uint8_t v = mmu->read(HL.word);
        BIT(5, v);
        return 12;
    }
    uint8_t CPU::instr_cb_BIT_5_A() { BIT(5, A); return 8; }

    // --- Row 0x7_ (BIT 6 & BIT 7) ---
    uint8_t CPU::instr_cb_BIT_6_B() { BIT(6, B); return 8; }
    uint8_t CPU::instr_cb_BIT_6_C() { BIT(6, C); return 8; }
    uint8_t CPU::instr_cb_BIT_6_D() { BIT(6, D); return 8; }
    uint8_t CPU::instr_cb_BIT_6_E() { BIT(6, E); return 8; }
    uint8_t CPU::instr_cb_BIT_6_H() { BIT(6, H); return 8; }
    uint8_t CPU::instr_cb_BIT_6_L() { BIT(6, L); return 8; }
    uint8_t CPU::instr_cb_BIT_6_mHL() {
        uint8_t v = mmu->read(HL.word);
        BIT(6, v);
        return 12;
    }
    uint8_t CPU::instr_cb_BIT_6_A() { BIT(6, A); return 8; }
    uint8_t CPU::instr_cb_BIT_7_B() { BIT(7, B); return 8; }
    uint8_t CPU::instr_cb_BIT_7_C() { BIT(7, C); return 8; }
    uint8_t CPU::instr_cb_BIT_7_D() { BIT(7, D); return 8; }
    uint8_t CPU::instr_cb_BIT_7_E() { BIT(7, E); return 8; }
    uint8_t CPU::instr_cb_BIT_7_H() { BIT(7, H); return 8; }
    uint8_t CPU::instr_cb_BIT_7_L() { BIT(7, L); return 8; }
    uint8_t CPU::instr_cb_BIT_7_mHL() {
        uint8_t v = mmu->read(HL.word);
        BIT(7, v);
        return 12;
    }
    uint8_t CPU::instr_cb_BIT_7_A() { BIT(7, A); return 8; }

    // --- Row 0x8_ (RES 0 & RES 1) ---

    uint8_t CPU::instr_cb_RES_0_B() { RES(0, B); return 8; }
    uint8_t CPU::instr_cb_RES_0_C() { RES(0, C); return 8; }
    uint8_t CPU::instr_cb_RES_0_D() { RES(0, D); return 8; }
    uint8_t CPU::instr_cb_RES_0_E() { RES(0, E); return 8; }
    uint8_t CPU::instr_cb_RES_0_H() { RES(0, H); return 8; }
    uint8_t CPU::instr_cb_RES_0_L() { RES(0, L); return 8; }
    uint8_t CPU::instr_cb_RES_0_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(0, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_0_A() { RES(0, A); return 8; }
    uint8_t CPU::instr_cb_RES_1_B() { RES(1, B); return 8; }
    uint8_t CPU::instr_cb_RES_1_C() { RES(1, C); return 8; }
    uint8_t CPU::instr_cb_RES_1_D() { RES(1, D); return 8; }
    uint8_t CPU::instr_cb_RES_1_E() { RES(1, E); return 8; }
    uint8_t CPU::instr_cb_RES_1_H() { RES(1, H); return 8; }
    uint8_t CPU::instr_cb_RES_1_L() { RES(1, L); return 8; }
    uint8_t CPU::instr_cb_RES_1_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(1, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_1_A() { RES(1, A); return 8; }

    // --- Row 0x9_ (RES 2 & RES 3) ---

    uint8_t CPU::instr_cb_RES_2_B() { RES(2, B); return 8; }
    uint8_t CPU::instr_cb_RES_2_C() { RES(2, C); return 8; }
    uint8_t CPU::instr_cb_RES_2_D() { RES(2, D); return 8; }
    uint8_t CPU::instr_cb_RES_2_E() { RES(2, E); return 8; }
    uint8_t CPU::instr_cb_RES_2_H() { RES(2, H); return 8; }
    uint8_t CPU::instr_cb_RES_2_L() { RES(2, L); return 8; }
    uint8_t CPU::instr_cb_RES_2_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(2, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_2_A() { RES(2, A); return 8; }
    uint8_t CPU::instr_cb_RES_3_B() { RES(3, B); return 8; }
    uint8_t CPU::instr_cb_RES_3_C() { RES(3, C); return 8; }
    uint8_t CPU::instr_cb_RES_3_D() { RES(3, D); return 8; }
    uint8_t CPU::instr_cb_RES_3_E() { RES(3, E); return 8; }
    uint8_t CPU::instr_cb_RES_3_H() { RES(3, H); return 8; }
    uint8_t CPU::instr_cb_RES_3_L() { RES(3, L); return 8; }
    uint8_t CPU::instr_cb_RES_3_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(3, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_3_A() { RES(3, A); return 8; }

    // --- Row 0xA_ (RES 4 & RES 5) ---

    uint8_t CPU::instr_cb_RES_4_B() { RES(4, B); return 8; }
    uint8_t CPU::instr_cb_RES_4_C() { RES(4, C); return 8; }
    uint8_t CPU::instr_cb_RES_4_D() { RES(4, D); return 8; }
    uint8_t CPU::instr_cb_RES_4_E() { RES(4, E); return 8; }
    uint8_t CPU::instr_cb_RES_4_H() { RES(4, H); return 8; }
    uint8_t CPU::instr_cb_RES_4_L() { RES(4, L); return 8; }
    uint8_t CPU::instr_cb_RES_4_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(4, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_4_A() { RES(4, A); return 8; }
    uint8_t CPU::instr_cb_RES_5_B() { RES(5, B); return 8; }
    uint8_t CPU::instr_cb_RES_5_C() { RES(5, C); return 8; }
    uint8_t CPU::instr_cb_RES_5_D() { RES(5, D); return 8; }
    uint8_t CPU::instr_cb_RES_5_E() { RES(5, E); return 8; }
    uint8_t CPU::instr_cb_RES_5_H() { RES(5, H); return 8; }
    uint8_t CPU::instr_cb_RES_5_L() { RES(5, L); return 8; }
    uint8_t CPU::instr_cb_RES_5_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(5, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_5_A() { RES(5, A); return 8; }

    // --- Row 0xB_ (RES 6 & RES 7) ---

    uint8_t CPU::instr_cb_RES_6_B() { RES(6, B); return 8; }
    uint8_t CPU::instr_cb_RES_6_C() { RES(6, C); return 8; }
    uint8_t CPU::instr_cb_RES_6_D() { RES(6, D); return 8; }
    uint8_t CPU::instr_cb_RES_6_E() { RES(6, E); return 8; }
    uint8_t CPU::instr_cb_RES_6_H() { RES(6, H); return 8; }
    uint8_t CPU::instr_cb_RES_6_L() { RES(6, L); return 8; }
    uint8_t CPU::instr_cb_RES_6_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(6, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_6_A() { RES(6, A); return 8; }
    uint8_t CPU::instr_cb_RES_7_B() { RES(7, B); return 8; }
    uint8_t CPU::instr_cb_RES_7_C() { RES(7, C); return 8; }
    uint8_t CPU::instr_cb_RES_7_D() { RES(7, D); return 8; }
    uint8_t CPU::instr_cb_RES_7_E() { RES(7, E); return 8; }
    uint8_t CPU::instr_cb_RES_7_H() { RES(7, H); return 8; }
    uint8_t CPU::instr_cb_RES_7_L() { RES(7, L); return 8; }
    uint8_t CPU::instr_cb_RES_7_mHL() {
        uint8_t v = mmu->read(HL.word);
        RES(7, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_RES_7_A() { RES(7, A); return 8; }

    // --- Row 0xC_ (SET 0 & SET 1) ---

    uint8_t CPU::instr_cb_SET_0_B() { SET(0, B); return 8; }
    uint8_t CPU::instr_cb_SET_0_C() { SET(0, C); return 8; }
    uint8_t CPU::instr_cb_SET_0_D() { SET(0, D); return 8; }
    uint8_t CPU::instr_cb_SET_0_E() { SET(0, E); return 8; }
    uint8_t CPU::instr_cb_SET_0_H() { SET(0, H); return 8; }
    uint8_t CPU::instr_cb_SET_0_L() { SET(0, L); return 8; }
    uint8_t CPU::instr_cb_SET_0_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(0, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_0_A() { SET(0, A); return 8; }
    uint8_t CPU::instr_cb_SET_1_B() { SET(1, B); return 8; }
    uint8_t CPU::instr_cb_SET_1_C() { SET(1, C); return 8; }
    uint8_t CPU::instr_cb_SET_1_D() { SET(1, D); return 8; }
    uint8_t CPU::instr_cb_SET_1_E() { SET(1, E); return 8; }
    uint8_t CPU::instr_cb_SET_1_H() { SET(1, H); return 8; }
    uint8_t CPU::instr_cb_SET_1_L() { SET(1, L); return 8; }
    uint8_t CPU::instr_cb_SET_1_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(1, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_1_A() { SET(1, A); return 8; }

    // --- Row 0xD_ (SET 2 & SET 3) ---

    uint8_t CPU::instr_cb_SET_2_B() { SET(2, B); return 8; }
    uint8_t CPU::instr_cb_SET_2_C() { SET(2, C); return 8; }
    uint8_t CPU::instr_cb_SET_2_D() { SET(2, D); return 8; }
    uint8_t CPU::instr_cb_SET_2_E() { SET(2, E); return 8; }
    uint8_t CPU::instr_cb_SET_2_H() { SET(2, H); return 8; }
    uint8_t CPU::instr_cb_SET_2_L() { SET(2, L); return 8; }
    uint8_t CPU::instr_cb_SET_2_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(2, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_2_A() { SET(2, A); return 8; }
    uint8_t CPU::instr_cb_SET_3_B() { SET(3, B); return 8; }
    uint8_t CPU::instr_cb_SET_3_C() { SET(3, C); return 8; }
    uint8_t CPU::instr_cb_SET_3_D() { SET(3, D); return 8; }
    uint8_t CPU::instr_cb_SET_3_E() { SET(3, E); return 8; }
    uint8_t CPU::instr_cb_SET_3_H() { SET(3, H); return 8; }
    uint8_t CPU::instr_cb_SET_3_L() { SET(3, L); return 8; }
    uint8_t CPU::instr_cb_SET_3_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(3, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_3_A() { SET(3, A); return 8; }

    // --- Row 0xE_ (SET 4 & SET 5) ---

    uint8_t CPU::instr_cb_SET_4_B() { SET(4, B); return 8; }
    uint8_t CPU::instr_cb_SET_4_C() { SET(4, C); return 8; }
    uint8_t CPU::instr_cb_SET_4_D() { SET(4, D); return 8; }
    uint8_t CPU::instr_cb_SET_4_E() { SET(4, E); return 8; }
    uint8_t CPU::instr_cb_SET_4_H() { SET(4, H); return 8; }
    uint8_t CPU::instr_cb_SET_4_L() { SET(4, L); return 8; }
    uint8_t CPU::instr_cb_SET_4_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(4, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_4_A() { SET(4, A); return 8; }
    uint8_t CPU::instr_cb_SET_5_B() { SET(5, B); return 8; }
    uint8_t CPU::instr_cb_SET_5_C() { SET(5, C); return 8; }
    uint8_t CPU::instr_cb_SET_5_D() { SET(5, D); return 8; }
    uint8_t CPU::instr_cb_SET_5_E() { SET(5, E); return 8; }
    uint8_t CPU::instr_cb_SET_5_H() { SET(5, H); return 8; }
    uint8_t CPU::instr_cb_SET_5_L() { SET(5, L); return 8; }
    uint8_t CPU::instr_cb_SET_5_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(5, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_5_A() { SET(5, A); return 8; }

    // --- Row 0xF_ (SET 6 & SET 7) ---

    uint8_t CPU::instr_cb_SET_6_B() { SET(6, B); return 8; }
    uint8_t CPU::instr_cb_SET_6_C() { SET(6, C); return 8; }
    uint8_t CPU::instr_cb_SET_6_D() { SET(6, D); return 8; }
    uint8_t CPU::instr_cb_SET_6_E() { SET(6, E); return 8; }
    uint8_t CPU::instr_cb_SET_6_H() { SET(6, H); return 8; }
    uint8_t CPU::instr_cb_SET_6_L() { SET(6, L); return 8; }
    uint8_t CPU::instr_cb_SET_6_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(6, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_6_A() { SET(6, A); return 8; }
    uint8_t CPU::instr_cb_SET_7_B() { SET(7, B); return 8; }
    uint8_t CPU::instr_cb_SET_7_C() { SET(7, C); return 8; }
    uint8_t CPU::instr_cb_SET_7_D() { SET(7, D); return 8; }
    uint8_t CPU::instr_cb_SET_7_E() { SET(7, E); return 8; }
    uint8_t CPU::instr_cb_SET_7_H() { SET(7, H); return 8; }
    uint8_t CPU::instr_cb_SET_7_L() { SET(7, L); return 8; }
    uint8_t CPU::instr_cb_SET_7_mHL() {
        uint8_t v = mmu->read(HL.word);
        SET(7, v);
        mmu->write(HL.word, v);
        return 16;
    }
    uint8_t CPU::instr_cb_SET_7_A() { SET(7, A); return 8; }

}
