#include "main.hpp"
#include "vga.hpp"
#include "serial.hpp"

[[noreturn]]
void kmain()
{
    if (!serial::init())
        vga_print("Failed to init serial"_s);

    serial::print("DuckOS starting up\n");

    while(true)
    {};
}
