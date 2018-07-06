#pragma once
#include <gamekid/utils/types.h>

namespace gamekid::memory {
    class page {
    public:
        virtual byte load(byte offset) = 0;
        virtual void store(byte offset, byte value) = 0;
        virtual ~page() = default;
    };
}
