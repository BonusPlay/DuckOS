#include "main.hpp"
#include "vga.hpp"
#include "serial.hpp"

[[noreturn]]
void kmain()
{
    if (!serial::init())
        vga::print("Failed to init serial"_s);

    serial::print("DuckOS starting up\n");
    serial::print("DuckOS starting up\n"_s);

    vga::clear();
    vga::set_pos(0, 0);
    vga::print("Yoloooooo");

    while(true)
    {};
}
