#include "acpi/apic.hpp"
#include "io.hpp"

#include "utility.hpp"
#include "memory/manager.hpp"
#include "memory/phys_addr.hpp"
#include "log.hpp"
#include "acpi/ioapic.hpp"

namespace acpi
{

/*
 * https://ethv.net/workshops/osdev/notes/notes-3.html
 */
void disable_pic()
{
    const constexpr uint16_t PORT_SLAVE_PIC_DATA = 0x21;
    const constexpr uint16_t PORT_MASTER_PIC_DATA = 0xA1;

    // set ICW1
    io::out(PORT_SLAVE_PIC_DATA, 0x11);
    io::out(PORT_MASTER_PIC_DATA, 0x11);

    // set ICW2 (IRQ base offsets)
    io::out(PORT_SLAVE_PIC_DATA, 0xe0);
    io::out(PORT_MASTER_PIC_DATA, 0xe8);

    // set ICW3
    io::out(PORT_SLAVE_PIC_DATA, 0x4);
    io::out(PORT_MASTER_PIC_DATA, 0x2);

    // set ICW3
    io::out(PORT_SLAVE_PIC_DATA, 0x1);
    io::out(PORT_MASTER_PIC_DATA, 0x1);

    // set OCW1 (interrupt masks)
    io::out(PORT_SLAVE_PIC_DATA, 0xFF);
    io::out(PORT_MASTER_PIC_DATA, 0xFF);
}

void print_apic_info(const memory::VirtualAddress<uint32_t>& apic_virt)
{
    const auto lapic_id = apic_virt + 0x20;
    log::debug("APIC id: ", dstd::to_string(*(lapic_id.val), 16));

    const auto lapic_version = apic_virt + 0x30;
    log::debug("APIC version: ", dstd::to_string(*(lapic_version.val), 16));
}

void init_spurious_register(const memory::VirtualAddress<uint32_t>& apic_virt)
{
    auto reg_addr = apic_virt + 0xF0;
    *(reg_addr.val) = 0x1FF;
}

void apic_init()
{
    log::debug("apic::init()");

    disable_pic();

    // 0xfee00000
    auto tmp = io::rdmsr(io::MSR_IA32_APIC_BASE);
    auto apic_base = memory::PhysicalAddress((tmp >> 12) << 12);

    // TODO: map no cache
    const auto apic_virt = memory::map_4kb(apic_base).as<uint32_t>();

    print_apic_info(apic_virt);
    init_spurious_register(apic_virt);
}

constexpr auto IOAPICREDTBL(uint8_t n)
{
    return (0x10 + 2 * n);
}

void ioapic_init(memory::PhysicalAddress addr)
{
    log::debug("Setting up I/O APIC");
    const auto ioapic_virt = memory::map_4kb(addr).as<uint32_t>();
    
    auto ioapic = IoApic(ioapic_virt);

    IoApicRedEntry entry;
    entry.vector = 0x41;
    entry.delivery_mode = IoApicRedEntry::DeliveryMode::NORMAL;
    entry.destination_mode = IoApicRedEntry::DestinationMode::PHYSICAL;
    entry.pin_polarity = IoApicRedEntry::PinPolarity::ACTIVE_HIGH;
    entry.remote_irr = false;
    entry.trigger_mode = IoApicRedEntry::TriggerMode::EDGE;
    entry.masked = false;
    // HACK: hardcoded Local APIC ID
    entry.destination = 0x0;

    // keyboard
    ioapic.set(IOAPICREDTBL(1), entry);

    // enable
    auto tmp = io::rdmsr(io::MSR_IA32_APIC_BASE);
    tmp |= (1 << 11);
    io::wrmsr(io::MSR_IA32_APIC_BASE, tmp);

    // enable interrupts (just in case)
    __asm__("sti");

    log::debug("Finished I/O APIC");
}

void apic_eoi()
{
    // HACK: duplicated code
    auto tmp = io::rdmsr(io::MSR_IA32_APIC_BASE);
    auto apic_base = memory::PhysicalAddress((tmp >> 12) << 12);
    auto apic_virt = memory::map_4kb(apic_base).as<uint32_t>();
    *(apic_virt + 0xB0) = 0;
}

}
