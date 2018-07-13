#pragma once
#include "lcd.h"
#include "gamekid/memory/cell.h"

namespace gamekid::io {
    class lcd;

    class lcd_control_cell : public memory::cell {
    private:
        lcd& _lcd;
    public:
        explicit lcd_control_cell(lcd& lcd);
        void store(byte value) override;
    };
}
