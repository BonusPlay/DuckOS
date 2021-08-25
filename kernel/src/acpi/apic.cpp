#include "acpi/apic.hpp"
#include "io.hpp"

#include "utility.hpp"
#include "serial.hpp"
#include "memory/paging.hpp"
#include "memory/phys_addr.hpp"

namespace acpi
{

void disable_pic()
{
    const constexpr uint16_t PORT_SLAVE_PIC_DATA = 0x21;
    const constexpr uint16_t PORT_MASTER_PIC_DATA = 0xA1;

    // disable 8259 PIC
    out(PORT_MASTER_PIC_DATA, 0xFF);
    out(PORT_SLAVE_PIC_DATA, 0xFF);
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

void init()
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

}
