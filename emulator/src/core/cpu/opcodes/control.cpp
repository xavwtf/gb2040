#include "core/cpu.h"
#include "core/console.h"

namespace GB2040::Core
{

uint8_t CPU::JR_F_s8(bool flag) {
    int8_t addr = static_cast<int8_t>(fetch8());

    if (flag) {
        PC += addr; // signed

        return 3;
    }

    return 2;
}

uint8_t CPU::JR_NZ_s8(void) { return JR_F_s8(!getFlag(ZF)); }
uint8_t CPU::JR_NC_s8(void) { return JR_F_s8(!getFlag(CF)); }
uint8_t CPU::JR_Z_s8(void) { return JR_F_s8(getFlag(ZF)); }
uint8_t CPU::JR_C_s8(void) { return JR_F_s8(getFlag(CF)); }

uint8_t CPU::JR_s8(void) { return JR_F_s8(true); }

uint8_t CPU::RET_F(bool flag) {
    if (flag) {
        PC = pop();
        return 5;
    }

    return 2;
}

uint8_t CPU::RET_NZ(void) { return RET_F(!getFlag(ZF)); }
uint8_t CPU::RET_NC(void) { return RET_F(!getFlag(CF)); }

uint8_t CPU::JP_F_a16(bool flag) {
    uint16_t addr = fetch16();

    if (flag) {
        PC = addr;

        return 4;
    }

    return 3;
}

uint8_t CPU::JP_NZ_a16(void) { return JP_F_a16(!getFlag(ZF)); }
uint8_t CPU::JP_NC_a16(void) { return JP_F_a16(!getFlag(CF)); }

uint8_t CPU::JP_a16(void) {
    uint16_t addr = fetch16();
    PC = addr;

    return 4;
}

uint8_t CPU::CALL_F_a16(bool flag) {
    uint16_t addr = fetch16();

    if (flag) {
        push(PC);
        PC = addr;

        return 6;
    }

    return 3;
}

uint8_t CPU::CALL_NZ_a16(void) { return CALL_F_a16(!getFlag(ZF)); }
uint8_t CPU::CALL_NC_a16(void) { return CALL_F_a16(!getFlag(CF)); }

uint8_t CPU::RST_n(uint8_t n) {
    uint8_t addr = n * 0x08;

    push(PC);
    PC = addr;

    return 4;
}

uint8_t CPU::RST_0(void) { return RST_n(0); }
uint8_t CPU::RST_2(void) { return RST_n(2); }
uint8_t CPU::RST_4(void) { return RST_n(4); }
uint8_t CPU::RST_6(void) { return RST_n(6); }

uint8_t CPU::RET_Z(void) { return RET_F(getFlag(ZF)); }
uint8_t CPU::RET_C(void) { return RET_F(getFlag(CF)); }

uint8_t CPU::RET(void) {
    PC = pop();
    
    return 4;
}

uint8_t CPU::RETI(void) {
    PC = pop();
    ime = true;

    return 4;
}

uint8_t CPU::RST_1(void) { return RST_n(1); }
uint8_t CPU::RST_3(void) { return RST_n(3); }
uint8_t CPU::RST_5(void) { return RST_n(5); }
uint8_t CPU::RST_7(void) { return RST_n(7); }

uint8_t CPU::JP_HL(void) {
    uint16_t addr = HL.get();
    PC = addr;

    return 1;
}

uint8_t CPU::JP_Z_a16(void) { return JP_F_a16(getFlag(ZF)); }
uint8_t CPU::JP_C_a16(void) { return JP_F_a16(getFlag(CF)); }

uint8_t CPU::CALL_Z_a16(void) { return CALL_F_a16(getFlag(ZF)); }
uint8_t CPU::CALL_C_a16(void) { return CALL_F_a16(getFlag(CF)); }

uint8_t CPU::CALL_a16(void) {
    uint16_t addr = fetch16();

    push(PC);
    PC = addr;

    return 6;
}

} // namespace GB2040::Core
