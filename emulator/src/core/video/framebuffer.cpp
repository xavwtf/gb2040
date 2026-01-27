#include "core/graphics.h"
#include "core/ppu.h"

namespace GB2040::Core
{

Framebuffer::Framebuffer(unsigned int w, unsigned int h)
: w(w), h(h), fb(w * h) {
    clear();
}

void Framebuffer::clear() {
    Colour white = 0xFFFF;

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

Colour* Framebuffer::data(void) {
    return fb.data();
}

size_t Framebuffer::size(void) {
    return fb.size();
}

unsigned int Framebuffer::getWidth(void) {
    return w;
}

unsigned int Framebuffer::getHeight(void) {
    return h;
}

} // namespace GB2040::Core