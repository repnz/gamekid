#pragma once
#include "page.h"

namespace gamekid::memory {
    class view_page : public page {
    private:
        const byte* _view;
    public:
        explicit view_page(const byte* view);
        byte load(byte offset) override;
        void store(byte offset, byte value) override;
    };
}
