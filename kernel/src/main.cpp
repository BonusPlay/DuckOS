#include "main.hpp"
#include "vga.hpp"
#include "serial.hpp"
#include "idt.hpp"
#include "io.hpp"
#include "cursed/apic.hpp"
#include "utility.hpp"
#include "memory/paging.hpp"

[[noreturn]]
// cppcheck-suppress unusedFunction
void kmain()
{
    if (!serial::init())
        vga::print("Failed to init serial"_s);

    vga::clear();
/*     serial::print("DuckOS starting up\n"_s);
 *
 *     vga::clear();
 *     vga::set_pos(0, 0);
 *     vga::print("Yoloooooo\n");
 *     vga::print("No witam, mam newline'y\n");
 *     vga::set_color(vga::Color::GREEN);
 *     vga::print("Nawet kolorki\n"); */

    idt::init();
    memory::init();

    /* serial::println("Hello before the interrupt"); */

    /* interrupt<0x01>(); */

    /* serial::println("Hello after the interrupt"); */

    apic::init();

    while(true)
    {};
}
