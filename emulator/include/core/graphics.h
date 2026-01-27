#pragma once

#include <cstdint>
#include <vector>

namespace GB2040::Core
{

typedef uint16_t Colour;

class Framebuffer {
public:
    Framebuffer(unsigned int, unsigned int);

    void clear(void);

    void setPixel(unsigned int, unsigned int, Colour);
    Colour getPixel(unsigned int, unsigned int);
    Colour* data(void);
    size_t size(void);

    unsigned int getWidth(void);
    unsigned int getHeight(void);
private:
    unsigned int w;
    unsigned int h;

    std::vector<Colour> fb;
};

} // namespace GB2040::Core
