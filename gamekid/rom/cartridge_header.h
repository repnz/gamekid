#pragma once
#include <vector>
#include <array>
#include <gamekid/utils/types.h>

namespace gamekid::rom {
    enum class cartridge_type {
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

    const size_t size_of_nintendo_logo = 6 * 8;
    
    const std::array<byte, size_of_nintendo_logo> nintendo_logo = 
    {
        0xCE, 0xED, 0x66, 0x66, 0xCC, 0x0D, 0x00, 0x0B, 
        0x03, 0x73, 0x00, 0x83, 0x00, 0x0C, 0x00, 0x0D,
        0x00, 0x08, 0x11, 0x1F, 0x88, 0x89, 0x00, 0x0E,
        0xDC, 0xCC, 0x6E, 0xE6, 0xDD, 0xDD, 0xD9, 0x99,
        0xBB, 0xBB, 0x67, 0x63, 0x6E, 0x0E, 0xEC, 0xCC,
        0xDD, 0xDC, 0x99, 0x9F, 0xBB, 0xB9, 0x33, 0x3E
    };

    namespace cgb_flags {
        enum {
            no_support = 0x00,
            support_cbg = 0x80,
            only_cgb = 0xC0
        };
    }

    namespace sgb_flags {
        enum {
            no_sgb = 0x00,
            support_sgb = 0x03
        };
    }

    enum class rom_size {
        kb_32 = 0x00,
        kb_64 = 0x01,
        kb_128 = 0x02,
        kb_256 = 0x03,
        kb_512 = 0x04,
        mb_1 = 0x05,
        mb_2 = 0x06,
        mb_4 = 0x07,
        mb_1_1 = 0x52,
        mb_1_2 = 0x53,
        mb_1_5 = 0x54
    };
    
    inline bool is_rom_size_valid(const byte rom_size_value) {
        if (rom_size_value >= (byte)rom_size::kb_32 &&
            rom_size_value <= (byte)rom_size::mb_4) {
            return true;
        }

        if (rom_size_value >= (byte)rom_size::mb_1_1 &&
            rom_size_value <= (byte)rom_size::mb_1_5)
            return true;

        return false;
    }

    enum class ram_size {
        none = 0x00,
        kb_2 = 0x01,
        kb_8 = 0x02,
        kb_32 = 0x03
    };
    
    inline bool is_ram_size_valid(const byte ram_size_byte) {
        return ram_size_byte >= 0 && ram_size_byte <= 3;
    }

    enum class destination_code {
        japanese = 0x00,
        non_japanese = 0x01
    };

    inline bool is_destination_code_valid(const byte destination_code_byte) {
        return destination_code_byte == 0 || destination_code_byte == 1;
    }
}

