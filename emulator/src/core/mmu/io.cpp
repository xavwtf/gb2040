#include "core/mmu.h"
#include "core/console.h"

#include <cstdint>

namespace GB2040::Core
{

uint8_t MMU::readIo(uint16_t port) {
    switch (port) {
        case 0x00:
            return console.getInputRegister();
        case 0x01:
        case 0x02:
            // TODO: serial
            return 0xFF;
        case 0x04:
            return console.timer.getDiv();
        case 0x05:
            return console.timer.tima;
        case 0x06:
            return console.timer.tma;
        case 0x07:
            return console.timer.tac;
        case 0x0F:
            return console.cpu.intFlag | 0xE0;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
            // TODO: audio channel 1
            return 0x0;
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
            // TODO: audio channel 2
            return 0x0;
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
            // TODO: audio channel 3
            return 0x0;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            // TODO: audio channel 4
            return 0x0;
        case 0x24:
        case 0x25:
        case 0x26:
            // TODO: audio control
            return 0x0;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            // TODO: audio wave pattern registers
            return 0x0;
        case 0x40:
            return console.ppu.lcdc;
        case 0x41:
            return console.ppu.stat;
        case 0x42:
            return console.ppu.scy;
        case 0x43:
            return console.ppu.scx;
        case 0x44:
            return console.ppu.ly;
        case 0x45:
            return console.ppu.lyc;
        case 0x46:
            // dma start/source register is write only
            return 0xFF; // open bus
        case 0x47:
            return console.ppu.bgp;
        case 0x48:
            return console.ppu.obp0;
        case 0x49:
            return console.ppu.obp1;
        case 0x4A:
            return console.ppu.wy;
        case 0x4B:
            return console.ppu.wx;
        default:
            return 0xFF; // open bus
    }
}

void MMU::writeIo(uint16_t port, uint8_t val) {
    switch (port) {
        case 0x00:
            console.inputSelectButtons = val & 0x20;
            console.inputSelectDpad = val & 0x10;
            return;
        case 0x01:
        case 0x02:
            // TODO: serial
            return;
        case 0x04:
            console.timer.resetSysCounter();
            return;
        case 0x05:
            console.timer.tima = val;
            return;
        case 0x06:
            console.timer.tma = val;
            return;
        case 0x07:
            console.timer.tac = val;
            return;
        case 0x0F:
            console.cpu.intFlag = val & 0x1F;
            return;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
            // TODO: audio channel 1
            return;
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
            // TODO: audio channel 2
            return;
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
            // TODO: audio channel 3
            return;
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
            // TODO: audio channel 4
            return;
        case 0x24:
        case 0x25:
        case 0x26:
            // TODO: audio control
            return;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
            // TODO: audio wave pattern registers
            return;
        case 0x40:
            console.ppu.lcdc = val;
            return;
        case 0x41:
            val &= 0xF8;
            console.ppu.stat = val;
            return;
        case 0x42:
            console.ppu.scy = val;
            return;
        case 0x43:
            console.ppu.scx = val;
            return;
        case 0x44: return; // don't allow writes to LY
        case 0x45:
            console.ppu.lyc = val;
            return;
        case 0x46:
            console.ppu.oamDma(val);
            return;
        case 0x47:
            console.ppu.bgp = val;
            return;
        case 0x48:
            console.ppu.obp0 = val;
            return;
        case 0x49:
            console.ppu.obp1 = val;
            return;
        case 0x4A:
            console.ppu.wy = val;
            return;
        case 0x4B:
            console.ppu.wx = val;
            return;
        case 0x50:
            if (bootRomMapped && val != 0) {
                printf("boot ROM unmapped\n");
                bootRomMapped = false;
            }
            return;
        default:
            return; // don't write anywhere
    }
}

} // namespace GB2040::Core
