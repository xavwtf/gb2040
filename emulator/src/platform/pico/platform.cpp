#include "platform/platform.h"

#include "core/graphics.h"
#include "core/audio.h"
#include "core/console.h"

#include <cstdint>
#include <string>

namespace GB2040::Platform
{

ROMSource::~ROMSource(void) = default;

Platform::~Platform(void) = default;

class PicoPlatform : public Platform {
public:
    void init(int argc, char** argv) override {
        
    }

    void run(void) override {
        
    }

    void deinit(void) override {
        
    }

    void wait(uint64_t us) override {
        
    }

    bool doEvents(GB2040::Core::Console& console) override {
        
    }

    uint64_t getClock(void) {
        
    }

    void draw(GB2040::Core::Framebuffer& framebuffer) override {
        
    }

    ROMSource* selectROM(void) override {
        
    }

    RAMSource* getSave(size_t size) override {
        
    }

    void saveData(RAMSource* data) override {
        
    }

    void pushSamples(GB2040::Core::StereoSample* samples, size_t count) override {
        
    }

private:
    int argc;
    char** argv;

    std::string romPath;

    bool audioEnabled = true;
};

Platform* createPlatform(void) {
    return new PicoPlatform();
}

} // namespace GB2040::Platform
