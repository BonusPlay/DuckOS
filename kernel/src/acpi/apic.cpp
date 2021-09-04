#include "acpi/apic.hpp"
#include "io.hpp"

#include "utility.hpp"
#include "serial.hpp"
#include "memory/paging.hpp"
#include "memory/phys_addr.hpp"
#include "log.hpp"
#include "acpi/ioapic.hpp"

namespace acpi
{

void disable_pic()
{
    const constexpr uint16_t PORT_SLAVE_PIC_DATA = 0x21;
    const constexpr uint16_t PORT_MASTER_PIC_DATA = 0xA1;

    // disable 8259 PIC
    out(PORT_SLAVE_PIC_DATA, 0xFF);
    out(PORT_MASTER_PIC_DATA, 0xFF);
}

void print_apic_info(const memory::VirtualAddress<uint32_t>& apic_virt)
{
    const auto lapic_id = apic_virt + 0x20;
    serial::print("APIC id: ");
    serial::println(dstd::to_string(*(lapic_id.val), 16));

    const auto lapic_version = apic_virt + 0x30;
    serial::print("APIC version: ");
    serial::println(dstd::to_string(*(lapic_version.val), 16));
}

void init_spurious_register(const memory::VirtualAddress<uint32_t>& apic_virt)
{
    auto reg_addr = apic_virt + 0xF0;
    *(reg_addr.val) = 0xF0;
}

void apic_init()
{
    serial::println("apic::init()");

    disable_pic();

    // 0xfee00000
    auto tmp = rdmsr(MSR_IA32_APIC_BASE);
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
    
    auto ioapic = IoApic(ioapic_virt, 0x0);

    IoApicRedEntry entry;
    entry.vector = 0x20;
    entry.delivery_mode = IoApicRedEntry::DeliveryMode::NORMAL;
    entry.destination_mode = IoApicRedEntry::DestinationMode::PHYSICAL;
    entry.pin_polarity = IoApicRedEntry::PinPolarity::ACTIVE_HIGH;
    entry.remote_irr = false;
    entry.trigger_mode = IoApicRedEntry::TriggerMode::EDGE;
    entry.masked = false;
    // HACK: hardcoded Local APIC ID
    entry.destination = 0x0;

    ioapic.set(0x12, entry);

    // enable
    auto tmp = rdmsr(MSR_IA32_APIC_BASE);
    tmp |= (1 << 11);
    wrmsr(MSR_IA32_APIC_BASE, tmp);

    // enable interrupts (just in case)
    __asm__("sti");

    log::debug("Finished I/O APIC");
}

}
