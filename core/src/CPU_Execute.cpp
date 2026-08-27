//
// Created by Andreas Sabelfeld on 27.04.2026.
//

#include <ios>
#include <iostream>
#include <ostream>

#include "CPU.h"
#include "Timer.h"

namespace gb::core {
    void CPU::execute(const Instruction &inst, uint8_t opcode) {
#ifdef PRINT_TRACE
        std::cout << "Executing: " << inst.mnemonic
              << " at PC: " << std::hex << PC
              << " | DE: " << std::hex << DE.word
              << " | Z: " << get_flag_z() << std::endl;
#endif

        switch (opcode) {
            // --- Row 0x0_ ---
            case 0x00: instr_NOP(); break; 
            case 0x01: instr_LD_BC_n16(); break; 
            case 0x02: instr_LD_mBC_A(); break; 
            case 0x03: instr_INC_BC(); break; 
            case 0x04: instr_INC_B(); break; 
            case 0x05: instr_DEC_B(); break; 
            case 0x06: instr_LD_B_n8(); break; 
            case 0x07: instr_RLCA(); break; 
            case 0x08: instr_LD_mn16_SP(); break; 
            case 0x09: instr_ADD_HL_BC(); break; 
            case 0x0A: instr_LD_A_mBC(); break; 
            case 0x0B: instr_DEC_BC(); break; 
            case 0x0C: instr_INC_C(); break; 
            case 0x0D: instr_DEC_C(); break; 
            case 0x0E: instr_LD_C_n8(); break; 
            case 0x0F: instr_RRCA(); break; 

            // --- Row 0x1_ ---
            case 0x10: instr_STOP(); break; 
            case 0x11: instr_LD_DE_n16(); break; 
            case 0x12: instr_LD_mDE_A(); break; 
            case 0x13: instr_INC_DE(); break; 
            case 0x14: instr_INC_D(); break; 
            case 0x15: instr_DEC_D(); break; 
            case 0x16: instr_LD_D_n8(); break; 
            case 0x17: instr_RLA(); break; 
            case 0x18: instr_JR_n8(); break; 
            case 0x19: instr_ADD_HL_DE(); break; 
            case 0x1A: instr_LD_A_mDE(); break; 
            case 0x1B: instr_DEC_DE(); break; 
            case 0x1C: instr_INC_E(); break; 
            case 0x1D: instr_DEC_E(); break; 
            case 0x1E: instr_LD_E_n8(); break; 
            case 0x1F: instr_RRA(); break; 

            // --- Row 0x2_ ---
            case 0x20: instr_JR_NZ_n8(); break; 
            case 0x21: instr_LD_HL_n16(); break; 
            case 0x22: instr_LD_mHL_plus_A(); break; 
            case 0x23: instr_INC_HL(); break; 
            case 0x24: instr_INC_H(); break; 
            case 0x25: instr_DEC_H(); break; 
            case 0x26: instr_LD_H_n8(); break; 
            case 0x27: instr_DAA(); break; 
            case 0x28: instr_JR_Z_n8(); break; 
            case 0x29: instr_ADD_HL_HL(); break; 
            case 0x2A: instr_LD_A_mHL_plus(); break; 
            case 0x2B: instr_DEC_HL(); break; 
            case 0x2C: instr_INC_L(); break; 
            case 0x2D: instr_DEC_L(); break; 
            case 0x2E: instr_LD_L_n8(); break; 
            case 0x2F: instr_CPL(); break; 

            // --- Row 0x3_ ---
            case 0x30: instr_JR_NC_n8(); break; 
            case 0x31: instr_LD_SP_n16(); break; 
            case 0x32: instr_LD_mHL_minus_A(); break; 
            case 0x33: instr_INC_SP(); break; 
            case 0x34: instr_INC_mHL(); break; 
            case 0x35: instr_DEC_mHL(); break; 
            case 0x36: instr_LD_mHL_n8(); break; 
            case 0x37: instr_SCF(); break; 
            case 0x38: instr_JR_C_n8(); break; 
            case 0x39: instr_ADD_HL_SP(); break; 
            case 0x3A: instr_LD_A_mHL_minus(); break; 
            case 0x3B: instr_DEC_SP(); break; 
            case 0x3C: instr_INC_A(); break; 
            case 0x3D: instr_DEC_A(); break; 
            case 0x3E: instr_LD_A_n8(); break; 
            case 0x3F: instr_CCF(); break; 

            // --- Row 0x4_ ---
            case 0x40: instr_LD_B_B(); break; 
            case 0x41: instr_LD_B_C(); break; 
            case 0x42: instr_LD_B_D(); break; 
            case 0x43: instr_LD_B_E(); break; 
            case 0x44: instr_LD_B_H(); break; 
            case 0x45: instr_LD_B_L(); break; 
            case 0x46: instr_LD_B_mHL(); break; 
            case 0x47: instr_LD_B_A(); break; 
            case 0x48: instr_LD_C_B(); break; 
            case 0x49: instr_LD_C_C(); break; 
            case 0x4A: instr_LD_C_D(); break; 
            case 0x4B: instr_LD_C_E(); break; 
            case 0x4C: instr_LD_C_H(); break; 
            case 0x4D: instr_LD_C_L(); break; 
            case 0x4E: instr_LD_C_mHL(); break; 
            case 0x4F: instr_LD_C_A(); break; 

            // --- Row 0x5_ ---
            case 0x50: instr_LD_D_B(); break; 
            case 0x51: instr_LD_D_C(); break; 
            case 0x52: instr_LD_D_D(); break; 
            case 0x53: instr_LD_D_E(); break; 
            case 0x54: instr_LD_D_H(); break; 
            case 0x55: instr_LD_D_L(); break; 
            case 0x56: instr_LD_D_mHL(); break; 
            case 0x57: instr_LD_D_A(); break; 
            case 0x58: instr_LD_E_B(); break; 
            case 0x59: instr_LD_E_C(); break; 
            case 0x5A: instr_LD_E_D(); break; 
            case 0x5B: instr_LD_E_E(); break; 
            case 0x5C: instr_LD_E_H(); break; 
            case 0x5D: instr_LD_E_L(); break; 
            case 0x5E: instr_LD_E_mHL(); break; 
            case 0x5F: instr_LD_E_A(); break; 

            // --- Row 0x6_ ---
            case 0x60: instr_LD_H_B(); break; 
            case 0x61: instr_LD_H_C(); break; 
            case 0x62: instr_LD_H_D(); break; 
            case 0x63: instr_LD_H_E(); break; 
            case 0x64: instr_LD_H_H(); break; 
            case 0x65: instr_LD_H_L(); break; 
            case 0x66: instr_LD_H_mHL(); break; 
            case 0x67: instr_LD_H_A(); break; 
            case 0x68: instr_LD_L_B(); break; 
            case 0x69: instr_LD_L_C(); break; 
            case 0x6A: instr_LD_L_D(); break; 
            case 0x6B: instr_LD_L_E(); break; 
            case 0x6C: instr_LD_L_H(); break; 
            case 0x6D: instr_LD_L_L(); break; 
            case 0x6E: instr_LD_L_mHL(); break; 
            case 0x6F: instr_LD_L_A(); break; 

            // --- Row 0x7_ ---
            case 0x70: instr_LD_mHL_B(); break; 
            case 0x71: instr_LD_mHL_C(); break; 
            case 0x72: instr_LD_mHL_D(); break; 
            case 0x73: instr_LD_mHL_E(); break; 
            case 0x74: instr_LD_mHL_H(); break; 
            case 0x75: instr_LD_mHL_L(); break; 
            case 0x76: instr_HALT(); break; 
            case 0x77: instr_LD_mHL_A(); break; 
            case 0x78: instr_LD_A_B(); break; 
            case 0x79: instr_LD_A_C(); break; 
            case 0x7A: instr_LD_A_D(); break; 
            case 0x7B: instr_LD_A_E(); break; 
            case 0x7C: instr_LD_A_H(); break; 
            case 0x7D: instr_LD_A_L(); break; 
            case 0x7E: instr_LD_A_mHL(); break; 
            case 0x7F: instr_LD_A_A(); break; 

            // --- Row 0x8_ ---
            case 0x80: instr_ADD_A_B(); break; 
            case 0x81: instr_ADD_A_C(); break; 
            case 0x82: instr_ADD_A_D(); break; 
            case 0x83: instr_ADD_A_E(); break; 
            case 0x84: instr_ADD_A_H(); break; 
            case 0x85: instr_ADD_A_L(); break; 
            case 0x86: instr_ADD_A_mHL(); break; 
            case 0x87: instr_ADD_A_A(); break; 
            case 0x88: instr_ADC_A_B(); break; 
            case 0x89: instr_ADC_A_C(); break; 
            case 0x8A: instr_ADC_A_D(); break; 
            case 0x8B: instr_ADC_A_E(); break; 
            case 0x8C: instr_ADC_A_H(); break; 
            case 0x8D: instr_ADC_A_L(); break; 
            case 0x8E: instr_ADC_A_mHL(); break; 
            case 0x8F: instr_ADC_A_A(); break; 

            // --- Row 0x9_ ---
            case 0x90: instr_SUB_A_B(); break; 
            case 0x91: instr_SUB_A_C(); break; 
            case 0x92: instr_SUB_A_D(); break; 
            case 0x93: instr_SUB_A_E(); break; 
            case 0x94: instr_SUB_A_H(); break; 
            case 0x95: instr_SUB_A_L(); break; 
            case 0x96: instr_SUB_A_mHL(); break; 
            case 0x97: instr_SUB_A_A(); break; 
            case 0x98: instr_SBC_A_B(); break; 
            case 0x99: instr_SBC_A_C(); break; 
            case 0x9A: instr_SBC_A_D(); break; 
            case 0x9B: instr_SBC_A_E(); break; 
            case 0x9C: instr_SBC_A_H(); break; 
            case 0x9D: instr_SBC_A_L(); break; 
            case 0x9E: instr_SBC_A_mHL(); break; 
            case 0x9F: instr_SBC_A_A(); break; 

            // --- Row 0xA_ ---
            case 0xA0: instr_AND_A_B(); break; 
            case 0xA1: instr_AND_A_C(); break; 
            case 0xA2: instr_AND_A_D(); break; 
            case 0xA3: instr_AND_A_E(); break; 
            case 0xA4: instr_AND_A_H(); break; 
            case 0xA5: instr_AND_A_L(); break; 
            case 0xA6: instr_AND_A_mHL(); break; 
            case 0xA7: instr_AND_A_A(); break; 
            case 0xA8: instr_XOR_A_B(); break; 
            case 0xA9: instr_XOR_A_C(); break; 
            case 0xAA: instr_XOR_A_D(); break; 
            case 0xAB: instr_XOR_A_E(); break; 
            case 0xAC: instr_XOR_A_H(); break; 
            case 0xAD: instr_XOR_A_L(); break; 
            case 0xAE: instr_XOR_A_mHL(); break; 
            case 0xAF: instr_XOR_A_A(); break; 

            // --- Row 0xB_ ---
            case 0xB0: instr_OR_A_B(); break; 
            case 0xB1: instr_OR_A_C(); break; 
            case 0xB2: instr_OR_A_D(); break; 
            case 0xB3: instr_OR_A_E(); break; 
            case 0xB4: instr_OR_A_H(); break; 
            case 0xB5: instr_OR_A_L(); break; 
            case 0xB6: instr_OR_A_mHL(); break; 
            case 0xB7: instr_OR_A_A(); break; 
            case 0xB8: instr_CP_A_B(); break; 
            case 0xB9: instr_CP_A_C(); break; 
            case 0xBA: instr_CP_A_D(); break; 
            case 0xBB: instr_CP_A_E(); break; 
            case 0xBC: instr_CP_A_H(); break; 
            case 0xBD: instr_CP_A_L(); break; 
            case 0xBE: instr_CP_A_mHL(); break; 
            case 0xBF: instr_CP_A_A(); break; 

            // --- Row 0xC_ ---
            case 0xC0: instr_RET_NZ(); break; 
            case 0xC1: instr_POP_BC(); break; 
            case 0xC2: instr_JP_NZ_n16(); break; 
            case 0xC3: instr_JP_n16(); break; 
            case 0xC4: instr_CALL_NZ_n16(); break; 
            case 0xC5: instr_PUSH_BC(); break; 
            case 0xC6: instr_ADD_A_n8(); break; 
            case 0xC7: instr_RST_00H(); break; 
            case 0xC8: instr_RET_Z(); break; 
            case 0xC9: instr_RET(); break; 
            case 0xCA: instr_JP_Z_n16(); break; 
            case 0xCB: instr_PREFIX_CB(); break; 
            case 0xCC: instr_CALL_Z_n16(); break; 
            case 0xCD: instr_CALL_n16(); break; 
            case 0xCE: instr_ADC_A_n8(); break; 
            case 0xCF: instr_RST_08H(); break; 

            // --- Row 0xD_ ---
            case 0xD0: instr_RET_NC(); break; 
            case 0xD1: instr_POP_DE(); break; 
            case 0xD2: instr_JP_NC_n16(); break; 
            case 0xD3: instr_UNUSED_D3(); break; 
            case 0xD4: instr_CALL_NC_n16(); break; 
            case 0xD5: instr_PUSH_DE(); break; 
            case 0xD6: instr_SUB_A_n8(); break; 
            case 0xD7: instr_RST_10H(); break; 
            case 0xD8: instr_RET_C(); break; 
            case 0xD9: instr_RETI(); break; 
            case 0xDA: instr_JP_C_n16(); break; 
            case 0xDB: instr_UNUSED_DB(); break; 
            case 0xDC: instr_CALL_C_n16(); break; 
            case 0xDD: instr_UNUSED_DD(); break; 
            case 0xDE: instr_SBC_A_n8(); break; 
            case 0xDF: instr_RST_18H(); break; 

            // --- Row 0xE_ ---
            case 0xE0: instr_LDH_mn8_A(); break; 
            case 0xE1: instr_POP_HL(); break; 
            case 0xE2: instr_LD_mC_A(); break; 
            case 0xE3: instr_UNUSED_E3(); break; 
            case 0xE4: instr_UNUSED_E4(); break; 
            case 0xE5: instr_PUSH_HL(); break; 
            case 0xE6: instr_AND_A_n8(); break; 
            case 0xE7: instr_RST_20H(); break; 
            case 0xE8: instr_ADD_SP_e8(); break; 
            case 0xE9: instr_JP_HL(); break; 
            case 0xEA: instr_LD_mn16_A(); break; 
            case 0xEB: instr_UNUSED_EB(); break; 
            case 0xEC: instr_UNUSED_EC(); break; 
            case 0xED: instr_UNUSED_ED(); break; 
            case 0xEE: instr_XOR_A_n8(); break; 
            case 0xEF: instr_RST_28H(); break; 

            // --- Row 0xF_ ---
            case 0xF0: instr_LDH_A_mn8(); break; 
            case 0xF1: instr_POP_AF(); break; 
            case 0xF2: instr_LD_A_mC(); break; 
            case 0xF3: instr_DI(); break; 
            case 0xF4: instr_UNUSED_F4(); break; 
            case 0xF5: instr_PUSH_AF(); break; 
            case 0xF6: instr_OR_A_n8(); break; 
            case 0xF7: instr_RST_30H(); break; 
            case 0xF8: instr_LD_HL_SP_plus_e8(); break; 
            case 0xF9: instr_LD_SP_HL(); break; 
            case 0xFA: instr_LD_A_mn16(); break; 
            case 0xFB: instr_EI(); break; 
            case 0xFC: instr_UNUSED_FC(); break; 
            case 0xFD: instr_UNUSED_FD(); break; 
            case 0xFE: instr_CP_A_n8(); break; 
            case 0xFF: instr_RST_38H(); break; 
            default:
                // It should be impossible to hit this default;
        }
    }

    void CPU::execute_cb() {
        uint8_t opcode = fetch_byte();

        switch (opcode) {
            // --- Row 0x0_ ---
            case 0x00: instr_cb_RLC_B(); break; 
            case 0x01: instr_cb_RLC_C(); break; 
            case 0x02: instr_cb_RLC_D(); break; 
            case 0x03: instr_cb_RLC_E(); break; 
            case 0x04: instr_cb_RLC_H(); break; 
            case 0x05: instr_cb_RLC_L(); break; 
            case 0x06: instr_cb_RLC_mHL(); break; 
            case 0x07: instr_cb_RLC_A(); break; 
            case 0x08: instr_cb_RRC_B(); break; 
            case 0x09: instr_cb_RRC_C(); break; 
            case 0x0A: instr_cb_RRC_D(); break; 
            case 0x0B: instr_cb_RRC_E(); break; 
            case 0x0C: instr_cb_RRC_H(); break; 
            case 0x0D: instr_cb_RRC_L(); break; 
            case 0x0E: instr_cb_RRC_mHL(); break; 
            case 0x0F: instr_cb_RRC_A(); break; 

            // --- Row 0x1_ ---
            case 0x10: instr_cb_RL_B(); break; 
            case 0x11: instr_cb_RL_C(); break; 
            case 0x12: instr_cb_RL_D(); break; 
            case 0x13: instr_cb_RL_E(); break; 
            case 0x14: instr_cb_RL_H(); break; 
            case 0x15: instr_cb_RL_L(); break; 
            case 0x16: instr_cb_RL_mHL(); break; 
            case 0x17: instr_cb_RL_A(); break; 
            case 0x18: instr_cb_RR_B(); break; 
            case 0x19: instr_cb_RR_C(); break; 
            case 0x1A: instr_cb_RR_D(); break; 
            case 0x1B: instr_cb_RR_E(); break; 
            case 0x1C: instr_cb_RR_H(); break; 
            case 0x1D: instr_cb_RR_L(); break; 
            case 0x1E: instr_cb_RR_mHL(); break; 
            case 0x1F: instr_cb_RR_A(); break; 

            // --- Row 0x2_ ---
            case 0x20: instr_cb_SLA_B(); break; 
            case 0x21: instr_cb_SLA_C(); break; 
            case 0x22: instr_cb_SLA_D(); break; 
            case 0x23: instr_cb_SLA_E(); break; 
            case 0x24: instr_cb_SLA_H(); break; 
            case 0x25: instr_cb_SLA_L(); break; 
            case 0x26: instr_cb_SLA_mHL(); break; 
            case 0x27: instr_cb_SLA_A(); break; 
            case 0x28: instr_cb_SRA_B(); break; 
            case 0x29: instr_cb_SRA_C(); break; 
            case 0x2A: instr_cb_SRA_D(); break; 
            case 0x2B: instr_cb_SRA_E(); break; 
            case 0x2C: instr_cb_SRA_H(); break; 
            case 0x2D: instr_cb_SRA_L(); break; 
            case 0x2E: instr_cb_SRA_mHL(); break; 
            case 0x2F: instr_cb_SRA_A(); break; 

            // --- Row 0x3_ ---
            case 0x30: instr_cb_SWAP_B(); break; 
            case 0x31: instr_cb_SWAP_C(); break; 
            case 0x32: instr_cb_SWAP_D(); break; 
            case 0x33: instr_cb_SWAP_E(); break; 
            case 0x34: instr_cb_SWAP_H(); break; 
            case 0x35: instr_cb_SWAP_L(); break; 
            case 0x36: instr_cb_SWAP_mHL(); break; 
            case 0x37: instr_cb_SWAP_A(); break; 
            case 0x38: instr_cb_SRL_B(); break; 
            case 0x39: instr_cb_SRL_C(); break; 
            case 0x3A: instr_cb_SRL_D(); break; 
            case 0x3B: instr_cb_SRL_E(); break; 
            case 0x3C: instr_cb_SRL_H(); break; 
            case 0x3D: instr_cb_SRL_L(); break; 
            case 0x3E: instr_cb_SRL_mHL(); break; 
            case 0x3F: instr_cb_SRL_A(); break; 

            // --- Row 0x4_ ---
            case 0x40: instr_cb_BIT_0_B(); break; 
            case 0x41: instr_cb_BIT_0_C(); break; 
            case 0x42: instr_cb_BIT_0_D(); break; 
            case 0x43: instr_cb_BIT_0_E(); break; 
            case 0x44: instr_cb_BIT_0_H(); break; 
            case 0x45: instr_cb_BIT_0_L(); break; 
            case 0x46: instr_cb_BIT_0_mHL(); break; 
            case 0x47: instr_cb_BIT_0_A(); break; 
            case 0x48: instr_cb_BIT_1_B(); break; 
            case 0x49: instr_cb_BIT_1_C(); break; 
            case 0x4A: instr_cb_BIT_1_D(); break; 
            case 0x4B: instr_cb_BIT_1_E(); break; 
            case 0x4C: instr_cb_BIT_1_H(); break; 
            case 0x4D: instr_cb_BIT_1_L(); break; 
            case 0x4E: instr_cb_BIT_1_mHL(); break; 
            case 0x4F: instr_cb_BIT_1_A(); break; 

            // --- Row 0x5_ ---
            case 0x50: instr_cb_BIT_2_B(); break; 
            case 0x51: instr_cb_BIT_2_C(); break; 
            case 0x52: instr_cb_BIT_2_D(); break; 
            case 0x53: instr_cb_BIT_2_E(); break; 
            case 0x54: instr_cb_BIT_2_H(); break; 
            case 0x55: instr_cb_BIT_2_L(); break; 
            case 0x56: instr_cb_BIT_2_mHL(); break; 
            case 0x57: instr_cb_BIT_2_A(); break; 
            case 0x58: instr_cb_BIT_3_B(); break; 
            case 0x59: instr_cb_BIT_3_C(); break; 
            case 0x5A: instr_cb_BIT_3_D(); break; 
            case 0x5B: instr_cb_BIT_3_E(); break; 
            case 0x5C: instr_cb_BIT_3_H(); break; 
            case 0x5D: instr_cb_BIT_3_L(); break; 
            case 0x5E: instr_cb_BIT_3_mHL(); break; 
            case 0x5F: instr_cb_BIT_3_A(); break; 

            // --- Row 0x6_ ---
            case 0x60: instr_cb_BIT_4_B(); break; 
            case 0x61: instr_cb_BIT_4_C(); break; 
            case 0x62: instr_cb_BIT_4_D(); break; 
            case 0x63: instr_cb_BIT_4_E(); break; 
            case 0x64: instr_cb_BIT_4_H(); break; 
            case 0x65: instr_cb_BIT_4_L(); break; 
            case 0x66: instr_cb_BIT_4_mHL(); break; 
            case 0x67: instr_cb_BIT_4_A(); break; 
            case 0x68: instr_cb_BIT_5_B(); break; 
            case 0x69: instr_cb_BIT_5_C(); break; 
            case 0x6A: instr_cb_BIT_5_D(); break; 
            case 0x6B: instr_cb_BIT_5_E(); break; 
            case 0x6C: instr_cb_BIT_5_H(); break; 
            case 0x6D: instr_cb_BIT_5_L(); break; 
            case 0x6E: instr_cb_BIT_5_mHL(); break; 
            case 0x6F: instr_cb_BIT_5_A(); break; 

            // --- Row 0x7_ ---
            case 0x70: instr_cb_BIT_6_B(); break; 
            case 0x71: instr_cb_BIT_6_C(); break; 
            case 0x72: instr_cb_BIT_6_D(); break; 
            case 0x73: instr_cb_BIT_6_E(); break; 
            case 0x74: instr_cb_BIT_6_H(); break; 
            case 0x75: instr_cb_BIT_6_L(); break; 
            case 0x76: instr_cb_BIT_6_mHL(); break; 
            case 0x77: instr_cb_BIT_6_A(); break; 
            case 0x78: instr_cb_BIT_7_B(); break; 
            case 0x79: instr_cb_BIT_7_C(); break; 
            case 0x7A: instr_cb_BIT_7_D(); break; 
            case 0x7B: instr_cb_BIT_7_E(); break; 
            case 0x7C: instr_cb_BIT_7_H(); break; 
            case 0x7D: instr_cb_BIT_7_L(); break; 
            case 0x7E: instr_cb_BIT_7_mHL(); break; 
            case 0x7F: instr_cb_BIT_7_A(); break; 

            // --- Row 0x8_ ---
            case 0x80: instr_cb_RES_0_B(); break; 
            case 0x81: instr_cb_RES_0_C(); break; 
            case 0x82: instr_cb_RES_0_D(); break; 
            case 0x83: instr_cb_RES_0_E(); break; 
            case 0x84: instr_cb_RES_0_H(); break; 
            case 0x85: instr_cb_RES_0_L(); break; 
            case 0x86: instr_cb_RES_0_mHL(); break; 
            case 0x87: instr_cb_RES_0_A(); break; 
            case 0x88: instr_cb_RES_1_B(); break; 
            case 0x89: instr_cb_RES_1_C(); break; 
            case 0x8A: instr_cb_RES_1_D(); break; 
            case 0x8B: instr_cb_RES_1_E(); break; 
            case 0x8C: instr_cb_RES_1_H(); break; 
            case 0x8D: instr_cb_RES_1_L(); break; 
            case 0x8E: instr_cb_RES_1_mHL(); break; 
            case 0x8F: instr_cb_RES_1_A(); break; 

            // --- Row 0x9_ ---
            case 0x90: instr_cb_RES_2_B(); break; 
            case 0x91: instr_cb_RES_2_C(); break; 
            case 0x92: instr_cb_RES_2_D(); break; 
            case 0x93: instr_cb_RES_2_E(); break; 
            case 0x94: instr_cb_RES_2_H(); break; 
            case 0x95: instr_cb_RES_2_L(); break; 
            case 0x96: instr_cb_RES_2_mHL(); break; 
            case 0x97: instr_cb_RES_2_A(); break; 
            case 0x98: instr_cb_RES_3_B(); break; 
            case 0x99: instr_cb_RES_3_C(); break; 
            case 0x9A: instr_cb_RES_3_D(); break; 
            case 0x9B: instr_cb_RES_3_E(); break; 
            case 0x9C: instr_cb_RES_3_H(); break; 
            case 0x9D: instr_cb_RES_3_L(); break; 
            case 0x9E: instr_cb_RES_3_mHL(); break; 
            case 0x9F: instr_cb_RES_3_A(); break; 

            // --- Row 0xA_ ---
            case 0xA0: instr_cb_RES_4_B(); break; 
            case 0xA1: instr_cb_RES_4_C(); break; 
            case 0xA2: instr_cb_RES_4_D(); break; 
            case 0xA3: instr_cb_RES_4_E(); break; 
            case 0xA4: instr_cb_RES_4_H(); break; 
            case 0xA5: instr_cb_RES_4_L(); break; 
            case 0xA6: instr_cb_RES_4_mHL(); break; 
            case 0xA7: instr_cb_RES_4_A(); break; 
            case 0xA8: instr_cb_RES_5_B(); break; 
            case 0xA9: instr_cb_RES_5_C(); break; 
            case 0xAA: instr_cb_RES_5_D(); break; 
            case 0xAB: instr_cb_RES_5_E(); break; 
            case 0xAC: instr_cb_RES_5_H(); break; 
            case 0xAD: instr_cb_RES_5_L(); break; 
            case 0xAE: instr_cb_RES_5_mHL(); break; 
            case 0xAF: instr_cb_RES_5_A(); break; 

            // --- Row 0xB_ ---
            case 0xB0: instr_cb_RES_6_B(); break; 
            case 0xB1: instr_cb_RES_6_C(); break; 
            case 0xB2: instr_cb_RES_6_D(); break; 
            case 0xB3: instr_cb_RES_6_E(); break; 
            case 0xB4: instr_cb_RES_6_H(); break; 
            case 0xB5: instr_cb_RES_6_L(); break; 
            case 0xB6: instr_cb_RES_6_mHL(); break; 
            case 0xB7: instr_cb_RES_6_A(); break; 
            case 0xB8: instr_cb_RES_7_B(); break; 
            case 0xB9: instr_cb_RES_7_C(); break; 
            case 0xBA: instr_cb_RES_7_D(); break; 
            case 0xBB: instr_cb_RES_7_E(); break; 
            case 0xBC: instr_cb_RES_7_H(); break; 
            case 0xBD: instr_cb_RES_7_L(); break; 
            case 0xBE: instr_cb_RES_7_mHL(); break; 
            case 0xBF: instr_cb_RES_7_A(); break; 

            // --- Row 0xC_ ---
            case 0xC0: instr_cb_SET_0_B(); break; 
            case 0xC1: instr_cb_SET_0_C(); break; 
            case 0xC2: instr_cb_SET_0_D(); break; 
            case 0xC3: instr_cb_SET_0_E(); break; 
            case 0xC4: instr_cb_SET_0_H(); break; 
            case 0xC5: instr_cb_SET_0_L(); break; 
            case 0xC6: instr_cb_SET_0_mHL(); break; 
            case 0xC7: instr_cb_SET_0_A(); break; 
            case 0xC8: instr_cb_SET_1_B(); break; 
            case 0xC9: instr_cb_SET_1_C(); break; 
            case 0xCA: instr_cb_SET_1_D(); break; 
            case 0xCB: instr_cb_SET_1_E(); break; 
            case 0xCC: instr_cb_SET_1_H(); break; 
            case 0xCD: instr_cb_SET_1_L(); break; 
            case 0xCE: instr_cb_SET_1_mHL(); break; 
            case 0xCF: instr_cb_SET_1_A(); break; 

            // --- Row 0xD_ ---
            case 0xD0: instr_cb_SET_2_B(); break; 
            case 0xD1: instr_cb_SET_2_C(); break; 
            case 0xD2: instr_cb_SET_2_D(); break; 
            case 0xD3: instr_cb_SET_2_E(); break; 
            case 0xD4: instr_cb_SET_2_H(); break; 
            case 0xD5: instr_cb_SET_2_L(); break; 
            case 0xD6: instr_cb_SET_2_mHL(); break; 
            case 0xD7: instr_cb_SET_2_A(); break; 
            case 0xD8: instr_cb_SET_3_B(); break; 
            case 0xD9: instr_cb_SET_3_C(); break; 
            case 0xDA: instr_cb_SET_3_D(); break; 
            case 0xDB: instr_cb_SET_3_E(); break; 
            case 0xDC: instr_cb_SET_3_H(); break; 
            case 0xDD: instr_cb_SET_3_L(); break; 
            case 0xDE: instr_cb_SET_3_mHL(); break; 
            case 0xDF: instr_cb_SET_3_A(); break; 

            // --- Row 0xE_ ---
            case 0xE0: instr_cb_SET_4_B(); break; 
            case 0xE1: instr_cb_SET_4_C(); break; 
            case 0xE2: instr_cb_SET_4_D(); break; 
            case 0xE3: instr_cb_SET_4_E(); break; 
            case 0xE4: instr_cb_SET_4_H(); break; 
            case 0xE5: instr_cb_SET_4_L(); break; 
            case 0xE6: instr_cb_SET_4_mHL(); break; 
            case 0xE7: instr_cb_SET_4_A(); break; 
            case 0xE8: instr_cb_SET_5_B(); break; 
            case 0xE9: instr_cb_SET_5_C(); break; 
            case 0xEA: instr_cb_SET_5_D(); break; 
            case 0xEB: instr_cb_SET_5_E(); break; 
            case 0xEC: instr_cb_SET_5_H(); break; 
            case 0xED: instr_cb_SET_5_L(); break; 
            case 0xEE: instr_cb_SET_5_mHL(); break; 
            case 0xEF: instr_cb_SET_5_A(); break; 

            // --- Row 0xF_ ---
            case 0xF0: instr_cb_SET_6_B(); break; 
            case 0xF1: instr_cb_SET_6_C(); break; 
            case 0xF2: instr_cb_SET_6_D(); break; 
            case 0xF3: instr_cb_SET_6_E(); break; 
            case 0xF4: instr_cb_SET_6_H(); break; 
            case 0xF5: instr_cb_SET_6_L(); break; 
            case 0xF6: instr_cb_SET_6_mHL(); break; 
            case 0xF7: instr_cb_SET_6_A(); break; 
            case 0xF8: instr_cb_SET_7_B(); break; 
            case 0xF9: instr_cb_SET_7_C(); break; 
            case 0xFA: instr_cb_SET_7_D(); break; 
            case 0xFB: instr_cb_SET_7_E(); break; 
            case 0xFC: instr_cb_SET_7_H(); break; 
            case 0xFD: instr_cb_SET_7_L(); break; 
            case 0xFE: instr_cb_SET_7_mHL(); break; 
            case 0xFF: instr_cb_SET_7_A(); break; 

            default:
                // Should never be hit
        }
    }

    // Helper Functions:
    void CPU::INC(uint8_t &to) {
        // If the lower 4 bits are 1111 (0x0F), adding 1 will carry over.
        bool half_carry = (to & 0x0F) == 0x0F;
        to++;
        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(half_carry);
    }

    void CPU::DEC(uint8_t &to) {
        // If the lower 4 bits are 0000, subtracting 1 will borrow from bit 4.
        bool half_carry = (to & 0x0F) == 0x00;
        to--;
        set_flag_z(to == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
    }

    void CPU::ADD(uint8_t &to, uint8_t value) {
        uint16_t result = to + value;

        bool half_carry = ((to & 0x0F) + (value & 0x0F)) > 0x0F;
        to = static_cast<uint8_t>(result);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(result > 0xFF);
    }

    void CPU::ADD_HL(uint16_t value) {
        tick();
        bool half_carry = ((HL.word & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF;
        bool carry = (static_cast<uint32_t>(HL.word) + static_cast<uint32_t>(value)) > 0xFFFF;

        HL.word += value;

        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(carry);
    }

    void CPU::ADC(uint8_t &to, uint8_t value) {
        uint8_t carry = get_flag_c() ? 1 : 0;
        uint16_t result = to + value + carry;

        bool half_carry = ((to & 0x0F) + (value & 0x0F) + carry) > 0x0F;
        to = static_cast<uint8_t>(result);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(result > 0xFF);
    }

    void CPU::SUB(uint8_t &to, uint8_t value) {
        bool half_carry = (to & 0x0F) < (value & 0x0F);
        bool carry = to < value;
        to = static_cast<uint8_t>(to - value);

        set_flag_z(to == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        set_flag_c(carry);
    }

    void CPU::SBC(uint8_t &to, uint8_t value) {
        uint8_t carry_bit = get_flag_c() ? 1 : 0;

        uint16_t result = to - value - carry_bit;
        bool half_carry = (to & 0x0F) < ((value & 0x0F) + carry_bit);
        bool carry = static_cast<uint16_t>(to) < (static_cast<uint16_t>(value) + carry_bit);
        to = static_cast<uint8_t>(result);

        set_flag_z(to == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        set_flag_c(carry);
    }

    void CPU::AND_A(uint8_t value) {
        A &= value;

        set_flag_z(A == 0);
        set_flag_n(false);
        set_flag_h(true);
        set_flag_c(false);
    }

    void CPU::XOR_A(uint8_t value) {
        A ^= value;

        set_flag_z(A == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(false);
        
    }

    void CPU::OR_A(uint8_t value) {
        A |= value;

        set_flag_z(A == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(false);
    }

    void CPU::CP_A(uint8_t value) {
        bool half_carry = (A & 0x0F) < (value & 0x0F);
        bool carry = A < value;
        uint8_t result = static_cast<uint8_t>(A - value);

        set_flag_z(result == 0);
        set_flag_n(true);
        set_flag_h(half_carry);
        set_flag_c(carry);
    }

    inline uint16_t CPU::read_16bit(uint16_t address) {
        uint16_t lower = mmu->read(address);
        uint16_t higher = mmu->read(address + 1);
        return static_cast<uint16_t>((higher << 8) | lower);
    }

    // --- Row 0x0_ ---
    void CPU::instr_NOP() {             // 0x00
        // no operation
    }

    void CPU::instr_LD_BC_n16() {       // 0x01
        C = fetch_byte();
        B = fetch_byte();
    }

    void CPU::instr_LD_mBC_A() {        // 0x02
        write_byte(BC.word, A);
    }

    void CPU::instr_INC_BC() {          // 0x03
        tick();
        BC.word++;
    }

    void CPU::instr_INC_B() {           // 0x04
        INC(B);
    }

    void CPU::instr_DEC_B() {           // 0x05
        DEC(B);
    }

    void CPU::instr_LD_B_n8() {         // 0x06
        B = fetch_byte();
    }

    void CPU::instr_RLCA() {            // 0x07: Rotate Left Circular Accumulator
        uint8_t b7 = (A & 0x80) >> 7;
        A = static_cast<uint8_t>((A << 1) | b7);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
    }

    void CPU::instr_LD_mn16_SP() {      // 0x08
        uint16_t address = fetch_word();

        uint8_t sp_low = SP & 0xFF;             // top 8 bits
        uint8_t sp_high = (SP >> 8) & 0xFF;     // bottom 8 bits

        write_byte(address, sp_low);
        write_byte(address + 1, sp_high);
    }

    void CPU::instr_ADD_HL_BC() {       // 0x09
        ADD_HL(BC.word);
    }

    void CPU::instr_LD_A_mBC() {        // 0x0A
        A = read_byte(BC.word);
    }

    void CPU::instr_DEC_BC() {          // 0x0B
        tick();
        BC.word--;
    }

    void CPU::instr_INC_C() {           // 0x0C
        INC(C);
    }

    void CPU::instr_DEC_C() {           // 0x0D
        DEC(C);
    }

    void CPU::instr_LD_C_n8() {         // 0x0E
        C = fetch_byte();
    }

    void CPU::instr_RRCA() {            // 0x0F: Rotate Right Circular Accumulator
        uint8_t b0 = static_cast<uint8_t>((A & 0x01) << 7);
        A = b0 | (A >> 1);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
    }


    // --- Row 0x1_ ---
    void CPU::instr_STOP() {            // 0x10
        // TODO: Implement actual 'is_stopped' CPU state flag to halt execution until a Joypad interrupt fires.
        mmu->read(PC++);
        // TODO: is_stopped = true;
    }
    void CPU::instr_LD_DE_n16() {       // 0x11
        E = fetch_byte();
        D = fetch_byte();
    }
    void CPU::instr_LD_mDE_A() {        // 0x12
        write_byte(DE.word, A);
    }
    void CPU::instr_INC_DE() {          // 0x13
        tick();
        DE.word++;
    }
    void CPU::instr_INC_D() {           // 0x14
        INC(D);
    }
    void CPU::instr_DEC_D() {           // 0x15
        DEC(D);
    }
    void CPU::instr_LD_D_n8() {         // 0x16
        D = fetch_byte();
    }
    void CPU::instr_RLA() {             // 0x17
        uint8_t b7 = (A & 0x80) >> 7;
        A = static_cast<uint8_t>((A << 1) | static_cast<uint8_t>(get_flag_c()));

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
    }
    void CPU::instr_JR_n8() {           // 0x18
        int8_t offset = fetch_byte();
        tick();
        PC += offset;
    }
    void CPU::instr_ADD_HL_DE() {       // 0x19
        ADD_HL(DE.word);
    }
    void CPU::instr_LD_A_mDE() {        // 0x1A
        A = read_byte(DE.word);
    }
    void CPU::instr_DEC_DE() {          // 0x1B
        tick();
        DE.word--;
    }
    void CPU::instr_INC_E() {           // 0x1C
        INC(E);
    }
    void CPU::instr_DEC_E() {           // 0x1D
        DEC(E);
    }
    void CPU::instr_LD_E_n8() {         // 0x1E
        E = fetch_byte();
    }
    void CPU::instr_RRA() {             // 0x1F
        bool b0 = (A & 0x01) != 0;
        uint8_t old_carry = get_flag_c() ? 1 : 0;
        A = static_cast<uint8_t>(old_carry << 7) | (A >> 1);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0);
    }

    // --- Row 0x2_ ---
    void CPU::instr_JR_NZ_n8() {        // 0x20
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (!get_flag_z()) {
            tick();
            PC += offset;
        }
    }
    void CPU::instr_LD_HL_n16() {        // 0x21
        L = fetch_byte();
        H = fetch_byte();
    }
    void CPU::instr_LD_mHL_plus_A() {    // 0x22
        write_byte(HL.word++, A);
    }
    void CPU::instr_INC_HL() {           // 0x23
        tick();
        HL.word++;
    }
    void CPU::instr_INC_H() {            // 0x24
        INC(H);
    }
    void CPU::instr_DEC_H() {            // 0x25
        DEC(H);
    }
    void CPU::instr_LD_H_n8() {          // 0x26
        H = fetch_byte();
    }
    void CPU::instr_DAA() {              // 0x27: Decimal Adjust Accumulator
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
    }
    void CPU::instr_JR_Z_n8() {          // 0x28
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (get_flag_z()) {
            tick();
            PC += offset;
        }
    }
    void CPU::instr_ADD_HL_HL() {        // 0x29
        ADD_HL(HL.word);
    }
    void CPU::instr_LD_A_mHL_plus() {    // 0x2A
        A = read_byte(HL.word++);
    }
    void CPU::instr_DEC_HL() {           // 0x2B
        tick();
        HL.word--;
    }
    void CPU::instr_INC_L() {            // 0x2C
        INC(L);
    }
    void CPU::instr_DEC_L() {            // 0x2D
        DEC(L);
    }
    void CPU::instr_LD_L_n8() {          // 0x2E
        L = fetch_byte();
    }
    void CPU::instr_CPL() {              // 0x2F
        A = static_cast<uint8_t>(~A);

        set_flag_n(true);
        set_flag_h(true);
    }

    // --- Row 0x3_ ---
    void CPU::instr_JR_NC_n8() {         // 0x30
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (!get_flag_c()) {
            tick();
            PC += offset;
        }
    }
    void CPU::instr_LD_SP_n16() {        // 0x31
        SP = fetch_word();
    }
    void CPU::instr_LD_mHL_minus_A() {   // 0x32
        write_byte(HL.word--, A);
    }
    void CPU::instr_INC_SP() {           // 0x33
        tick();
        SP++;
    }
    void CPU::instr_INC_mHL() {          // 0x34
        uint8_t value = read_byte(HL.word);
        INC(value);
        write_byte(HL.word, value);
    }
    void CPU::instr_DEC_mHL() {          // 0x35
        uint8_t value = read_byte(HL.word);
        DEC(value);
        write_byte(HL.word, value);
    }
    void CPU::instr_LD_mHL_n8() {        // 0x36
        uint8_t value = fetch_byte();
        write_byte(HL.word, value);
    }
    void CPU::instr_SCF() {              // 0x37
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(true);
    }
    void CPU::instr_JR_C_n8() {          // 0x38
        int8_t offset = static_cast<int8_t>(fetch_byte());
        if (get_flag_c()) {
            tick();
            PC += offset;
        }
    }
    void CPU::instr_ADD_HL_SP() {        // 0x39
        ADD_HL(SP);
    }
    void CPU::instr_LD_A_mHL_minus() {   // 0x3A
        A = read_byte(HL.word--);
    }
    void CPU::instr_DEC_SP() {           // 0x3B
        tick();
        SP--;
    }
    void CPU::instr_INC_A() {            // 0x3C
        INC(A);
    }
    void CPU::instr_DEC_A() {            // 0x3D
        DEC(A);
    }
    void CPU::instr_LD_A_n8() {          // 0x3E
        A = fetch_byte();
    }
    void CPU::instr_CCF() {              // 0x3F
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(!get_flag_c());
    }

    // --- Row 0x4_ ---
    void CPU::instr_LD_B_B() {        }                    // 0x40
    void CPU::instr_LD_B_C() { B = C; }                    // 0x41
    void CPU::instr_LD_B_D() { B = D; }                    // 0x42
    void CPU::instr_LD_B_E() { B = E; }                    // 0x43
    void CPU::instr_LD_B_H() { B = H; }                    // 0x44
    void CPU::instr_LD_B_L() { B = L; }                    // 0x45
    void CPU::instr_LD_B_mHL() { B = read_byte(HL.word); } // 0x46
    void CPU::instr_LD_B_A() { B = A; }                    // 0x47
    void CPU::instr_LD_C_B() { C = B; }                    // 0x48
    void CPU::instr_LD_C_C() {        }                    // 0x49
    void CPU::instr_LD_C_D() { C = D; }                    // 0x4A
    void CPU::instr_LD_C_E() { C = E; }                    // 0x4B
    void CPU::instr_LD_C_H() { C = H; }                    // 0x4C
    void CPU::instr_LD_C_L() { C = L; }                    // 0x4D
    void CPU::instr_LD_C_mHL() { C = read_byte(HL.word); } // 0x4E
    void CPU::instr_LD_C_A() { C = A; }                    // 0x4F

    // --- Row 0x5_ ---
    void CPU::instr_LD_D_B() { D = B; }                    // 0x50
    void CPU::instr_LD_D_C() { D = C; }                    // 0x51
    void CPU::instr_LD_D_D() {        }                    // 0x52
    void CPU::instr_LD_D_E() { D = E; }                    // 0x53
    void CPU::instr_LD_D_H() { D = H; }                    // 0x54
    void CPU::instr_LD_D_L() { D = L; }                    // 0x55
    void CPU::instr_LD_D_mHL() { D = read_byte(HL.word); } // 0x56
    void CPU::instr_LD_D_A() { D = A; }                    // 0x57
    void CPU::instr_LD_E_B() { E = B; }                    // 0x58
    void CPU::instr_LD_E_C() { E = C; }                    // 0x59
    void CPU::instr_LD_E_D() { E = D; }                    // 0x5A
    void CPU::instr_LD_E_E() {        }                    // 0x5B
    void CPU::instr_LD_E_H() { E = H; }                    // 0x5C
    void CPU::instr_LD_E_L() { E = L; }                    // 0x5D
    void CPU::instr_LD_E_mHL() { E = read_byte(HL.word); } // 0x5E
    void CPU::instr_LD_E_A() { E = A; }                    // 0x5F

    // --- Row 0x6_ ---
    void CPU::instr_LD_H_B() { H = B; }                    // 0x60
    void CPU::instr_LD_H_C() { H = C; }                    // 0x61
    void CPU::instr_LD_H_D() { H = D; }                    // 0x62
    void CPU::instr_LD_H_E() { H = E; }                    // 0x63
    void CPU::instr_LD_H_H() {        }                    // 0x64
    void CPU::instr_LD_H_L() { H = L; }                    // 0x65
    void CPU::instr_LD_H_mHL() { H = read_byte(HL.word); } // 0x66
    void CPU::instr_LD_H_A() { H = A; }                    // 0x67
    void CPU::instr_LD_L_B() { L = B; }                    // 0x68
    void CPU::instr_LD_L_C() { L = C; }                    // 0x69
    void CPU::instr_LD_L_D() { L = D; }                    // 0x6A
    void CPU::instr_LD_L_E() { L = E; }                    // 0x6B
    void CPU::instr_LD_L_H() { L = H; }                    // 0x6C
    void CPU::instr_LD_L_L() {        }                    // 0x6D
    void CPU::instr_LD_L_mHL() { L = read_byte(HL.word); } // 0x6E
    void CPU::instr_LD_L_A() { L = A; }                    // 0x6F

    // --- Row 0x7_ ---
    void CPU::instr_LD_mHL_B() { write_byte(HL.word, B); } // 0x70
    void CPU::instr_LD_mHL_C() { write_byte(HL.word, C); } // 0x71
    void CPU::instr_LD_mHL_D() { write_byte(HL.word, D); } // 0x72
    void CPU::instr_LD_mHL_E() { write_byte(HL.word, E); } // 0x73
    void CPU::instr_LD_mHL_H() { write_byte(HL.word, H); } // 0x74
    void CPU::instr_LD_mHL_L() { write_byte(HL.word, L); } // 0x75
    void CPU::instr_HALT() {
        is_halted = true;
        
    }                                                                   // 0x76
    void CPU::instr_LD_mHL_A() { write_byte(HL.word, A); } // 0x77
    void CPU::instr_LD_A_B() { A = B; }                    // 0x78
    void CPU::instr_LD_A_C() { A = C; }                    // 0x79
    void CPU::instr_LD_A_D() { A = D; }                    // 0x7A
    void CPU::instr_LD_A_E() { A = E; }                    // 0x7B
    void CPU::instr_LD_A_H() { A = H; }                    // 0x7C
    void CPU::instr_LD_A_L() { A = L; }                    // 0x7D
    void CPU::instr_LD_A_mHL() { A = read_byte(HL.word); } // 0x7E
    void CPU::instr_LD_A_A() {        }                    // 0x7F

    // --- Row 0x8_ ---
    void CPU::instr_ADD_A_B() { ADD(A, B); }                  // 0x80
    void CPU::instr_ADD_A_C() { ADD(A, C); }                  // 0x81
    void CPU::instr_ADD_A_D() { ADD(A, D); }                  // 0x82
    void CPU::instr_ADD_A_E() { ADD(A, E); }                  // 0x83
    void CPU::instr_ADD_A_H() { ADD(A, H); }                  // 0x84
    void CPU::instr_ADD_A_L() { ADD(A, L); }                  // 0x85
    void CPU::instr_ADD_A_mHL() {                                        // 0x86
        ADD(A, read_byte(HL.word));
    }
    void CPU::instr_ADD_A_A() { ADD(A, A); }                  // 0x87
    void CPU::instr_ADC_A_B() { ADC(A, B); }                  // 0x88
    void CPU::instr_ADC_A_C() { ADC(A, C); }                  // 0x89
    void CPU::instr_ADC_A_D() { ADC(A, D); }                  // 0x8A
    void CPU::instr_ADC_A_E() { ADC(A, E); }                  // 0x8B
    void CPU::instr_ADC_A_H() { ADC(A, H); }                  // 0x8C
    void CPU::instr_ADC_A_L() { ADC(A, L); }                  // 0x8D
    void CPU::instr_ADC_A_mHL() {                                        // 0x8E
        ADC(A, read_byte(HL.word));
    }
    void CPU::instr_ADC_A_A() { ADC(A, A); }                  // 0x8F

    // --- Row 0x9_ ---
    void CPU::instr_SUB_A_B() { SUB(A, B); }                    // 0x90
    void CPU::instr_SUB_A_C() { SUB(A, C); }                    // 0x91
    void CPU::instr_SUB_A_D() { SUB(A, D); }                    // 0x92
    void CPU::instr_SUB_A_E() { SUB(A, E); }                    // 0x93
    void CPU::instr_SUB_A_H() { SUB(A, H); }                    // 0x94
    void CPU::instr_SUB_A_L() { SUB(A, L); }                    // 0x95
    void CPU::instr_SUB_A_mHL() {                                                 // 0x96
        SUB(A, read_byte(HL.word));
    }
    void CPU::instr_SUB_A_A() { SUB(A, A); }                  // 0x97
    void CPU::instr_SBC_A_B() { SBC(A, B); }                  // 0x98
    void CPU::instr_SBC_A_C() { SBC(A, C); }                  // 0x99
    void CPU::instr_SBC_A_D() { SBC(A, D); }                  // 0x9A
    void CPU::instr_SBC_A_E() { SBC(A, E); }                  // 0x9B
    void CPU::instr_SBC_A_H() { SBC(A, H); }                  // 0x9C
    void CPU::instr_SBC_A_L() { SBC(A, L); }                  // 0x9D
    void CPU::instr_SBC_A_mHL() {
        SBC(A, read_byte(HL.word));
    }                                                                           // 0x9E
    void CPU::instr_SBC_A_A() { SBC(A, A); }                  // 0x9F

    // --- Row 0xA_ ---
    void CPU::instr_AND_A_B() { AND_A(B); }              // 0xA0
    void CPU::instr_AND_A_C() { AND_A(C); }              // 0xA1
    void CPU::instr_AND_A_D() { AND_A(D); }              // 0xA2
    void CPU::instr_AND_A_E() { AND_A(E); }              // 0xA3
    void CPU::instr_AND_A_H() { AND_A(H); }              // 0xA4
    void CPU::instr_AND_A_L() { AND_A(L); }              // 0xA5
    void CPU::instr_AND_A_mHL() {
        AND_A(read_byte(HL.word));
    }                                                    // 0xA6
    void CPU::instr_AND_A_A() { AND_A(A); }              // 0xA7
    void CPU::instr_XOR_A_B() { XOR_A(B); }              // 0xA8
    void CPU::instr_XOR_A_C() { XOR_A(C); }              // 0xA9
    void CPU::instr_XOR_A_D() { XOR_A(D); }              // 0xAA
    void CPU::instr_XOR_A_E() { XOR_A(E); }              // 0xAB
    void CPU::instr_XOR_A_H() { XOR_A(H); }              // 0xAC
    void CPU::instr_XOR_A_L() { XOR_A(L); }              // 0xAD
    void CPU::instr_XOR_A_mHL() {
        XOR_A(read_byte(HL.word));
    }                                                    // 0xAE
    void CPU::instr_XOR_A_A() { XOR_A(A); }              // 0xAF

    // --- Row 0xB_ ---
    void CPU::instr_OR_A_B() { OR_A(B); }                // 0xB0
    void CPU::instr_OR_A_C() { OR_A(C); }                // 0xB1
    void CPU::instr_OR_A_D() { OR_A(D); }                // 0xB2
    void CPU::instr_OR_A_E() { OR_A(E); }                // 0xB3
    void CPU::instr_OR_A_H() { OR_A(H); }                // 0xB4
    void CPU::instr_OR_A_L() { OR_A(L); }                // 0xB5
    void CPU::instr_OR_A_mHL() {
        OR_A(read_byte(HL.word));
    }                                                    // 0xB6
    void CPU::instr_OR_A_A() { OR_A(A); }                // 0xB7

    void CPU::instr_CP_A_B() { CP_A(B); }                // 0xB8
    void CPU::instr_CP_A_C() { CP_A(C); }                // 0xB9
    void CPU::instr_CP_A_D() { CP_A(D); }                // 0xBA
    void CPU::instr_CP_A_E() { CP_A(E); }                // 0xBB
    void CPU::instr_CP_A_H() { CP_A(H); }                // 0xBC
    void CPU::instr_CP_A_L() { CP_A(L); }                // 0xBD
    void CPU::instr_CP_A_mHL() {
        CP_A(read_byte(HL.word));
    }                                                    // 0xBE
    void CPU::instr_CP_A_A() { CP_A(A); }                // 0xBF

    // --- Row 0xC_ ---
    void CPU::instr_RET_NZ() {           // 0xC0
        tick();
        if (!get_flag_z()) {
            tick();
            PC = pop_16bit();
        }
    }
    void CPU::instr_POP_BC() {           // 0xC1
        BC.word = pop_16bit();
    }
    void CPU::instr_JP_NZ_n16() {        // 0xC2
        uint16_t address = fetch_word();
        if (!get_flag_z()) {
            tick();
            PC = address; 
        }
    }
    void CPU::instr_JP_n16() {           // 0xC3
        uint16_t address = fetch_word();
        tick();
        PC = address;
    }
    void CPU::instr_CALL_NZ_n16() {      // 0xC4
        uint16_t address = fetch_word();
        if (!get_flag_z()) {
            push_16bit(PC);
            PC = address;
        }
    }
    void CPU::instr_PUSH_BC() {              // 0xC5
        push_16bit(BC.word);
    }
    void CPU::instr_ADD_A_n8() {             // 0xC6
        ADD(A, fetch_byte());
    }
    void CPU::instr_RST_00H() {              // 0xC7
        push_16bit(PC);
        PC = 0x0000;
    }
    void CPU::instr_RET_Z() {                // 0xC8
        tick();
        if (get_flag_z()) {
            tick();
            PC = pop_16bit();
        }
    }
    void CPU::instr_RET() {                  // 0xC9
        tick();
        PC = pop_16bit();
    }
    void CPU::instr_JP_Z_n16() {             // 0xCA
        uint16_t address = fetch_word();
        if (get_flag_z()) {
            tick();
            PC = address;
        }
    }
    void CPU::instr_PREFIX_CB() {            // 0xCB
        execute_cb();
    }
    void CPU::instr_CALL_Z_n16() {           // 0xCC
        uint16_t address = fetch_word();
        if (get_flag_z()) {
            push_16bit(PC);
            PC = address;
        }
    }
    void CPU::instr_CALL_n16() {             // 0xCD
        uint16_t address = fetch_word();
        push_16bit(PC);
        PC = address;
    }
    void CPU::instr_ADC_A_n8() {             // 0xCE
        ADC(A, fetch_byte());
    }
    void CPU::instr_RST_08H() {              // 0xCF
        push_16bit(PC);
        PC = 0x0008;
    }

    // --- Row 0xD_ ---
    void CPU::instr_RET_NC() {               // 0xD0
        tick();
        if (!get_flag_c()) {
            tick();
            PC = pop_16bit();
        }
    }
    void CPU::instr_POP_DE() {               // 0xD1
        DE.word = pop_16bit();
    }
    void CPU::instr_JP_NC_n16() {            // 0xD2
        uint16_t address = fetch_word();
        if (!get_flag_c()) {
            tick();
            PC = address;
        }
    }
    void CPU::instr_UNUSED_D3() { }          // 0xD3
    void CPU::instr_CALL_NC_n16() {          // 0xD4
        uint16_t address = fetch_word();
        if (!get_flag_c()) {
            push_16bit(PC);
            PC = address;
        }
    }
    void CPU::instr_PUSH_DE() {              // 0xD5
        push_16bit(DE.word);
    }
    void CPU::instr_SUB_A_n8() {             // 0xD6
        SUB(A, fetch_byte());
    }
    void CPU::instr_RST_10H() {              // 0xD7
        push_16bit(PC);
        PC = 0x0010;
    }
    void CPU::instr_RET_C() {                // 0xD8
        tick();
        if (get_flag_c()) {
            tick();
            PC = pop_16bit();
        }
    }
    void CPU::instr_RETI() {                 // 0xD9
        IME = true;
        uint16_t target_address = pop_16bit();
        tick();
        PC = target_address;
    }
    void CPU::instr_JP_C_n16() {             // 0xDA
        uint16_t address = fetch_word();
        if (get_flag_c()) {
            tick();
            PC = address;
        }
    }
    void CPU::instr_UNUSED_DB() { }          // 0xDB
    void CPU::instr_CALL_C_n16() {           // 0xDC
        uint16_t address = fetch_word();
        if (get_flag_c()) {
            push_16bit(PC);
            PC = address;
        }
    }
    void CPU::instr_UNUSED_DD() { }          // 0xDD
    void CPU::instr_SBC_A_n8() {             // 0xDE
        SBC(A, fetch_byte());
    }
    void CPU::instr_RST_18H() {              // 0xDF
        push_16bit(PC);
        PC = 0x0018;
    }

    // --- Row 0xE_ ---
    void CPU::instr_LDH_mn8_A() {            // 0xE0
        uint8_t offset = fetch_byte();

        write_byte(static_cast<uint16_t>(0xFF00 | offset), A);
    }
    void CPU::instr_POP_HL() {               // 0xE1
        HL.word = pop_16bit();
    }
    void CPU::instr_LD_mC_A() {              // 0xE2
        write_byte(0xFF00 | C, A);
    }
    void CPU::instr_UNUSED_E3() { }          // 0xE3
    void CPU::instr_UNUSED_E4() { }          // 0xE4
    void CPU::instr_PUSH_HL() {              // 0xE5
        push_16bit(HL.word);
    }
    void CPU::instr_AND_A_n8() {             // 0xE6
        AND_A(fetch_byte());
    }
    void CPU::instr_RST_20H() {              // 0xE7
        push_16bit(PC);
        PC = 0x0020;
    }
    void CPU::instr_ADD_SP_e8() {            // 0xE8
        int8_t value = static_cast<int8_t>(fetch_byte());

        bool half_carry = ((SP & 0x0F) + (value & 0x0F)) > 0x0F;
        bool carry = ((SP & 0xFF) + (value & 0xFF)) > 0xFF;
        
        tick();
        SP += value;
        
        tick();
        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(carry);
    }
    void CPU::instr_JP_HL() {                // 0xE9
        PC = HL.word;
    }
    void CPU::instr_LD_mn16_A() {            // 0xEA
        uint16_t address = fetch_word();

        write_byte(address, A);
    }
    void CPU::instr_UNUSED_EB() { }          // 0xEB
    void CPU::instr_UNUSED_EC() { }          // 0xEC
    void CPU::instr_UNUSED_ED() { }          // 0xED
    void CPU::instr_XOR_A_n8() {             // 0xEE
        XOR_A(fetch_byte());
    }
    void CPU::instr_RST_28H() {              // 0xEF
        push_16bit(PC);
        PC = 0x0028;
    }

    // --- Row 0xF_ ---
    void CPU::instr_LDH_A_mn8() {            // 0xF0
        uint8_t offset = fetch_byte();
        A = read_byte(static_cast<uint16_t>(0xFF00 | offset));
    }
    void CPU::instr_POP_AF() {               // 0xF1
        AF.word = pop_16bit() & 0xFFF0;
    }
    void CPU::instr_LD_A_mC() {              // 0xF2
        A = read_byte(static_cast<uint16_t>(0xFF00 | C));
    }
    void CPU::instr_DI() {                   // 0xF3
        EI_delay = -1;
        IME = false;
    }
    void CPU::instr_UNUSED_F4() { }          // 0xF4
    void CPU::instr_PUSH_AF() {              // 0xF5
        push_16bit(AF.word);
    }
    void CPU::instr_OR_A_n8() {              // 0xF6
        OR_A(fetch_byte());
    }
    void CPU::instr_RST_30H() {              // 0xF7
        push_16bit(PC);
        PC = 0x0030;
    }
    void CPU::instr_LD_HL_SP_plus_e8() {     // 0xF8
        int8_t offset = static_cast<int8_t>(fetch_byte());

        bool half_carry = ((SP & 0x0F) + (offset & 0x0F)) > 0x0F;
        bool carry = ((SP & 0xFF) + (offset & 0xFF)) > 0xFF;

        tick();
        HL.word = static_cast<uint16_t>(SP + offset);

        set_flag_z(false);
        set_flag_n(false);
        set_flag_h(half_carry);
        set_flag_c(carry);
    }
    void CPU::instr_LD_SP_HL() {             // 0xF9
        tick();
        SP = HL.word;
    }
    void CPU::instr_LD_A_mn16() {            // 0xFA
        uint16_t address = fetch_word();
        A = read_byte(address);
    }
    void CPU::instr_EI() {                   // 0xFB
        EI_delay = 1;
    }
    void CPU::instr_UNUSED_FC() { }          // 0xFC
    void CPU::instr_UNUSED_FD() { }          // 0xFD
    void CPU::instr_CP_A_n8() {              // 0xFE
        CP_A(fetch_byte());
    }
    void CPU::instr_RST_38H() {              // 0xFF
        push_16bit(PC);
        PC = 0x0038;
    }

    // =========================================================================
    // PREFIX CB OPCODES IMPLEMENTATION (0xCB 0x00 - 0xCB 0xFF)
    // =========================================================================

    void CPU::RLC(uint8_t& to) {
        uint8_t b7 = (to & 0x80) >> 7;
        to = static_cast<uint8_t>((to << 1) | b7);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
    }

    void CPU::RRC(uint8_t& to) {
        uint8_t b0 = static_cast<uint8_t>((to & 0x01) << 7);
        to = b0 | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
    }

    void CPU::RL(uint8_t& to) {
        uint8_t b7 = (to & 0x80) >> 7;
        to = static_cast<uint8_t>((to << 1) | static_cast<uint8_t>(get_flag_c()));

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
    }

    void CPU::RR(uint8_t& to) {
        bool b0 = (to & 0x01) != 0;
        uint8_t old_carry = get_flag_c() ? 1 : 0;
        to = static_cast<uint8_t>(old_carry << 7) | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0);
    }

    void CPU::SLA(uint8_t& to) {
        uint8_t b7 = (to & 0x80) >> 7;
        to = static_cast<uint8_t>((to << 1) | static_cast<uint8_t>(0));

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b7 == 1);
    }

    void CPU::SRA(uint8_t& to) {
        uint8_t b7 = (to & 0x80);
        uint8_t b0 = static_cast<uint8_t>((to & 0x01) << 7);
        to = b7 | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
    }

    void CPU::SRL(uint8_t& to) {
        uint8_t b0 = static_cast<uint8_t>((to & 0x01) << 7);
        to = static_cast<uint8_t>(0) | (to >> 1);

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(b0 == 0x80);
    }

    void CPU::SWAP(uint8_t& to) {
        uint8_t higher = to & 0xF0;
        uint8_t lower = to & 0x0F;

        to = static_cast<uint8_t>((higher >> 4) | (lower << 4));

        set_flag_z(to == 0);
        set_flag_n(false);
        set_flag_h(false);
        set_flag_c(false);
    }

    void CPU::BIT(uint8_t bit, uint8_t &reg) {
        bool is_set = (reg & (1 << bit)) != 0;

        set_flag_z(!is_set);
        set_flag_n(false);
        set_flag_h(true);
    }

    void CPU::RES(uint8_t bit, uint8_t &reg) {
        reg &= ~(1 << bit);
    }

    void CPU::SET(uint8_t bit, uint8_t &reg) {
        reg |= (1 << bit);
    }

    // =========================================================================
    // PREFIX CB OPCODES IMPLEMENTATION (0xCB 0x00 - 0xCB 0xFF)
    // =========================================================================

    // --- Row 0x0_ (RLC & RRC) ---
    void CPU::instr_cb_RLC_B() { RLC(B); }
    void CPU::instr_cb_RLC_C() { RLC(C); }
    void CPU::instr_cb_RLC_D() { RLC(D); }
    void CPU::instr_cb_RLC_E() { RLC(E); }
    void CPU::instr_cb_RLC_H() { RLC(H); }
    void CPU::instr_cb_RLC_L() { RLC(L); }
    void CPU::instr_cb_RLC_mHL() {
        uint8_t v = read_byte(HL.word);
        RLC(v);
        write_byte(HL.word, v);
    }
    void CPU::instr_cb_RLC_A() { RLC(A); }
    void CPU::instr_cb_RRC_B() { RRC(B); }
    void CPU::instr_cb_RRC_C() { RRC(C); }
    void CPU::instr_cb_RRC_D() { RRC(D); }
    void CPU::instr_cb_RRC_E() { RRC(E); }
    void CPU::instr_cb_RRC_H() { RRC(H); }
    void CPU::instr_cb_RRC_L() { RRC(L); }
    void CPU::instr_cb_RRC_mHL() {
        uint8_t v = read_byte(HL.word);
        RRC(v);
        write_byte(HL.word, v);
    }
    void CPU::instr_cb_RRC_A() { RRC(A); }

    // --- Row 0x1_ (RL & RR) ---
    void CPU::instr_cb_RL_B() { RL(B); }
    void CPU::instr_cb_RL_C() { RL(C); }
    void CPU::instr_cb_RL_D() { RL(D); }
    void CPU::instr_cb_RL_E() { RL(E); }
    void CPU::instr_cb_RL_H() { RL(H); }
    void CPU::instr_cb_RL_L() { RL(L); }
    void CPU::instr_cb_RL_mHL() {
        uint8_t v = read_byte(HL.word);
        RL(v);
        write_byte(HL.word, v);
    }
    void CPU::instr_cb_RL_A() { RL(A); }
    void CPU::instr_cb_RR_B() { RR(B); }
    void CPU::instr_cb_RR_C() { RR(C); }
    void CPU::instr_cb_RR_D() { RR(D); }
    void CPU::instr_cb_RR_E() { RR(E); }
    void CPU::instr_cb_RR_H() { RR(H); }
    void CPU::instr_cb_RR_L() { RR(L); }
    void CPU::instr_cb_RR_mHL() {
        uint8_t v = read_byte(HL.word);
        RR(v);
        write_byte(HL.word, v);
    }
    void CPU::instr_cb_RR_A() { RR(A); }

    // --- Row 0x2_ (SLA & SRA) ---
    void CPU::instr_cb_SLA_B() { SLA(B); }
    void CPU::instr_cb_SLA_C() { SLA(C); }
    void CPU::instr_cb_SLA_D() { SLA(D); }
    void CPU::instr_cb_SLA_E() { SLA(E); }
    void CPU::instr_cb_SLA_H() { SLA(H); }
    void CPU::instr_cb_SLA_L() { SLA(L); }
    void CPU::instr_cb_SLA_mHL() {
         uint8_t v = read_byte(HL.word);
         SLA(v);
         write_byte(HL.word, v);
    }
    void CPU::instr_cb_SLA_A() { SLA(A); }
    void CPU::instr_cb_SRA_B() { SRA(B); }
    void CPU::instr_cb_SRA_C() { SRA(C); }
    void CPU::instr_cb_SRA_D() { SRA(D); }
    void CPU::instr_cb_SRA_E() { SRA(E); }
    void CPU::instr_cb_SRA_H() { SRA(H); }
    void CPU::instr_cb_SRA_L() { SRA(L); }
    void CPU::instr_cb_SRA_mHL() {
         uint8_t v = read_byte(HL.word);
         SRA(v);
         write_byte(HL.word, v);
    }
    void CPU::instr_cb_SRA_A() { SRA(A); }

    // --- Row 0x3_ (SWAP & SRL) ---
    void CPU::instr_cb_SWAP_B() { SWAP(B); }
    void CPU::instr_cb_SWAP_C() { SWAP(C); }
    void CPU::instr_cb_SWAP_D() { SWAP(D); }
    void CPU::instr_cb_SWAP_E() { SWAP(E); }
    void CPU::instr_cb_SWAP_H() { SWAP(H); }
    void CPU::instr_cb_SWAP_L() { SWAP(L); }
    void CPU::instr_cb_SWAP_mHL() {
         uint8_t v = read_byte(HL.word);
         SWAP(v);
         write_byte(HL.word, v);
    }
    void CPU::instr_cb_SWAP_A() { SWAP(A); }
    void CPU::instr_cb_SRL_B() { SRL(B); }
    void CPU::instr_cb_SRL_C() { SRL(C); }
    void CPU::instr_cb_SRL_D() { SRL(D); }
    void CPU::instr_cb_SRL_E() { SRL(E); }
    void CPU::instr_cb_SRL_H() { SRL(H); }
    void CPU::instr_cb_SRL_L() { SRL(L); }
    void CPU::instr_cb_SRL_mHL() {
         uint8_t v = read_byte(HL.word);
         SRL(v);
         write_byte(HL.word, v);
    }
    void CPU::instr_cb_SRL_A() { SRL(A); }

    // --- Row 0x4_ (BIT 0 & BIT 1) ---
    void CPU::instr_cb_BIT_0_B() { BIT(0, B); }
    void CPU::instr_cb_BIT_0_C() { BIT(0, C); }
    void CPU::instr_cb_BIT_0_D() { BIT(0, D); }
    void CPU::instr_cb_BIT_0_E() { BIT(0, E); }
    void CPU::instr_cb_BIT_0_H() { BIT(0, H); }
    void CPU::instr_cb_BIT_0_L() { BIT(0, L); }
    void CPU::instr_cb_BIT_0_mHL() {
        uint8_t v = read_byte(HL.word);
        BIT(0, v);
    }
    void CPU::instr_cb_BIT_0_A() { BIT(0, A); }
    void CPU::instr_cb_BIT_1_B() { BIT(1, B); }
    void CPU::instr_cb_BIT_1_C() { BIT(1, C); }
    void CPU::instr_cb_BIT_1_D() { BIT(1, D); }
    void CPU::instr_cb_BIT_1_E() { BIT(1, E); }
    void CPU::instr_cb_BIT_1_H() { BIT(1, H); }
    void CPU::instr_cb_BIT_1_L() { BIT(1, L); }
    void CPU::instr_cb_BIT_1_mHL() {
         uint8_t v = read_byte(HL.word);
         BIT(1, v);
    }
    void CPU::instr_cb_BIT_1_A() { BIT(1, A); }

    // --- Row 0x5_ (BIT 2 & BIT 3) ---
    void CPU::instr_cb_BIT_2_B() { BIT(2, B); }
    void CPU::instr_cb_BIT_2_C() { BIT(2, C); }
    void CPU::instr_cb_BIT_2_D() { BIT(2, D); }
    void CPU::instr_cb_BIT_2_E() { BIT(2, E); }
    void CPU::instr_cb_BIT_2_H() { BIT(2, H); }
    void CPU::instr_cb_BIT_2_L() { BIT(2, L); }
    void CPU::instr_cb_BIT_2_mHL() {
         uint8_t v = read_byte(HL.word);
         BIT(2, v);
    }
    void CPU::instr_cb_BIT_2_A() { BIT(2, A); }
    void CPU::instr_cb_BIT_3_B() { BIT(3, B); }
    void CPU::instr_cb_BIT_3_C() { BIT(3, C); }
    void CPU::instr_cb_BIT_3_D() { BIT(3, D); }
    void CPU::instr_cb_BIT_3_E() { BIT(3, E); }
    void CPU::instr_cb_BIT_3_H() { BIT(3, H); }
    void CPU::instr_cb_BIT_3_L() { BIT(3, L); }
    void CPU::instr_cb_BIT_3_mHL() {
         uint8_t v = read_byte(HL.word);
         BIT(3, v);
    }
    void CPU::instr_cb_BIT_3_A() { BIT(3, A); }

    // --- Row 0x6_ (BIT 4 & BIT 5) ---
    void CPU::instr_cb_BIT_4_B() { BIT(4, B); }
    void CPU::instr_cb_BIT_4_C() { BIT(4, C); }
    void CPU::instr_cb_BIT_4_D() { BIT(4, D); }
    void CPU::instr_cb_BIT_4_E() { BIT(4, E); }
    void CPU::instr_cb_BIT_4_H() { BIT(4, H); }
    void CPU::instr_cb_BIT_4_L() { BIT(4, L); }
    void CPU::instr_cb_BIT_4_mHL() {
         uint8_t v = read_byte(HL.word);
         BIT(4, v);
    }
    void CPU::instr_cb_BIT_4_A() { BIT(4, A); }
    void CPU::instr_cb_BIT_5_B() { BIT(5, B); }
    void CPU::instr_cb_BIT_5_C() { BIT(5, C); }
    void CPU::instr_cb_BIT_5_D() { BIT(5, D); }
    void CPU::instr_cb_BIT_5_E() { BIT(5, E); }
    void CPU::instr_cb_BIT_5_H() { BIT(5, H); }
    void CPU::instr_cb_BIT_5_L() { BIT(5, L); }
    void CPU::instr_cb_BIT_5_mHL() {
        uint8_t v = read_byte(HL.word);
        BIT(5, v);
        
    }
    void CPU::instr_cb_BIT_5_A() { BIT(5, A); }

    // --- Row 0x7_ (BIT 6 & BIT 7) ---
    void CPU::instr_cb_BIT_6_B() { BIT(6, B); }
    void CPU::instr_cb_BIT_6_C() { BIT(6, C); }
    void CPU::instr_cb_BIT_6_D() { BIT(6, D); }
    void CPU::instr_cb_BIT_6_E() { BIT(6, E); }
    void CPU::instr_cb_BIT_6_H() { BIT(6, H); }
    void CPU::instr_cb_BIT_6_L() { BIT(6, L); }
    void CPU::instr_cb_BIT_6_mHL() {
        uint8_t v = read_byte(HL.word);
        BIT(6, v);
        
    }
    void CPU::instr_cb_BIT_6_A() { BIT(6, A); }
    void CPU::instr_cb_BIT_7_B() { BIT(7, B); }
    void CPU::instr_cb_BIT_7_C() { BIT(7, C); }
    void CPU::instr_cb_BIT_7_D() { BIT(7, D); }
    void CPU::instr_cb_BIT_7_E() { BIT(7, E); }
    void CPU::instr_cb_BIT_7_H() { BIT(7, H); }
    void CPU::instr_cb_BIT_7_L() { BIT(7, L); }
    void CPU::instr_cb_BIT_7_mHL() {
        uint8_t v = read_byte(HL.word);
        BIT(7, v);
        
    }
    void CPU::instr_cb_BIT_7_A() { BIT(7, A); }

    // --- Row 0x8_ (RES 0 & RES 1) ---

    void CPU::instr_cb_RES_0_B() { RES(0, B); }
    void CPU::instr_cb_RES_0_C() { RES(0, C); }
    void CPU::instr_cb_RES_0_D() { RES(0, D); }
    void CPU::instr_cb_RES_0_E() { RES(0, E); }
    void CPU::instr_cb_RES_0_H() { RES(0, H); }
    void CPU::instr_cb_RES_0_L() { RES(0, L); }
    void CPU::instr_cb_RES_0_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(0, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_0_A() { RES(0, A); }
    void CPU::instr_cb_RES_1_B() { RES(1, B); }
    void CPU::instr_cb_RES_1_C() { RES(1, C); }
    void CPU::instr_cb_RES_1_D() { RES(1, D); }
    void CPU::instr_cb_RES_1_E() { RES(1, E); }
    void CPU::instr_cb_RES_1_H() { RES(1, H); }
    void CPU::instr_cb_RES_1_L() { RES(1, L); }
    void CPU::instr_cb_RES_1_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(1, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_1_A() { RES(1, A); }

    // --- Row 0x9_ (RES 2 & RES 3) ---

    void CPU::instr_cb_RES_2_B() { RES(2, B); }
    void CPU::instr_cb_RES_2_C() { RES(2, C); }
    void CPU::instr_cb_RES_2_D() { RES(2, D); }
    void CPU::instr_cb_RES_2_E() { RES(2, E); }
    void CPU::instr_cb_RES_2_H() { RES(2, H); }
    void CPU::instr_cb_RES_2_L() { RES(2, L); }
    void CPU::instr_cb_RES_2_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(2, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_2_A() { RES(2, A); }
    void CPU::instr_cb_RES_3_B() { RES(3, B); }
    void CPU::instr_cb_RES_3_C() { RES(3, C); }
    void CPU::instr_cb_RES_3_D() { RES(3, D); }
    void CPU::instr_cb_RES_3_E() { RES(3, E); }
    void CPU::instr_cb_RES_3_H() { RES(3, H); }
    void CPU::instr_cb_RES_3_L() { RES(3, L); }
    void CPU::instr_cb_RES_3_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(3, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_3_A() { RES(3, A); }

    // --- Row 0xA_ (RES 4 & RES 5) ---

    void CPU::instr_cb_RES_4_B() { RES(4, B); }
    void CPU::instr_cb_RES_4_C() { RES(4, C); }
    void CPU::instr_cb_RES_4_D() { RES(4, D); }
    void CPU::instr_cb_RES_4_E() { RES(4, E); }
    void CPU::instr_cb_RES_4_H() { RES(4, H); }
    void CPU::instr_cb_RES_4_L() { RES(4, L); }
    void CPU::instr_cb_RES_4_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(4, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_4_A() { RES(4, A); }
    void CPU::instr_cb_RES_5_B() { RES(5, B); }
    void CPU::instr_cb_RES_5_C() { RES(5, C); }
    void CPU::instr_cb_RES_5_D() { RES(5, D); }
    void CPU::instr_cb_RES_5_E() { RES(5, E); }
    void CPU::instr_cb_RES_5_H() { RES(5, H); }
    void CPU::instr_cb_RES_5_L() { RES(5, L); }
    void CPU::instr_cb_RES_5_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(5, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_5_A() { RES(5, A); }

    // --- Row 0xB_ (RES 6 & RES 7) ---

    void CPU::instr_cb_RES_6_B() { RES(6, B); }
    void CPU::instr_cb_RES_6_C() { RES(6, C); }
    void CPU::instr_cb_RES_6_D() { RES(6, D); }
    void CPU::instr_cb_RES_6_E() { RES(6, E); }
    void CPU::instr_cb_RES_6_H() { RES(6, H); }
    void CPU::instr_cb_RES_6_L() { RES(6, L); }
    void CPU::instr_cb_RES_6_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(6, v);
        write_byte(HL.word, v);
        
   }
    void CPU::instr_cb_RES_6_A() { RES(6, A); }
    void CPU::instr_cb_RES_7_B() { RES(7, B); }
    void CPU::instr_cb_RES_7_C() { RES(7, C); }
    void CPU::instr_cb_RES_7_D() { RES(7, D); }
    void CPU::instr_cb_RES_7_E() { RES(7, E); }
    void CPU::instr_cb_RES_7_H() { RES(7, H); }
    void CPU::instr_cb_RES_7_L() { RES(7, L); }
    void CPU::instr_cb_RES_7_mHL() {
        uint8_t v = read_byte(HL.word);
        RES(7, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_RES_7_A() { RES(7, A); }

    // --- Row 0xC_ (SET 0 & SET 1) ---

    void CPU::instr_cb_SET_0_B() { SET(0, B); }
    void CPU::instr_cb_SET_0_C() { SET(0, C); }
    void CPU::instr_cb_SET_0_D() { SET(0, D); }
    void CPU::instr_cb_SET_0_E() { SET(0, E); }
    void CPU::instr_cb_SET_0_H() { SET(0, H); }
    void CPU::instr_cb_SET_0_L() { SET(0, L); }
    void CPU::instr_cb_SET_0_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(0, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_0_A() { SET(0, A); }
    void CPU::instr_cb_SET_1_B() { SET(1, B); }
    void CPU::instr_cb_SET_1_C() { SET(1, C); }
    void CPU::instr_cb_SET_1_D() { SET(1, D); }
    void CPU::instr_cb_SET_1_E() { SET(1, E); }
    void CPU::instr_cb_SET_1_H() { SET(1, H); }
    void CPU::instr_cb_SET_1_L() { SET(1, L); }
    void CPU::instr_cb_SET_1_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(1, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_1_A() { SET(1, A); }

    // --- Row 0xD_ (SET 2 & SET 3) ---

    void CPU::instr_cb_SET_2_B() { SET(2, B); }
    void CPU::instr_cb_SET_2_C() { SET(2, C); }
    void CPU::instr_cb_SET_2_D() { SET(2, D); }
    void CPU::instr_cb_SET_2_E() { SET(2, E); }
    void CPU::instr_cb_SET_2_H() { SET(2, H); }
    void CPU::instr_cb_SET_2_L() { SET(2, L); }
    void CPU::instr_cb_SET_2_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(2, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_2_A() { SET(2, A); }
    void CPU::instr_cb_SET_3_B() { SET(3, B); }
    void CPU::instr_cb_SET_3_C() { SET(3, C); }
    void CPU::instr_cb_SET_3_D() { SET(3, D); }
    void CPU::instr_cb_SET_3_E() { SET(3, E); }
    void CPU::instr_cb_SET_3_H() { SET(3, H); }
    void CPU::instr_cb_SET_3_L() { SET(3, L); }
    void CPU::instr_cb_SET_3_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(3, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_3_A() { SET(3, A); }

    // --- Row 0xE_ (SET 4 & SET 5) ---

    void CPU::instr_cb_SET_4_B() { SET(4, B); }
    void CPU::instr_cb_SET_4_C() { SET(4, C); }
    void CPU::instr_cb_SET_4_D() { SET(4, D); }
    void CPU::instr_cb_SET_4_E() { SET(4, E); }
    void CPU::instr_cb_SET_4_H() { SET(4, H); }
    void CPU::instr_cb_SET_4_L() { SET(4, L); }
    void CPU::instr_cb_SET_4_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(4, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_4_A() { SET(4, A); }
    void CPU::instr_cb_SET_5_B() { SET(5, B); }
    void CPU::instr_cb_SET_5_C() { SET(5, C); }
    void CPU::instr_cb_SET_5_D() { SET(5, D); }
    void CPU::instr_cb_SET_5_E() { SET(5, E); }
    void CPU::instr_cb_SET_5_H() { SET(5, H); }
    void CPU::instr_cb_SET_5_L() { SET(5, L); }
    void CPU::instr_cb_SET_5_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(5, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_5_A() { SET(5, A); }

    // --- Row 0xF_ (SET 6 & SET 7) ---

    void CPU::instr_cb_SET_6_B() { SET(6, B); }
    void CPU::instr_cb_SET_6_C() { SET(6, C); }
    void CPU::instr_cb_SET_6_D() { SET(6, D); }
    void CPU::instr_cb_SET_6_E() { SET(6, E); }
    void CPU::instr_cb_SET_6_H() { SET(6, H); }
    void CPU::instr_cb_SET_6_L() { SET(6, L); }
    void CPU::instr_cb_SET_6_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(6, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_6_A() { SET(6, A); }
    void CPU::instr_cb_SET_7_B() { SET(7, B); }
    void CPU::instr_cb_SET_7_C() { SET(7, C); }
    void CPU::instr_cb_SET_7_D() { SET(7, D); }
    void CPU::instr_cb_SET_7_E() { SET(7, E); }
    void CPU::instr_cb_SET_7_H() { SET(7, H); }
    void CPU::instr_cb_SET_7_L() { SET(7, L); }
    void CPU::instr_cb_SET_7_mHL() {
        uint8_t v = read_byte(HL.word);
        SET(7, v);
        write_byte(HL.word, v);
        
    }
    void CPU::instr_cb_SET_7_A() { SET(7, A); }

}
