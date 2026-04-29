//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#include "Cartridge.h"
#include <fstream>
#include <iostream>

namespace gb::core {
    Cartridge::Cartridge(std::string_view file_path) {
        load_rom(file_path);
        determine_ram_size();

        current_rom_bank = 1;
        current_sram_bank = 0;
        ram_enabled = false;
    }

    void Cartridge::load_rom(std::string_view file_path) {
        std::ifstream file(file_path.data(), std::ios::binary | std::ios::ate);

        if (!file.is_open()) {
            throw std::runtime_error(std::string("Can't open ROM file: ") + file_path.data());
        }

        std::streamsize size = file.tellg();    // get rom size
        file.seekg(0, std::ios::beg);       // put cursor at beginning of file
        rom.resize(size);

        if (file.read(reinterpret_cast<char*>(rom.data()), size)) {
            std::cout << "Successfully loaded ROM: " << file_path << " (" << size << " bytes)\n";
        } else {
            throw std::runtime_error("Failed to read ROM data.");
        }
    }

    uint8_t Cartridge::read_rom(uint16_t address) const {
        if (address < rom.size()) {
            return rom[address];
        }

        return 0xFF;
    }

    uint8_t Cartridge::read_sram(uint16_t address) const {
        if (address < sram.size()) {
            if (!ram_enabled || sram.empty()) return 0xFF;      // Locked or doesn't exist

            uint32_t ram_offset = current_sram_bank * 0x2000;
            uint32_t real_index = ram_offset + (address - 0xA000);

            return sram[real_index];
        }

        return 0xFF;
    }

    void Cartridge::write(uint16_t address, uint8_t value) {
        if (address <= 0x1FFF) {
            // Writing 0x0A in the lower nibble enables RAM, any other value disables it
            ram_enabled = ((value & 0x0F) == 0x0A);
        } else if (address >= 0x2000 && address <= 0x3FFF) {    // rom bank switch command
            if (value == 0) value = 1;
            current_rom_bank = value;
        } else if (address >= 0xA000 && address <= 0xBFFF) {    // Actual write to RAM
            if (!ram_enabled || sram.empty()) return;           // Ignore write if locked

            uint32_t ram_offset = current_sram_bank * 0x2000;
            uint32_t real_index = ram_offset + (address - 0xA000);

            sram[real_index] = value;
        }
    }

    void Cartridge::determine_ram_size() {
        uint8_t ram_flag = rom[0x0149];
        switch (ram_flag) {
            case 0x00: sram.resize(0); break;
            case 0x02: sram.resize(8 * 1024); break;
            case 0x03: sram.resize(32 * 1024); break;
            case 0x04: sram.resize(128 * 1024); break;
            case 0x05: sram.resize(64 * 1024); break;
                default: sram.resize(0); break;
        }
    }
}
