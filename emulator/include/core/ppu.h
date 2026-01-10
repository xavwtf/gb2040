#pragma once

#include "core/graphics.h"
#include "core/mmu.h"

#include <cstdint>

#define VRAM_SIZE      8192

#define OAM_SIZE       160

#define GB_WIDTH       160
#define GB_HEIGHT      144

namespace GB2040::Core
{

enum class PPUMode : uint8_t { HBLANK, VBLANK, OAM_SCAN, PIXEL_TRANSFER };
enum class PPULayer : uint8_t { BACKGROUND, WINDOW };

class Console;

struct Sprite {
    uint8_t y;
    uint8_t x;
    uint8_t tileIdx;
    uint8_t attrs;
    uint8_t oamIdx;
};
    
class PPU {
public:
    PPU(Console& console);

    void tick(size_t);
    void renderScanline(void);

    uint8_t readVram(uint16_t);
    void writeVram(uint16_t, uint8_t);

    uint8_t readCramBg(void);
    void writeCramBg(uint8_t);

    uint8_t readCramObj(void);
    void writeCramObj(uint8_t);

    uint8_t readOam(uint16_t);
    void writeOam(uint16_t, uint8_t);

    uint8_t readStat(void);
private:
    static constexpr Colour dmgLut[4] {
        0xFF,
        0x92,
        0x49,
        0x00
    };

    uint16_t getMapBase(PPULayer);

    void renderScanlineLayer(PPULayer);
    void renderScanlineObjects(void);
    void renderScanlinePixel(PPULayer, uint8_t x);
    void sortSprites(Sprite*, size_t);

    void hBlank(void);
    void vBlank(void);
    void oamScan(void);
    void pixelTransfer(void);

    void oamDma(uint8_t);

    friend MMU; // for IO ports

    Console& console;

    Framebuffer framebuffer;

    bool prevHBlank;
    bool prevVBlank;
    bool prevOam;
    bool prevLyc;

    PPUMode mode;
    uint32_t modeClock;

    Sprite sprites[40];

    uint8_t bgLineIndices[GB_WIDTH];
    bool objectPixelsDrawn[GB_WIDTH];

    uint8_t lcdc;
    uint8_t stat;

    uint8_t ly;
    uint8_t lyc;

    uint8_t wly;

    uint8_t scx;
    uint8_t scy;

    uint8_t wx;
    uint8_t wy;

    // GB palette registers
    uint8_t bgp;
    uint8_t obp0;
    uint8_t obp1;

    uint8_t vram[VRAM_SIZE];
    uint8_t oam[OAM_SIZE];
};

} // namespace GB2040::Core