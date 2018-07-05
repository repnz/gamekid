#pragma once
#include <gamekid/utils/offset.h>

namespace gamekid::rom::header_offsets {
    const gamekid::utils::offset
        entry_point(0x100, 3),
        logo(0x104, 47),
        title(0x134, 15),
        manuf_code(0x13f, 3),
        cgb_flag(0x143, 1),
        new_licensee_code(0x144, 2),
        sdb_flag(0x146, 1),
        cartridge_type(0x147, 1),
        rom_size(0x148, 1),
        ram_size(0x149, 1),
        dest_code(0x14a, 1),
        old_licensee_code(0x14b, 1),
        mask_rom_version(0x14c, 1),
        header_checksum(0x14b, 1),
        global_checksum(0x14e, 2);
};