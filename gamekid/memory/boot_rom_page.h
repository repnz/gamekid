#pragma once
#include "page.h"

namespace gamekid::memory {
    class boot_rom_page : public page {
    public:
        byte load(byte offset) override;
        void store(byte offset, byte value) override;
    };
}
