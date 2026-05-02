//
// Created by Andreas Sabelfeld on 24.04.2026.
//

#pragma once

#include <cstdint>
#include <string>
#include <string_view>
#include <vector>

namespace gb::core {
    class Cartridge {
    public:
        Cartridge(std::string_view file_path);
        uint8_t read_rom(uint16_t address) const;
        uint8_t read_sram(uint16_t address) const;
        void write(uint16_t address, uint8_t value);

    private:
        std::vector<uint8_t> rom;                           // vector since rom sizes are dynamic
        std::vector<uint8_t> sram;                          // vector since sram sizes are dynamic

        uint32_t current_rom_bank;
        uint32_t current_sram_bank;
        bool ram_enabled{};

        void load_rom(std::string_view file_path);
        void determine_ram_size();
        void save_state(std::string_view file_path);

    };
}
