#include "lcd_control_cell.h"
#include "gamekid/utils/bits.h"

namespace gamekid::io::lcd_control_bits {
    const byte lcd_display_enable = 7;
    const byte window_tile_map_display_select = 6;
    const byte window_display_enable = 5;
    const byte bg_window_tile_data_select = 4;
    const byte bg_tile_map_display_select = 3;
    const byte sprite_size = 2;
    const byte sprite_display_enable = 1;
    const byte bg_display = 0;
}

gamekid::io::lcd_control_cell::lcd_control_cell(lcd & lcd) : _lcd(lcd){
}

void gamekid::io::lcd_control_cell::store(byte value) {
    const bool lcd_enabled = utils::bits::check_bit(value, lcd_control_bits::lcd_display_enable);
    _lcd.enabled(lcd_enabled);
    

    const bool window_enabled = utils::bits::check_bit(value, lcd_control_bits::window_display_enable);
    _lcd.window_enabled(window_enabled);
    
}
