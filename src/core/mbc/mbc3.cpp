#include "core/mbc.h"
#include "core/console.h"
#include "platform/platform.h"

#include <cstdint>
#include <cstring>

namespace GB2040::Core
{

using GB2040::Platform::RAMSource;

MBC3::MBC3(Console& console, ROMSource* romSource, CartridgeHeader header)
: console(console), romSource(romSource) {
    ramSource = console.platform->getSave(32768);
}

uint8_t MBC3::read8(uint16_t addr) {
    if (0x0 <= addr && addr <= 0x3FFF) { // fixed ROM bank 0
        uint8_t v;
        romSource->read8(addr, &v, 1);
        return v;
    } else if (0x4000 <= addr && addr <= 0x7FFF) { // switchable ROM
        uint32_t romAddr = romBank * 0x4000 + (addr - 0x4000);
        uint8_t v;
        romSource->read8(romAddr, &v, 1);
        return v;
    } else if (0xA000 <= addr && addr <= 0xBFFF) {
        if (!ramEnabled) return 0xFF;
        if (rtcSelected) return 0x00; // stub

        uint32_t ramAddr = ramBank * 0x2000 + (addr - 0xA000);
        uint8_t v;
        ramSource->read8(ramAddr, &v, 1);
        return v;
    }

    return 0xFF;
}

void MBC3::write8(uint16_t addr, uint8_t val) {
    if (0x0 <= addr && addr <= 0x1FFF) {
        ramEnabled = ((val & 0x0F) == 0x0A);
        return;
    } else if (0x2000 <= addr && addr <= 0x3FFF) {
        romBank = val & 0x7F;
        if (romBank == 0) romBank = 1;
        return;
    } else if (0x4000 <= addr && addr <= 0x5FFF) {
        if (val <= 0x03) {
            ramBank = val;
            rtcSelected = false;
        } else if (0x08 <= val && val <= 0x0C) {
            rtcSelected = true;
            rtcReg = val;
        }

        return;
    } else if (0x6000 <= addr && addr <= 0x7FFF) {
        // TODO: RTC latch
        return;
    }

    if (0xA000 <= addr && addr <= 0xBFFF) {
        if (!ramEnabled) return;
        if (rtcSelected) {
            // TODO: handle RTC writes
            return;
        }

        uint32_t ramAddr = ramBank * 0x2000 + (addr - 0xA000);
        ramSource->write8(ramAddr, &val, 1);
    }
}

void MBC3::save(void) {
    console.platform->saveData(ramSource, nullptr, 0);
}

} // namespace GB2040::Core
