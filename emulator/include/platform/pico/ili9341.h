#pragma once

#include <cstdint>

#include "hardware/spi.h"

#include "core/graphics.h"

#define SPI_PORT spi1

namespace GB2040::Platform::ILI9341
{

enum class Command {
    NOP = 0x00,
    SWRESET = 0x01,
    SLPOUT = 0x11,
    GAMMA = 0x26,
    DISPON = 0x29,
    CASET = 0x2A,
    PASET = 0x2B,
    RAMWR = 0x2C,
    MADCTL = 0x36,
    VSCRO = 0x37,
    COLMOD = 0x3A,
    FRCTL1 = 0xB1,
    DFCTL = 0xB6,
    PWR1 = 0xC0,
    PWR2 = 0xC1,
    VCOM1 = 0xC5,
    VCOM2 = 0xC7,
    PWRCTLA = 0xCB,
    PWRCTLB = 0xCF,
    GPCTL = 0xE0,
    GNCTL = 0xE1,
    DTCTLA = 0xE8,
    DTCTLB = 0xEA,
    PWRSEQ = 0xED,
    G3EN = 0xF2,
    PUMPRC = 0xF7,
};

class ILI9341 {
public:
    ILI9341(uint sck, uint sda, uint cs, uint dc, uint rst, uint bl);

    void clear(void);
    void drawFramebuffer(GB2040::Core::Framebuffer& fb, uint xOffset, uint yOffset);

    void waitDMA(void);
private:
    void init(void);
    void sendCmd(Command command, std::initializer_list<uint8_t> params = {});
    void sendData(void* data, size_t count);
    void txBlock(uint x1, uint y1, uint x2, uint y2, void* data, size_t count);

    uint pinSck;
    uint pinSda;
    uint pinCs;
    uint pinDc;
    uint pinRst;
    uint pinBl;

    int dmaChannel;
};

} // namespace GB2040::Platform::ILI9341