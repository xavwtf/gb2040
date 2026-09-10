#pragma once

#include <cstdint>
#include <cstddef>

#define WRAM_SIZE 0x2000 // $C000-$DFFF
#define HRAM_SIZE 0x7F // $FF80-$FFFE

namespace GB2040::Core
{

class Console;

class MMU {
public:
    MMU(Console& console);

    uint8_t read8(uint16_t addr);
    uint16_t read16(uint16_t addr);

    void write8(uint16_t addr, uint8_t val);
    void write16(uint16_t addr, uint16_t val);

    uint8_t readIo(uint16_t port);
    void writeIo(uint16_t port, uint8_t val);

    void setRomCache(const uint8_t* data, size_t size) {
        romData = data;
        romSize = size;
    }
private:
    Console& console;

    bool bootRomMapped = true;

    const uint8_t* romData = nullptr;
    size_t romSize = 0;

    uint8_t internalWram[WRAM_SIZE];
    uint8_t hram[HRAM_SIZE];
};

} // namespace GB2040::Core