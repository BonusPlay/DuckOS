#include "cursed/apic.hpp"
#include "io.hpp"

#include "utility.hpp"
#include "serial.hpp"
#include "memory/paging.hpp"
#include "memory/phys_addr.hpp"

namespace apic
{

void init()
{
    serial::println("apic::init()");

    const constexpr uint16_t PORT_SLAVE_PIC_DATA = 0x21;
    const constexpr uint16_t PORT_MASTER_PIC_DATA = 0xA1;

    // disable 8259 PIC
    out(PORT_MASTER_PIC_DATA, 0xFF);
    out(PORT_SLAVE_PIC_DATA, 0xFF);

    // 0xfee00000
    auto tmp = rdmsr(MSR_IA32_APIC_BASE);
    auto apic_base = reinterpret_cast<uint64_t>((tmp >> 12) << 12);
    const auto apic_virt = static_cast<uint64_t>(memory::map_4kb(memory::PhysicalAddress{apic_base}));
    serial::println(dstd::to_string(apic_virt, 16));

    volatile uint32_t* lapic_id = reinterpret_cast<volatile uint32_t*>(apic_virt + 0x20);
    serial::println(dstd::to_string(*lapic_id, 16));

    volatile uint32_t* lapic_version = reinterpret_cast<volatile uint32_t*>(apic_virt + 0x30);
    serial::println(dstd::to_string(*lapic_version, 16));
}

}
