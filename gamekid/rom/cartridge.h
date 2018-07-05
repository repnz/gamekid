#pragma once
#include <gamekid/utils/types.h>
#include <gamekid/rom/cartridge_type.h>

#include <string>
#include <vector>

namespace gamekid::rom {
    class cartridge {
        std::string title() const;
        std::vector<byte> logo() const;
        byte cbg_flag() const;
        cartridge_type type() const;
        word new_licensee_code() const;
        byte sdb_flag() const;
        byte rom_size() const;
        byte ram_size() const;
        byte dest_code() const;
        byte old_licensee_code() const;
        byte mask_rom_version() const;
        byte header_checksum() const;
        word global_checksum() const;
    };
}