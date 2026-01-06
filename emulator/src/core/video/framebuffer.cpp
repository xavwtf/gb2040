#include "core/graphics.h"
#include "core/ppu.h"

namespace GB2040::Core
{

Framebuffer::Framebuffer(unsigned int w, unsigned int h)
: w(w), h(h), fb(w * h) {
    clear();
}

void Framebuffer::clear() {
    Colour white = 0xFF;

    std::fill(fb.begin(), fb.end(), white);
}

Colour Framebuffer::getPixel(unsigned int x, unsigned int y) {
    // get index into fb
    unsigned int idx = y * w + x;
    
    return fb[idx];
}

void Framebuffer::setPixel(unsigned int x, unsigned int y, Colour colour) {
    // get index into fb
    unsigned int idx = y * w + x;

    fb[idx] = colour;
}

void Framebuffer::getDiff(Framebuffer& other, Framebuffer& out) {
    unsigned int minW = std::min(w, other.w);
    unsigned int minH = std::min(h, other.h);

    for (int y = 0; y < minH; y++) {
        for (int x = 0; x < minW; x++) {
            if (getPixel(x, y) != other.getPixel(x, y)) {
                out.setPixel(x, y, other.getPixel(x, y));
            }
        }
    }

    // extra rows
    for (int y = minH; y < other.h; y++) {
        for (int x = 0; x < other.w; x++) {
            out.setPixel(x, y, other.getPixel(x, y));
        }
    }

    // extra columns
    for (int y = 0; y < other.h; y++) {
        for (int x = minW; x < other.w; x++) {
            out.setPixel(x, y, other.getPixel(x, y));
        }
    }
}

unsigned int Framebuffer::getWidth(void) {
    return w;
}

unsigned int Framebuffer::getHeight(void) {
    return h;
}

} // namespace GB2040::Core