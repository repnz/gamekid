#pragma once
#include <map>
#include <GameKid/cpu_types.h>

enum class joypad_button 
{
    a,
    b,
    select,
    start,
    right,
    left,
    up,
    down
};

class joypad 
{
private:
    byte * _p1;
    std::map<joypad_button, bool> _status;
    void set_byte_value(joypad_button b1, joypad_button b2, joypad_button b3, joypad_button b4);
public:
    explicit joypad(byte* p1_reg);
    void update(byte value);
    bool get_status(joypad_button button);
    void set_status(joypad_button button, bool status);
    

};