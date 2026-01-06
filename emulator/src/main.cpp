#include "platform/platform.h"
#include "core/console.h"

#include <string>

#include <fstream>
#include <vector>
#include <cstdint>

int main(int argc = 0, char** argv = nullptr) {
    // use generic factory method to get platform-specific platform manager
    GB2040::Platform::Platform* plat = GB2040::Platform::createPlatform();

    plat->init(argc, argv);
    plat->run();
}