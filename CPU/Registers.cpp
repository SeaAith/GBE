#include <iostream>
#include <cstdint>
#include <Registers.h>

Registers::Registers()
{
}

Registers::~Registers()
{
}

uint16_t Registers::get_bc() {
    (static_cast<uint16_t>(b) << 8) | static_cast<uint16_t>(c);
}
void Registers::set_bc(uint16_t value) {
    b = (value & 0xFF00) >> 8;
    c = value & 0xFF;
}

uint16_t Registers::get_af() {
    (static_cast<uint16_t>(a) << 8) | static_cast<uint16_t>(f);
}
void Registers::set_af(uint16_t value) {
    a = (value & 0xFF00) >> 8;
    f = value & 0xFF;
}

uint16_t Registers::get_de() {
    (static_cast<uint16_t>(d) << 8) | static_cast<uint16_t>(e);
}
void Registers::set_de(uint16_t value) {
    d = (value & 0xFF00) >> 8;
    e = value & 0xFF;
}

uint16_t Registers::get_hl() {
    (static_cast<uint16_t>(h) << 8) | static_cast<uint16_t>(l);
}
void Registers::set_hl(uint16_t value) {
    h = (value & 0xFF00) >> 8;
    l = value & 0xFF;
}


