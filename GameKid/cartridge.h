#pragma once
#include "cpu_types.h"
#include <tuple>

struct offset {
    int start;
    int end;

    offset(int start, int end) : start(start), end(end){}
};

namespace cartridge_offsets {
    const offset entry_point(0x100, 0x103);
    const offset logo(0x104, 0x133);
    const offset title(0x134, 0x143);
    const offset manuf_code(0x13f, 0x142);
    const offset cgb_flag(0x143, 0x144);
    const offset new_licensee_code(0x144, 0x145);
    const offset sdb_flag(0x146, 0x147);
    const offset cartridge_type(0x147, 0x148);
    const offset rom_size(0x148, 0x149);
    const offset ram_size(0x149, 0x14a);
    const offset dest_code(0x14a, 0x14b);
    const offset old_licensee_code(0x14b, 0x14c);
    const offset mask_rom_version(0x14c, 0x14d);
    const offset header_checksum(0x14b, 0x14c);
    const offset global_checksum(0x14e, 0x14f);
};

bool validate_checksum(byte* data);