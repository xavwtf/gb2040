# gb2040-emu

> Note: all tests in the `tests` directory are property of their respective developers. I do not claim ownership of any ROMs in `tests`.

An emulator written for my project GB2040 - an attempt to build a homemade Game Boy using an RP2040 (well.. RP2350 now but that doesn't roll off the tongue as well)

As of now it only supports DMG emulation, however later I may add GBC support.

Note: I wrote this documentation in like 5 minutes so it's not comprehensive nor is it sufficient in any way.

Note 2: The build system is super rigid and not particularly robust (I didn't really plan ahead). As such, you may have to modify your CMakeLists.txt in order to build on other systems (Linux, macOS etc). The included SDL3 library is NOT suitable for Linux or macOS development - get your own copy of SDL3's `devel` distribution at [the SDL GitHub repository](https://github.com/libsdl-org/SDL) if required.

## Building

### Desktop (Windows)

To build gb2040-emu for desktop, you'll need [CMake](https://cmake.org/), and a C/C++ compiler for your platform.

When configuring the project, make sure to set -DPICO_BUILD=OFF. I'd recommend using the Ninja generator.

### Desktop (Other)

TODO

### Pico

TODO