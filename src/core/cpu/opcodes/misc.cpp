#include "core/cpu.h"

#include <cstdint>

namespace GB2040::Core 
{

uint8_t CPU::NOP(void) {
    // do nothing
    return 1;
}

uint8_t CPU::STOP(void) {
    // TODO
    uint8_t next = fetch8();
    stopped = true;
    return 1;
}

uint8_t CPU::DAA(void) { // convert A to a BCD
    uint8_t a = AF.hi;
    uint8_t adj = 0;
    bool carry = getFlag(CF);

    if (!getFlag(NF)) { // addition
        if (getFlag(HF) || (a & 0x0F) > 9) adj |= 0x06;
        if (carry || a > 0x99) {
            adj |= 0x60;
            carry = true;
        }

        a += adj;
    } else {
        if (getFlag(HF)) adj |= 0x06;
        if (carry) adj |= 0x60;
        a -= adj;
    }

    AF.hi = a;

    setFlag(ZF, AF.hi == 0);
    setFlag(HF, false);
    setFlag(CF, carry);

    return 1;
}

uint8_t CPU::SCF(void) {
    setFlag(NF, false);
    setFlag(HF, false);
    setFlag(CF, true);


    return 1;
}

uint8_t CPU::CPL(void) {
    AF.hi = ~AF.hi;

    setFlag(NF, true);
    setFlag(HF, true);

    return 1;
}

uint8_t CPU::CCF(void) {
    setFlag(CF, !getFlag(CF));

    setFlag(NF, false);
    setFlag(HF, false);

    return 1;
}

uint8_t CPU::HALT(void) {
    if (!ime && (intFlag & ie)) {
        haltBug = true;
    } else {
        halted = true;
    }
    
    return 1;
}

uint8_t CPU::POP_r16(RegisterPair& reg) {
    uint16_t val = pop();
    reg.set(val);

    return 3;
}

uint8_t CPU::POP_BC(void) { return POP_r16(BC); }
uint8_t CPU::POP_DE(void) { return POP_r16(DE); }
uint8_t CPU::POP_HL(void) { return POP_r16(HL); }
uint8_t CPU::POP_AF(void) { 
    uint16_t val = pop();
    val &= 0xFFF0; // mask low nibble
    AF.set(val);

    return 3;
}

uint8_t CPU::PUSH_r16(RegisterPair& reg) {
    push(reg.get());

    return 4;
}

uint8_t CPU::PUSH_BC(void) { return PUSH_r16(BC); }
uint8_t CPU::PUSH_DE(void) { return PUSH_r16(DE); }
uint8_t CPU::PUSH_HL(void) { return PUSH_r16(HL); }
uint8_t CPU::PUSH_AF(void) { return PUSH_r16(AF); }

uint8_t CPU::DI(void) {
    ime = false;

    return 1;
}

uint8_t CPU::EI(void) {
    eiPending = true;

    return 1;
}

} // namespace GB2040::Core::Opcodes