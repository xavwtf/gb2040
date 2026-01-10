#include "core/channels.h"

#include <cstdint>
#include <algorithm>

namespace GB2040::Core
{

void PulseChannel::tick(void) {
    timer--;

    if (timer == 0) {
        timer = getFreq();
        dutyPos = (dutyPos + 1) % 8;
    }
}

void PulseChannel::lenTick(void) {
    if (lengthTimer > 0 && lengthEnable) {
        lengthTimer--;
        if (lengthTimer == 0) {
            enabled = false;
        }
    }
}

void PulseChannel::envTick(void) {
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

void PulseChannel::sweepTick(void) {
    sweepTimer--;

    if (sweepTimer == 0) {
        sweepTimer = sweepPace ? sweepPace : 8;

        if (sweepEnabled && sweepPace > 0) {
            uint16_t next = nextSweep();
            if (next < 2048 && sweepStep > 0) {
                sweepShadow = next;
                freq = next;
                timer = getFreq();
            }
        }
    }
}

uint16_t PulseChannel::getFreq(void) {
    return (2048 - freq) * 4;
}

uint8_t PulseChannel::out(void) {
    if (!enabled || !dacEnabled) return 0;

    return (dutyPatterns[duty] & (1 << dutyPos)) ? volume : 0;
}

void PulseChannel::init(void) {
    enabled = true;

    if (!lengthTimer) lengthTimer = 64;
    timer = getFreq();
    envelopeActive = (envInitVolume != 0 || envDir);
    envelopeTimer = envPeriod ? envPeriod : 8;
    volume = envInitVolume;
    sweepShadow = freq;
    sweepTimer = sweepPace ? sweepPace : 8;
    sweepEnabled = sweepPace > 0 || sweepStep > 0;

    if (sweepStep > 0) nextSweep(); // check for overflow
}

uint16_t PulseChannel::nextSweep(void) {
    uint16_t next = 0;
    if (sweepDir) next = sweepShadow - (sweepShadow >> sweepStep);
    else next = sweepShadow + (sweepShadow >> sweepStep);

    if (next >= 2048) enabled = false; // check overflow
    return next;
}

uint8_t PulseChannel::readReg(uint8_t idx) {
    switch (idx) {
        case 0x0:
            return (sweepStep & 0x07) | ((sweepDir & 0x01) << 3) | ((sweepPace & 0x07) << 4) | 0x80;
        case 0x1:
            return 0x3F | ((duty & 0x03) << 6);
        case 0x2:
            return (envPeriod & 0x07) | ((envDir & 0x01) << 3) | ((envInitVolume & 0x0F) << 4);
        case 0x3:
            return 0xFF; // write-only
        case 0x4:
            return ((freq >> 8) & 0x07) | ((lengthEnable & 0x01) << 6) | 0x80;
    }

    return 0xFF;
}

void PulseChannel::writeReg(uint8_t idx, uint8_t val) {
    switch (idx) {
        case 0x0:
            sweepStep = (val & 0x07);
            sweepDir = (val & 0x08) >> 3;
            sweepPace = (val & 0x70) >> 4;
            break;
        case 0x1:
            length = (val & 0x3F);
            duty = (val & 0xC0) >> 6;
            break;
        case 0x2:
            envPeriod = (val & 0x07);
            envDir = (val & 0x08) >> 3;
            envInitVolume = (val & 0xF0) >> 4;

            dacEnabled = (envInitVolume > 0) || envDir;
            break;
        case 0x3:
            freq = (freq & 0x0700) | val & 0xFF;
            timer = getFreq();
            break;
        case 0x4:
            freq = (freq & 0x00FF) | ((val & 0x07) << 8);
            timer = getFreq();
            lengthEnable = (val >> 6) & 0x01;
            if (val & 0x80) init();
            break;
    }
}

void PulseChannel::disable(void) {
    *this = PulseChannel{};
}

} // namespace GB2040::Core
