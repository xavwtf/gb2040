#pragma once

#include <cstdint>

namespace GB2040::Platform {
    class ROMSource;
    class RAMSource;
}

namespace GB2040::Core
{

using GB2040::Platform::ROMSource;
using GB2040::Platform::RAMSource;

enum class CartType : uint8_t {
    ROM_ONLY = 0x00,
    MBC1 = 0x01,
    MBC1_RAM = 0x02,
    MBC1_RAM_BATTERY = 0x03,
    MBC2 = 0x05,
    MBC2_BATTERY = 0x06,
    MBC3_TIMER_BATTERY = 0x0F,
    MBC3_TIMER_RAM_BATTERY = 0x10,
    MBC3 = 0x11,
    MBC3_RAM = 0x12,
    MBC3_RAM_BATTERY = 0x13,
    MBC5 = 0x19,
    MBC5_RAM = 0x1A,
    MBC5_RAM_BATTERY = 0x1B,
    MBC5_RUMBLE = 0x1C,
    MBC5_RUMBLE_RAM = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY = 0x1E

    // most others are largely irrelevant
};

class Console;
class CartridgeHeader;

class IMBC { // abstract
public:
    virtual uint8_t read8(uint16_t) = 0;
    virtual uint16_t read16(uint16_t addr) {
        return read8(addr) | (read8(addr + 1) << 8);
    }

    virtual void write8(uint16_t, uint8_t) = 0;
    virtual void write16(uint16_t addr, uint8_t val) {
        write8(addr, val & 0xFF);
        write8(addr + 1, val >> 8);
    };

    virtual void save(void) {  };
};

class MBC1 : public IMBC {
public:
    MBC1(Console& console, uint8_t* romData, CartType cartType);

    uint8_t read8(uint16_t) override;

    void write8(uint16_t, uint8_t) override;
};

class MBC2 : public IMBC {
public:
    MBC2(Console& console, uint8_t* romData, CartType cartType);

    uint8_t read8(uint16_t) override;

    void write8(uint16_t, uint8_t) override;
};

class MBC3 : public IMBC {
public:
    MBC3(Console& console, ROMSource* romSource, CartridgeHeader header);

    uint8_t read8(uint16_t) override;
    void write8(uint16_t, uint8_t) override;

    void save(void);
private:
    Console& console;
    ROMSource* romSource;
    RAMSource* ramSource;

    uint8_t romBank = 1;
    uint8_t ramBank = 0;
    bool ramEnabled = false;
    bool rtcSelected = false;
    uint8_t rtcReg = 0;
};

class MBC5 : public IMBC {
public:
    MBC5(Console& console, uint8_t* romData, CartType cartType);

    uint8_t read8(uint16_t) override;

    void write8(uint16_t, uint8_t) override;
};

class NoMBC : public IMBC {
public:
    NoMBC(Console& console, ROMSource* romSource, CartridgeHeader header);

    uint8_t read8(uint16_t) override;

    void write8(uint16_t, uint8_t) override;

private:
    Console& console;
    ROMSource* romSource;
    uint8_t ram[8192];

    bool hasRam;
};
    
} // namespace GB2040::Core
