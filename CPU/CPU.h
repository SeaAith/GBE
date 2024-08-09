#include <InstructionEnums.h>
#include <Registers.h>

class CPU {
    private:
    Registers registers;
    void handleAdd(ArithmeticTarget target);
    uint8_t add(uint8_t value);
    std::pair<uint8_t, bool> overflowingAdd(uint8_t a, uint8_t b);

    public:
    void execute(const Instruction& instruction);
};