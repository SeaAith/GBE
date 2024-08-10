#ifndef FLAGS_H
#define FLAGS_H

#include <iostream>
#include <cstdint>

const uint8_t ZERO_FLAG_BYTE_POSITION = 7;
const uint8_t SUBTRACT_FLAG_BYTE_POSITION = 6;
const uint8_t HALF_CARRY_FLAG_BYTE_POSITION = 5;
const uint8_t CARRY_FLAG_BYTE_POSITION = 4;

class FlagsRegister {
private:
public:
    bool zero, subtract, half_carry, carry;
    FlagsRegister();
    FlagsRegister(uint8_t byte);
    ~FlagsRegister();
    static FlagsRegister from_uint8(uint8_t byte);
    uint8_t to_uint8() const;

};

#endif