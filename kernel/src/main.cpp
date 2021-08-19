#include "main.hpp"
#include "vga.hpp"
#include "serial.hpp"
#include "idt.hpp"

[[noreturn]]
void kmain()
{
    if (!serial::init())
        vga::print("Failed to init serial"_s);

    serial::print("DuckOS starting up\n"_s);

    vga::clear();
    vga::set_pos(0, 0);
    vga::print("Yoloooooo\n");
    vga::print("No witam, mam newline'y\n");
    vga::set_color(vga::Color::GREEN);
    vga::print("Nawet kolorki\n");

/*     serial::print("UWAGA NAKURWIAM IDT\n");
 *
 *     idt::init();
 *
 *     serial::print("are we there?\n"); */

    while(true)
    {};
}
