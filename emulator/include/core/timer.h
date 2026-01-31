#pragma once

#include <cstdint>
#include <cstddef>

namespace GB2040::Core
{

class Console; // forward declaration

class Timer {
public:
    Timer(Console&);

    uint8_t tima = 0;

    uint8_t tac = 0;
    uint8_t tma = 0;

    void incTimers(size_t);
    void resetSysCounter(void);
    uint8_t getDiv(void);
private:
    Console& console;

    uint16_t sysCounter = 0;
    uint16_t timaCounter = 0;

    bool timaOverflow = false;
};

} // namespace GB2040::Core
