#pragma once

#include "channels.h"
#include "audio.h"
#include "mmu.h"

#include <cstdint>
#include <cmath>

#define SAMPLE_RATE 65536
#define SAMPLE_FREQ 4194304 / SAMPLE_RATE

namespace GB2040::Core {

class Console;

class APU {
public:
    APU(Console&);

    void tick(size_t);
    void setEnabled(bool);

private:
    StereoSample mix(uint8_t, uint8_t, uint8_t, uint8_t);

    friend MMU; // IO ports

    bool enabled;

    uint8_t lVolume;
    uint8_t rVolume;

    uint8_t pan;

    Console& console;
    PulseChannel pulse1, pulse2;
    WaveChannel wave;
    NoiseChannel noise;

    uint8_t divApu;
    uint32_t divApuTimer;

    uint32_t sampleTimer;
};

} // namespace GB2040::Core