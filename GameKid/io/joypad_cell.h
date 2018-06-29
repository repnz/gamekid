#pragma once
#include <map>
#include <GameKid/cpu_types.h>
#include <GameKid/memory/memory_cell.h>

enum class joypad_button 
{
    a, b, select, start, right, left, up, down
};

class joypad_cell : public memory_cell
{
private:
    std::map<joypad_button, bool> _status;
    void set_byte_value(joypad_button b1, joypad_button b2, joypad_button b3, joypad_button b4);
public:
    void store(byte value) override;
    bool get_status(joypad_button button);
    void set_status(joypad_button button, bool status);
};