#include "cartridge.h"
#include <gamekid/rom/header_offsets.h>

using namespace gamekid::rom;

cartridge::cartridge(const byte* rom): _rom(rom) {
}

std::string cartridge::title() const {
    const char* title_ptr = header_offsets::title.start + (char*)_rom;
    const size_t length = strnlen_s(title_ptr, header_offsets::title.length);
    return std::string(title_ptr, length);
}

const byte* cartridge::logo() const {
    return _rom + header_offsets::logo.start;
}

byte cartridge::cgb_flag() const {
    return _rom[header_offsets::cgb_flag.start];
}

word cartridge::new_licensee_code() const {
    return _rom[header_offsets::new_licensee_code.start];
}

destination_code cartridge::dest_code() const {

    const byte value = _rom[header_offsets::dest_code.start];

    if (!is_destination_code_valid(value)) {
        throw std::exception("Destination code is not valid");
    }

    return static_cast<destination_code>(value);
}

ram_size cartridge::ram_size() const {
    
    const byte ram_size_byte = _rom[header_offsets::ram_size.start];

    if (!is_ram_size_valid(ram_size_byte)) {
        throw std::exception("Ram size is not valid");
    }

    return static_cast<rom::ram_size>(ram_size_byte);
}

byte cartridge::old_licensee_code() const {
    return _rom[header_offsets::old_licensee_code.start];
}

byte cartridge::mask_rom_version() const {
    return _rom[header_offsets::mask_rom_version.start];
}

byte cartridge::header_checksum() const {
    return _rom[header_offsets::header_checksum.start];
}

word cartridge::global_checksum() const {
    return _rom[header_offsets::global_checksum.start];
}

byte cartridge::sgb_flag() const {
    return _rom[header_offsets::sdb_flag.start];
}

rom_size cartridge::rom_size() const {
    const byte rom_size_byte = _rom[header_offsets::rom_size.start];

    if (!is_rom_size_valid(rom_size_byte))
        throw std::exception("Rom size byte is not valid");

    return static_cast<rom::rom_size>(rom_size_byte);     
}

