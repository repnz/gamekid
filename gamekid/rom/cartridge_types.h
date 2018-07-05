#pragma once

namespace gamekid::rom {
    enum class cartrage_types {
        /// Rom Only
        /// 32kb rom only at memory 0x0000-0x7FFF
        rom_only = 0,

        /// Memory Bank Controller 1
        ///
        /// 0x0000-0x3FFF - Rom Bank 00 - First 16kb of rom - ReadOnly
        ///
        /// 0x4000-0x7FFF - Rom Bank 01-7F
        ///     - Allows accessing 2mb 
        ///     - Banks 0x20, 0x40, 0x60 cannot be used
        ///
        /// 0xA000-0xBFFFF - Ram Bank 00-03 - If Any (Read/Write)
        ///     - Allowing to store game positions or high score tables 
        ///     - Available ram sizes are 2kb (0xA000-0xA7FFF), 8kb (0xA000-0xBFFFF), 32kb (0xA000-0xBFFF)
        ///
        /// 0x0000-0x1FFF - Ram Enable - Write Only 
        ///     - Any value with 0xA in the lower nibble enables ram, other value disables
        ///
        /// 0x2000-0x3FFF - Rom Bank Number - Write Only
        ///     - Use 5 lower bits to choose the rom bank number
        ///     - 0 to 1, 20 to 21, 40 to 41, 60 to 61
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
        mbc3_timer_battery = 0xf,
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
}

