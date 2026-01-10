#include "core/channels.h"

#include <cstdint>
#include <algorithm>

namespace GB2040::Core
{

void NoiseChannel::tick(void) {
    timer--;

    if (timer == 0) {
        timer = divisors[clockDiv] << clockShift;

        uint8_t feedback = (lfsr & 0x01) ^ ((lfsr >> 1) & 0x01);

        lfsr >>= 1;

        if (lfsrWidth) {
            lfsr &= ~(1 << 6);
            lfsr |= (feedback << 6);
            lfsr &= 0x7F;
        } else {
            lfsr &= ~(1 << 14);
            lfsr |= (feedback << 14);
            lfsr &= 0x7FFF;
        }
    }
}

void NoiseChannel::lenTick(void) {
    if (lengthTimer > 0 && lengthEnable) {
        lengthTimer--;
        if (lengthTimer == 0) enabled = false;
    }
}

void NoiseChannel::envTick(void) {
    envelopeTimer--;

    if (envelopeTimer == 0) {
        envelopeTimer = envPeriod ? envPeriod : 8;

        if (envelopeActive && envPeriod > 0) {
            volume = std::clamp<uint8_t>(
                volume + (envDir ? 1 : -1),
                0, 15
            );
        }

        if (volume == 0 || volume == 15) envelopeActive = false;
    }
}

uint8_t NoiseChannel::out(void) {
    if (enabled && dacEnabled && (~lfsr & 0x01)) {
        return volume;
    } else return 0;
}

uint8_t NoiseChannel::readReg(uint8_t idx) {
    switch (idx) {
        case 0x0:
            return 0xFF; // write-only
        case 0x1:
            return (envPeriod & 0x07) | ((envDir & 0x01) << 3) | ((envInitVolume & 0x0F) << 4);
        case 0x2:
            return (clockDiv & 0x07) | ((lfsrWidth & 0x01) << 3) | ((clockShift & 0x0F) << 4);
        case 0x3:
            return 0x7F | ((lengthEnable & 0x01) << 6) | 0x80;
    }

    return 0xFF;
}

void NoiseChannel::writeReg(uint8_t idx, uint8_t val) {
    switch (idx) {
        case 0x0:
            length = val & 0x3F;
            break;
        case 0x1:
            envPeriod = (val & 0x07);
            envDir = (val & 0x08) >> 3;
            envInitVolume = (val & 0xF0) >> 4;

            dacEnabled = (envInitVolume > 0) || envDir;
            break;
        case 0x2:
            clockDiv = val & 0x07;
            lfsrWidth = (val >> 3) & 0x01;
            clockShift = (val >> 4) & 0x0F;
            break;
        case 0x3:
            lengthEnable = (val >> 6) & 0x01;
            if (val & 0x80) init();
            break;
    }
}

void NoiseChannel::init(void) {
    enabled = true;
    if (!lengthTimer) lengthTimer = 63;

    timer = divisors[clockDiv] << clockShift;
    envelopeActive = (envInitVolume != 0 || envDir);
    envelopeTimer = envPeriod;
    volume = envInitVolume;

    lfsr = 0x7FFF;
}

void NoiseChannel::disable(void) {
    *this = NoiseChannel{};
}

} // namespace GB2040::Core
