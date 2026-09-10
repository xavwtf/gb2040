#include "core/timer.h"
#include "core/console.h"

namespace GB2040::Core
{

Timer::Timer(Console& console)
: console(console) {  }
    
void Timer::incTimers(size_t cycles) {
    static const uint8_t selBits[4] = { 9, 3, 5, 7 };

    uint32_t oldSys = sysCounter;
    uint32_t newSys = oldSys + (uint32_t)cycles;
    sysCounter = (uint16_t)newSys;

    if (overflowDelay > 0) {
        if ((int)cycles >= overflowDelay) {
            oldSys += (uint32_t)overflowDelay;
            cycles -= (size_t)overflowDelay;
            overflowDelay = 0;
            tima = tma;
            console.requestInterrupt(Interrupt::TIMER);
            if (cycles == 0) return;
        } else {
            overflowDelay -= (int)cycles;
            return;
        }
    }

    if (!(tac & 0x04)) return;

    uint8_t shift = selBits[tac & 0x03] + 1;

    uint32_t increments = (newSys >> shift) - (oldSys >> shift);

    while (increments--) {
        if (tima == 0xFF) {
            tima = 0x00;
            overflowDelay = 4;

            break;
        } else {
            tima++;
        }
    }
}

uint8_t Timer::getDiv(void) {
    return sysCounter >> 8;
}

void Timer::resetSysCounter(void) {
    sysCounter = 0;
}

} // namespace GB2040::Core
