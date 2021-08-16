#include "main.hpp"
#include "vga.hpp"
#include "serial.hpp"

#define STRINGIFY(x) #x
#define test(cond) serial::print("Assertion failed: "); serial::print(__FUNCTION__); serial::print(STRINGIFY(__LINE__))

[[noreturn]]
void kmain()
{
    if (!serial::init())
        vga_print("Failed to init serial"_s);

    serial::print("DuckOS starting up\n");
    test("foo");

    while(true)
    {};
}
