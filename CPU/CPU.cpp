#include "CPU.h"
#include <iostream>
#include <variant>
#include "Registers.h"

void CPU::execute(const Instruction& instruction) {
    switch (instruction.type) {
        case Instruction::Type::ADD:
            handleAdd(instruction.target);
            break;
        
        default:
            // TODO: Support more instructions
            std::cout << "Instruction not supported" << std::endl;
            break;
    }
}

void CPU::handleAdd(ArithmeticTarget target) {
    switch (target) {
        case ArithmeticTarget::A: {
            uint8_t value = registers.a;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        case ArithmeticTarget::B: {
            uint8_t value = registers.b;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        case ArithmeticTarget::C: {
            uint8_t value = registers.c;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        case ArithmeticTarget::D: {
            uint8_t value = registers.d;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        case ArithmeticTarget::E: {
            uint8_t value = registers.e;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        case ArithmeticTarget::H: {
            uint8_t value = registers.h;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        case ArithmeticTarget::L: {
            uint8_t value = registers.l;
            uint8_t new_value = add(value);
            registers.a = new_value;
            break;
        }
        default:
            // TODO: support more targets
            std::cout << "Target not supported" << std::endl;
            break;
        }
};

uint8_t CPU::add(uint8_t value) {
    uint8_t new_value;
    bool did_overflow;

    std::tie(new_value, did_overflow) = overflowingAdd(registers.a, value);

    registers.flags.zero = (new_value == 0);
    registers.flags.subtract = false;
    registers.flags.carry = did_overflow;

    registers.flags.half_carry = ((registers.a & 0xF) + (value & 0xF)) > 0xF;

    return new_value;
};

std::pair<uint8_t, bool> CPU::overflowingAdd(uint8_t a, uint8_t b) {
    uint16_t result = static_cast<uint16_t>(a) + static_cast<uint16_t>(b);

    bool overflow = result > 0xFF;
    return {static_cast<uint8_t>(result), overflow};
}