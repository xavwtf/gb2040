#pragma once

#include <cstdint>
#include <string>
#include <chrono>

#include "core/graphics.h"

namespace GB2040::Core { class Console; }

namespace GB2040::Platform
{

class ROMSource {
public:
    virtual ~ROMSource(void);

    virtual void read8(uint32_t, uint8_t*, size_t) = 0;
    virtual size_t size(void) = 0;
};

class RAMSource : public ROMSource {
public:
    virtual void write8(uint32_t, uint8_t*, size_t) = 0;
};

class Platform {
public:
    virtual ~Platform(void);

    virtual void init(int, char**) = 0;
    virtual void run(void) = 0;
    virtual void deinit(void) = 0;
    virtual void wait(uint64_t) = 0;
    virtual uint64_t getClock(void) = 0;
    virtual bool doEvents(GB2040::Core::Console&) = 0;
    virtual void draw(GB2040::Core::Framebuffer&) = 0;
    virtual void playAudio(int16_t*, size_t) = 0;
    virtual ROMSource* selectROM(void) = 0;
    virtual RAMSource* getSave(size_t) = 0;
    virtual void saveData(RAMSource*, void*, size_t) = 0;
};
    
Platform* createPlatform(void); // platform-specific factory

} // namespace GB2040::Platform