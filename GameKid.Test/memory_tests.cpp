#include "pch.h"
#include <GameKid/memory/memory.h>
#include <GameKid/memory/memory_map.h>


TEST(MEMORY, ECHO_INTERNAL_MEMO)
{
    memory m({});
    
    word offset = 0;
    const word size = memory_map::internal_ram_8kb_echo - memory_map::internal_ram_8kb;
    
    while (offset < size)
    {
        const word a_address = memory_map::internal_ram_8kb + offset;
        const word b_address = memory_map::internal_ram_8kb_echo + offset;

        m.store_byte(a_address, 100);
        ASSERT_EQ(100, m.load_byte(b_address));

        m.store_byte(b_address, 200);
        ASSERT_EQ(200, m.load_byte(a_address));

        ++offset;
    }
}