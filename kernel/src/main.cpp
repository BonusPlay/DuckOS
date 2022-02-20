#include "main.hpp"
#include "vga.hpp"
#include "idt.hpp"
#include "io.hpp"
#include "utility.hpp"
#include "acpi/apic.hpp"
#include "acpi/rsdt.hpp"
#include "acpi/madt.hpp"
#include "memory/paging.hpp"
#include "multiboot2.hpp"
#include "log.hpp"
#include "syscalls.hpp"

// cppcheck-suppress unusedFunction
void kmain(void* mb2_struct)
{
    if (!serial::init())
        vga::print("Failed to init serial"_s);

    vga::clear();

    multiboot2::init(mb2_struct);

    log::info("DuckOS starting up");

    vga::clear();
    vga::set_pos(0, 0);
    vga::print("Yoloooooo\n");
    vga::print("No witam, mam newline'y\n");
    vga::set_color(vga::Color::GREEN);
    vga::print("Nawet kolorki\n");
    vga::set_color(vga::Color::WHITE);

    idt::init();
    memory::init();

    log::debug("Hello before the interrupt");
    io::interrupt<0x40>();
    log::debug("Hello after the interrupt");

    acpi::apic_init();

    auto rsdt = acpi::RSDTable::get();
    auto madt = rsdt->get_table(dstd::String{"APIC", 4}).as<acpi::MADTable>();
    test_madt(madt);

    syscalls::setup();

    log::debug("YOLO CALLING SYSCALL");
    io::syscall();
    log::debug("survived?");

    log::info("Going into infinite loop...");

    while(true)
    {
        __asm__ ("nop");
    }

    log::info("Finished...");
}
