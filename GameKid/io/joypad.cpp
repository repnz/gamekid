#include "joypad.h"
#include <GameKid/utils/bits.h>

/*
This is the matrix layout for the joypad byte
    
        P14         P15

P10     Right       A

P11     Left        B

P12     Up          Select

P13     Down        Start
*/

namespace joypad_bits 
{
    const byte P10 = 0;
    const byte P11 = 1;
    const byte P12 = 2;
    const byte P13 = 3;
    const byte P14 = 4;
    const byte P15 = 5;
}

void joypad::set_byte_value(joypad_button b1, joypad_button b2, joypad_button b3, joypad_button b4)
{
    *_p1 = bits::set_bit(*_p1, joypad_bits::P10, _status[b1]);
    *_p1 = bits::set_bit(*_p1, joypad_bits::P11, _status[b2]);
    *_p1 = bits::set_bit(*_p1, joypad_bits::P12, _status[b3]);
    *_p1 = bits::set_bit(*_p1, joypad_bits::P13, _status[b4]);
}

joypad::joypad(byte * p1_reg)
{
}

void joypad::update(byte value)
{
    if (bits::check_bit(value, joypad_bits::P14)) 
    {
        set_byte_value(
            joypad_button::right,
            joypad_button::left,
            joypad_button::up,
            joypad_button::down
        );
    }
    else 
    {
        set_byte_value(
            joypad_button::a,
            joypad_button::b,
            joypad_button::select,
            joypad_button::start
        );
    }
}

bool joypad::get_status(joypad_button button)
{
    return _status[button];
}

void joypad::set_status(joypad_button button, bool status)
{
    _status[button] = status;
}
