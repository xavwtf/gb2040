#pragma once

#include <cstdint>
#include <cstddef>

namespace GB2040::Core
{

class Console; // forward declaration

class Timer {
public:
    Timer(Console&);

    uint8_t tima;

    uint8_t tac;
    uint8_t tma;

    void incTimers(size_t);
    void resetSysCounter(void);
    uint8_t getDiv(void);
private:
    Console& console;

    uint16_t sysCounter;
    uint16_t timaCounter;

    bool timaOverflow;
};

} // namespace GB2040::Core
