#include "main.hpp"
#include "vga.hpp"
#include "serial.hpp"
#include "idt.hpp"
#include "io.hpp"
#include "utility.hpp"
#include "acpi/apic.hpp"
#include "acpi/rsdt.hpp"
#include "acpi/madt.hpp"
#include "memory/paging.hpp"
#include "multiboot2.hpp"
#include "log.hpp"

[[noreturn]]
// cppcheck-suppress unusedFunction
void kmain(void* mb2_struct)
{
    if (!serial::init())
        vga::print("Failed to init serial"_s);

    vga::clear();

    multiboot2::init(mb2_struct);

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

    acpi::apic_init();

    auto rsdt = acpi::RSDTable::get();
    auto madt = rsdt->get_table(dstd::String{"APIC", 4}).as<acpi::MADTable>();
    serial::print("madt addr: ");
    serial::println(dstd::addr_to_string(madt.val));
    log::info("sig", madt->Signature, "len", madt->Length, "rev", madt->Revision, "checksum", madt->Checksum);
    log::info("lapic addr", madt->lapic_addr, "flags", madt->flags);

    while(true)
    {};
}
