#pragma once
#include <gamekid/utils/types.h>
#include <gamekid/rom/cartridge_header.h>

#include <string>
#include <memory>
#include "rom_map.h"

namespace gamekid::rom {
    class cartridge {
    private:
        std::vector<byte> _rom;
    public:
        explicit cartridge(std::vector<byte>&& rom);
        const std::vector<byte>& data() const;
        std::string title() const;
        const byte* logo() const;
        byte cgb_flag() const;
        word new_licensee_code() const;
        byte sgb_flag() const;
        rom_size rom_size() const;
        ram_size ram_size() const;
        destination_code dest_code() const;
        byte old_licensee_code() const;
        byte mask_rom_version() const;
        byte header_checksum() const;
        word global_checksum() const;
        byte calculate_header_checksum() const;
        bool validate_header_checksum() const;
        word calculate_global_checksum() const;
        bool validate_global_checksum() const;
        std::unique_ptr<rom_map> create_rom_map() const;
    };
}
