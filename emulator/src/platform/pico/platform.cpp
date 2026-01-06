#include "platform/platform.h"
#include "platform/config.h"

#include <cstdint>
#include <string>
#include "pico/stdlib.h"

namespace GB2040::Platform
{

Platform::~Platform(void) = default;

class PicoPlatform : public Platform {
    void init(int argc = 0, char** argv = nullptr) override {
        // TODO: turn on LED, initialise spi, etc
        // init stdio
        stdio_init_all();

        // initialise led gpio pin
        gpio_init(PICO_DEFAULT_LED_PIN);
        gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);

        gpio_put(PICO_DEFAULT_LED_PIN, true);
    }

    void deinit(void) override {
        // TODO: turn off LED, cleanup, whatever

        gpio_put(PICO_DEFAULT_LED_PIN, false);   
    }

    void wait(uint32_t ms) override {
        sleep_ms(ms);
    }

    bool doEvents(void) override {
        // TODO: listen for power button or something
        return true
    }

    std::string selectROM(void) override {
        // TODO: file selection menu
        return "rom.gb";
    }
};

Platform* createPlatform(void) {
    return new PicoPlatform();
}

} // namespace GP2040::Platform