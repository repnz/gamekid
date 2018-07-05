#pragma once
#include "reg8.h"
#include <gamekid/utils/bits.h>

namespace gamekid::cpu::operands {
    class flags_reg8 : public reg8 {
    public:
        enum flag_bit_place {
            CARRY = 4,
            HALF_CARRY = 5,
            SUBSTRACT = 6,
            ZERO = 7
        };

        explicit flags_reg8()
            : reg8("F") {}

        bool check_bit(byte place) const {
            return gamekid::utils::bits::check_bit(_value, place);
        }

        void set_bit_on(byte place) {
            _value = gamekid::utils::bits::set_bit_on(_value, place);
        }

        void set_bit_off(byte place) {
            _value = gamekid::utils::bits::set_bit_off(_value, place);
        }

        void set_bit(byte place, bool is_on) {
            _value = gamekid::utils::bits::set_bit(_value, place, is_on);
        }

        bool zero() const { return check_bit(ZERO); }
        bool substract() const { return check_bit(SUBSTRACT); }
        bool half_carry() const { return check_bit(HALF_CARRY); }
        bool carry() const { return check_bit(CARRY); }

        byte zero_bit() const { return zero() ? 1 : 0; }
        byte substract_bit() const { return substract() ? 1 : 0; }
        byte half_carry_bit() const { return half_carry() ? 1 : 0; }
        byte carry_bit() const { return carry() ? 1 : 0; }

        void zero(bool value) { set_bit(ZERO, value); }
        void substract(bool value) { set_bit(SUBSTRACT, value); }
        void half_carry(bool value) { set_bit(HALF_CARRY, value); }
        void carry(bool value) { set_bit(CARRY, value); }
    };

}