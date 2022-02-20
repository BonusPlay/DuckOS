#include "keyboard.hpp"
#include "keycodes.hpp"
#include "log.hpp"
#include "io.hpp"
#include "acpi/apic.hpp"
#include "vga.hpp"

namespace keyboard
{

uint8_t shift = false;

void handle_interrupt(interrupts::Frame* interrupt_frame)
{
    log::info("handling keyboard");

    // read keycode
    auto a = io::inb(0x60);
    log::info(a);

    // convert keycode to ascii

    // clear buf
    io::out(0x20, 0x20);

    switch (static_cast<Keycode>(a))
    {
    case Keycode::KEY_A:
        vga::print(shift ? 'A' : 'a');
        break;
    case Keycode::KEY_B:
        vga::print(shift ? 'B' : 'b');
        break;
    case Keycode::KEY_C:
        vga::print(shift ? 'C' : 'c');
        break;
    case Keycode::KEY_D:
        vga::print(shift ? 'D' : 'd');
        break;
    case Keycode::KEY_E:
        vga::print(shift ? 'E' : 'e');
        break;
    case Keycode::KEY_F:
        vga::print(shift ? 'F' : 'f');
        break;
    case Keycode::KEY_G:
        vga::print(shift ? 'G' : 'g');
        break;
    case Keycode::KEY_H:
        vga::print(shift ? 'H' : 'h');
        break;
    case Keycode::KEY_I:
        vga::print(shift ? 'I' : 'i');
        break;
    case Keycode::KEY_J:
        vga::print(shift ? 'J' : 'j');
        break;
    case Keycode::KEY_K:
        vga::print(shift ? 'K' : 'k');
        break;
    case Keycode::KEY_L:
        vga::print(shift ? 'L' : 'l');
        break;
    case Keycode::KEY_M:
        vga::print(shift ? 'M' : 'm');
        break;
    case Keycode::KEY_N:
        vga::print(shift ? 'N' : 'n');
        break;
    case Keycode::KEY_O:
        vga::print(shift ? 'O' : 'o');
        break;
    case Keycode::KEY_P:
        vga::print(shift ? 'P' : 'p');
        break;
    case Keycode::KEY_Q:
        vga::print(shift ? 'Q' : 'q');
        break;
    case Keycode::KEY_R:
        vga::print(shift ? 'R' : 'r');
        break;
    case Keycode::KEY_S:
        vga::print(shift ? 'S' : 's');
        break;
    case Keycode::KEY_T:
        vga::print(shift ? 'T' : 't');
        break;
    case Keycode::KEY_U:
        vga::print(shift ? 'U' : 'u');
        break;
    case Keycode::KEY_V:
        vga::print(shift ? 'V' : 'v');
        break;
    case Keycode::KEY_W:
        vga::print(shift ? 'W' : 'w');
        break;
    case Keycode::KEY_X:
        vga::print(shift ? 'X' : 'x');
        break;
    case Keycode::KEY_Y:
        vga::print(shift ? 'Y' : 'y');
        break;
    case Keycode::KEY_Z:
        vga::print(shift ? 'Z' : 'z');
        break;

    case Keycode::KEY_1:
        vga::print(shift ? '!' : '1');
        break;
    case Keycode::KEY_2:
        vga::print(shift ? '@' : '2');
        break;
    case Keycode::KEY_3:
        vga::print(shift ? '#' : '3');
        break;
    case Keycode::KEY_4:
        vga::print(shift ? '$' : '4');
        break;
    case Keycode::KEY_5:
        vga::print(shift ? '%' : '5');
        break;
    case Keycode::KEY_6:
        vga::print(shift ? '^' : '6');
        break;
    case Keycode::KEY_7:
        vga::print(shift ? '&' : '7');
        break;
    case Keycode::KEY_8:
        vga::print(shift ? '*' : '8');
        break;
    case Keycode::KEY_9:
        vga::print(shift ? '(' : '9');
        break;
    case Keycode::KEY_0:
        vga::print(shift  ? ')' : '0');
        break;

    case Keycode::KEY_SPACE:
        vga::print(' ');
        break;
    case Keycode::KEY_TAB:
        vga::print('\t');
        break;
    case Keycode::KEY_DASH:
        vga::print(shift ? '_' : '-');
        break;
    case Keycode::KEY_COMMA:
        vga::print(shift ? '<' : ',');
        break;
    case Keycode::KEY_PEROID:
        vga::print(shift ? '>' : '.');
        break;
    case Keycode::KEY_SEMICOLON:
        vga::print(shift ? ':' : ';');
        break;

    case Keycode::KEY_LSHIFT_ON:
        shift += 1;
        break;
    case Keycode::KEY_LSHIFT_OFF:
        shift -= 1;
        break;
    case Keycode::KEY_RSHIFT_ON:
        shift += 1;
        break;
    case Keycode::KEY_RSHIFT_OFF:
        shift -= 1;
        break;

    default:
        log::warning("not handling keycode as it's not ascii");
        break;
    }

    // send APIC
    acpi::apic_eoi();
}

}
