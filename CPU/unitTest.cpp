#include "Test.h"
#include "CPU.h"
#include "Registers.h"

CPU cpu;

void resetCPU() {
    cpu = CPU();
}

TEST(TestAddInstruction) {
    resetCPU();
    
    // Test ADD B
    cpu.registers.a = 0x5A;
    cpu.registers.b = 0x14;
    cpu.execute(Instruction{Instruction::Type::ADD, ArithmeticTarget::B});
    SimpleTest::assertEqual(static_cast<uint8_t>(0x6E), cpu.registers.a, "ADD B");
    SimpleTest::assertTrue(!cpu.registers.flags.zero, "ADD B - Zero flag");
    SimpleTest::assertTrue(!cpu.registers.flags.subtract, "ADD B - Subtract flag");
    SimpleTest::assertTrue(!cpu.registers.flags.carry, "ADD B - Carry flag");
    SimpleTest::assertTrue(!cpu.registers.flags.half_carry, "ADD B - Half carry flag");

    // Test ADD C with overflow
    cpu.registers.a = 0xFF;
    cpu.registers.c = 0x02;
    cpu.execute(Instruction{Instruction::Type::ADD, ArithmeticTarget::C});
    SimpleTest::assertEqual(static_cast<uint8_t>(0x01), cpu.registers.a, "ADD C with overflow");
    SimpleTest::assertTrue(!cpu.registers.flags.zero, "ADD C - Zero flag");
    SimpleTest::assertTrue(!cpu.registers.flags.subtract, "ADD C - Subtract flag");
    SimpleTest::assertTrue(cpu.registers.flags.carry, "ADD C - Carry flag");
    SimpleTest::assertTrue(cpu.registers.flags.half_carry, "ADD C - Half carry flag");

    // Test ADD D resulting in zero
    cpu.registers.a = 0x80;
    cpu.registers.d = 0x80;
    cpu.execute(Instruction{Instruction::Type::ADD, ArithmeticTarget::D});
    SimpleTest::assertEqual(static_cast<uint8_t>(0x00), cpu.registers.a, "ADD D resulting in zero");
    SimpleTest::assertTrue(cpu.registers.flags.zero, "ADD D - Zero flag");
    SimpleTest::assertTrue(!cpu.registers.flags.subtract, "ADD D - Subtract flag");
    SimpleTest::assertTrue(cpu.registers.flags.carry, "ADD D - Carry flag");
    SimpleTest::assertTrue(!cpu.registers.flags.half_carry, "ADD D - Half carry flag");
}

TEST(TestOverflowingAdd) {
    resetCPU();

    uint8_t result;
    bool overflow;

    // Test normal addition
    std::tie(result, overflow) = cpu.overflowingAdd(0x45, 0x38);
    SimpleTest::assertEqual(static_cast<uint8_t>(0x7D), result, "Overflowing add - normal addition result");
    SimpleTest::assertTrue(!overflow, "Overflowing add - normal addition overflow");

    // Test addition with overflow
    std::tie(result, overflow) = cpu.overflowingAdd(0xFF, 0x01);
    SimpleTest::assertEqual(static_cast<uint8_t>(0x00), result, "Overflowing add - overflow addition result");
    SimpleTest::assertTrue(overflow, "Overflowing add - overflow addition overflow");
}

TEST(TestRegisters) {
    resetCPU();

    // Test individual registers
    cpu.registers.a = 0xAB;
    cpu.registers.b = 0xCD;
    SimpleTest::assertEqual(static_cast<uint8_t>(0xAB), cpu.registers.a, "Register A");
    SimpleTest::assertEqual(static_cast<uint8_t>(0xCD), cpu.registers.b, "Register B");

    // Test 16-bit register pairs
    cpu.registers.set_bc(0x1234);
    SimpleTest::assertEqual(static_cast<uint16_t>(0x1234), cpu.registers.get_bc(), "Register pair BC");
    SimpleTest::assertEqual(static_cast<uint8_t>(0x12), cpu.registers.b, "Register B after set_bc");
    SimpleTest::assertEqual(static_cast<uint8_t>(0x34), cpu.registers.c, "Register C after set_bc");

    cpu.registers.set_de(0x5678);
    SimpleTest::assertEqual(static_cast<uint16_t>(0x5678), cpu.registers.get_de(), "Register pair DE");
    SimpleTest::assertEqual(static_cast<uint8_t>(0x56), cpu.registers.d, "Register D after set_de");
    SimpleTest::assertEqual(static_cast<uint8_t>(0x78), cpu.registers.e, "Register E after set_de");

    cpu.registers.set_hl(0x9ABC);
    SimpleTest::assertEqual(static_cast<uint16_t>(0x9ABC), cpu.registers.get_hl(), "Register pair HL");
    SimpleTest::assertEqual(static_cast<uint8_t>(0x9A), cpu.registers.h, "Register H after set_hl");
    SimpleTest::assertEqual(static_cast<uint8_t>(0xBC), cpu.registers.l, "Register L after set_hl");
}

int main() {
    SimpleTest::runAll();
    return 0;
}