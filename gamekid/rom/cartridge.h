#pragma once
#include <gamekid/utils/types.h>
#include <gamekid/rom/cartridge_header.h>

#include <string>

namespace gamekid::rom {
    class cartridge {
    private:
        const byte* _rom;
    public:
        explicit cartridge(const byte* rom);

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
    };
}