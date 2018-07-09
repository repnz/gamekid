#pragma once
#include <memory>
#include <gamekid/utils/types.h>

namespace gamekid::memory {
    class memory_map;

    class memory {
    private:
        memory_map & _map;
    public:
        explicit memory(memory_map& map);
        memory(const memory&) = delete;
        memory& operator=(memory&) = delete;

        /*
        Implementation functions
        */
        void store_byte(word address, byte value);
        void store_word(word address, word value);
        byte load_byte(word address);
        word load_word(word address);

        /*
        Templated Operations
        */
        template <typename T>
        T load(word address);

        template <typename T>
        void store(word address, T value);

        /*
        Template Speciailizations
        */
        template <>
        word load<word>(word address) { return load_word(address); }

        template <>
        void store<word>(word address, word value) { store_word(address, value); }

        template <>
        byte load<byte>(word address) { return load_byte(address); }

        template <>
        void store<byte>(word address, byte value) { store_byte(address, value); }


    };

}
