#pragma once

#include <cstdint>

#define WRAM_SIZE 0x2000 // $C000-$DFFF
#define HRAM_SIZE 0x7F // $FF80-$FFFE

namespace GB2040::Core
{

class Console;

class MMU {
public:
    MMU(Console&);

    uint8_t read8(uint16_t);
    uint16_t read16(uint16_t);

    void write8(uint16_t, uint8_t);
    void write16(uint16_t, uint16_t);

    uint8_t readIo(uint16_t);
    void writeIo(uint16_t, uint8_t);
private:
    Console& console;

    bool bootRomMapped = true;

    uint8_t internalWram[WRAM_SIZE];
    uint8_t hram[HRAM_SIZE];
};

} // namespace GB2040::Core