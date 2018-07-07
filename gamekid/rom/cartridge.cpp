#include "cartridge.h"
#include <gamekid/rom/header_offsets.h>
#include "rom_only_map.h"

using namespace gamekid::rom;

cartridge::cartridge(std::vector<byte>&& rom): _rom(std::move(rom)) {
}

const std::vector<byte>& gamekid::rom::cartridge::data() const {
    return _rom;
}

std::string cartridge::title() const {
    const char* title_ptr = header_offsets::title.start + (char*)_rom.data();
    const size_t length = strnlen_s(title_ptr, header_offsets::title.length);
    return std::string(title_ptr, length);
}

const byte* cartridge::logo() const {
    return _rom.data() + header_offsets::logo.start;
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

byte cartridge::calculate_header_checksum() const {
    byte checksum = 0;

    for (size_t i = header_offsets::title.start; i < header_offsets::mask_rom_version.start; ++i) {
        checksum -= _rom[i] - 1;
    }

    return checksum;
}

bool cartridge::validate_header_checksum() const {
    return (calculate_header_checksum() == header_checksum());
}

word cartridge::calculate_global_checksum() const {
    word checksum = 0;

    size_t i;

    for (i = 0; i < header_offsets::global_checksum.start; ++i) {
        checksum += _rom[i];
    }

    for (i += header_offsets::global_checksum.length; i<_rom.size(); ++i) {
        checksum += _rom[i];
    }

    return checksum;
}

bool cartridge::validate_global_checksum() const {
    return calculate_global_checksum() == global_checksum();
}

std::unique_ptr<rom_map> cartridge::create_rom_map() const {
    switch (_rom[header_offsets::cartridge_type.start]) {
    case (byte)cartridge_type::rom_only:
        return std::make_unique<rom_only_map>(*this);
    default:
        throw std::exception("Unsupported cartridge type");
    }
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

