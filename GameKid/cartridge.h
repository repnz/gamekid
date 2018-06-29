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

enum class cartrage_types {
    rom_only = 0,
    mbc1 = 0x01,
    mbc1_ram = 0x02,
    mbc1_ram_battery = 0x03,
    mbc2 = 0x5,
    mbc2_battery = 0x5,
    rom_ram = 0x08,
    rom_ram_battery = 0x09,
    mmm01 = 0xb,
    mmm01_ram = 0xc,
    mmm01_ram_battery = 0xd,
    mbc3_timer_ram_battery = 0xf,
    mbc3_timer_ram_battery = 0x10,
    mbc3 = 0x11,
    mbc_ram = 0x12,
    mbc3_ram_battery = 0x13,
    mbc5 = 0x19,
    mbc5_ram = 0x1a,
    mbc5_ram_battery = 0x1b,
    mbc5_rumble = 0x1c,
    mbc5_rumble_ram = 0x1d,
    mbc5_rumble_ram_battery = 0x1e,
    mbc6 = 0x20,
    mbc7_sensor_rumble_ram_battery = 0x22,
    pocket_camera = 0xfc,
    bandai_tama5 = 0xfd,
    huc3 = 0xfe,
    huc1_ram_battery = 0xff
};

namespace cartridge {
    byte calculate_header_checksum(const byte* data);
    bool validate_header_checksum(const byte* data);
}