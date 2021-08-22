#include "cursed/apic.hpp"
#include "io.hpp"

#include "utility.hpp"
#include "serial.hpp"
#include "paging.hpp"

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
    
    auto cr3 = get_cr3();
    serial::println(dstd::to_string(cr3, 16));

    paging::setup_hack();

    // 0xfee00000
    /* auto apic_base = rdmsr(MSR_IA32_APIC_BASE); */
    uint64_t* apic_base = reinterpret_cast<uint64_t*>(0xfee00000);
    /* uint8_t* apic_end = reinterpret_cast<uint8_t*>(0xfee00400); */

    auto virt = paging::VirtAddr::from_addr(apic_base);
    serial::print("sign extend: ");
    serial::println(dstd::to_string(virt.sign_extend, 16));
    serial::print("pml4t offset: ");
    serial::println(dstd::to_string(virt.pml4t_offset, 16));
    serial::print("pml3t offset: ");
    serial::println(dstd::to_string(virt.pml3t_offset, 16));
    serial::print("pml2t offset: ");
    serial::println(dstd::to_string(virt.pml2t_offset, 16));
    serial::print("pml1t offset: ");
    serial::println(dstd::to_string(virt.pml1t_offset, 16));
    serial::print("page offset: ");
    serial::println(dstd::to_string(virt.page_offset, 16));

    auto* llapic_id = reinterpret_cast<uint64_t*>(0xfee00000);
    auto* lapic_id = apic_base + 0x4;
    serial::println(dstd::addr_to_string(lapic_id));
    /* serial::println(dstd::addr_to_string(llapic_id)); */
    serial::println(dstd::to_string(*lapic_id, 16));
}

}
