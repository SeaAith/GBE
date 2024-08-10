#ifndef REGISTERS_H
#define REGISTERS_H

#include <iostream>
#include <cstdint>
#include "FlagsRegister.h"

class Registers {
    private:
    public:
        FlagsRegister flags;
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t f;
        uint8_t h;
        uint8_t l;

        Registers();
        ~Registers();

        uint16_t get_bc();
        void set_bc(uint16_t value);
        
        uint16_t get_af();
        void set_af(uint16_t value);

        uint16_t get_de();
        void set_de(uint16_t value);

        uint16_t get_hl();
        void set_hl(uint16_t value);
};

#endif