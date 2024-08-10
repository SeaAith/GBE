#include <iostream>
#include <cstdint>
#include "FlagsRegister.h"

FlagsRegister::FlagsRegister() {
    zero = false;
    subtract = false;
    half_carry = false;
    carry = false;
}

FlagsRegister::FlagsRegister(uint8_t byte) {
    zero = ((byte >> ZERO_FLAG_BYTE_POSITION) & 0b1) != 0;
    subtract = ((byte >> SUBTRACT_FLAG_BYTE_POSITION) & 0b1) != 0;
    half_carry = ((byte >> HALF_CARRY_FLAG_BYTE_POSITION) & 0b1) != 0;
    carry = ((byte >> CARRY_FLAG_BYTE_POSITION) & 0b1) != 0;
}

FlagsRegister::~FlagsRegister() {
}

FlagsRegister FlagsRegister::from_uint8(uint8_t byte) {
    FlagsRegister flags;
    flags.zero = ((byte >> ZERO_FLAG_BYTE_POSITION) & 0b1) != 0;
    flags.subtract = ((byte >> SUBTRACT_FLAG_BYTE_POSITION) & 0b1) != 0;
    flags.half_carry = ((byte >> HALF_CARRY_FLAG_BYTE_POSITION) & 0b1) != 0;
    flags.carry = ((byte >> CARRY_FLAG_BYTE_POSITION) & 0b1) != 0;
    return flags;
}

uint8_t FlagsRegister::to_uint8() const {
    return (static_cast<uint8_t>(zero) << ZERO_FLAG_BYTE_POSITION) |
           (static_cast<uint8_t>(subtract) << SUBTRACT_FLAG_BYTE_POSITION) |
           (static_cast<uint8_t>(half_carry) << HALF_CARRY_FLAG_BYTE_POSITION) |
           (static_cast<uint8_t>(carry) << CARRY_FLAG_BYTE_POSITION);
}