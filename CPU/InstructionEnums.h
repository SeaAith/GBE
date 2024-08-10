#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <variant>

enum ArithmeticTarget {
  A, B, C, D, E, H, L,
};

struct Instruction {
    public:
    enum class Type {
        ADD
    } type;

    ArithmeticTarget target;

    Instruction(Type t, ArithmeticTarget tgt) : type(t), target(tgt) {}
};

#endif