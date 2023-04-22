#include "acpi/rsdt.hpp"
#include <dstd/cstdint.hpp>
#include <dstd/cstring.hpp>
#include "serial.hpp"
#include "memory/phys_addr.hpp"
#include "memory/manager.hpp"
#include "multiboot2.hpp"
#include "log.hpp"

namespace acpi
{

memory::VirtualAddress<RSDTable> RSDTable::get()
{
    const auto& rsdp = RSDPDescriptor::get();

    serial::print("rsdt addr: ");
    serial::println(dstd::to_string(rsdp.RsdtAddress, 16));

    auto start_addr = (rsdp.RsdtAddress) & ~0xFFF;
    auto page_virt = memory::map_4kb(memory::PhysicalAddress{start_addr});

    // 0x1FFE18FE
    return (page_virt + (rsdp.RsdtAddress & 0xFFF)).as<RSDTable>();
}

memory::VirtualAddress<ACPISDT> RSDTable::get_table(const dstd::String& signature)
{
    assert(signature.length() == 4, "invalid signature length");
    auto table_count = (this->header.Length - sizeof(header)) / 4;
    serial::print("table count: ");
    serial::println(dstd::to_string(table_count));

    for (uint32_t i = 0; i < table_count; ++i)
    {
        const auto table_phys = memory::PhysicalAddress{this->table_ptrs[i]};
        const auto page_virt = memory::map_4kb(memory::PhysicalAddress{reinterpret_cast<uint64_t>(table_phys.addr) & static_cast<uint64_t>(~0xFFFF)});
        const auto table_virt = (page_virt + (reinterpret_cast<uint64_t>(table_phys.addr) & 0xFFFF)).as<ACPISDT>();
        log::debug("Entry in RSDT", dstd::String(table_virt->Signature, 4));
        if (dstd::memcmp(table_virt->Signature, signature.data(), 4) == 0)
            return table_virt;
    }
    return memory::VirtualAddress<ACPISDT>{nullptr};
}

RSDPDescriptor& RSDPDescriptor::get()
{
    auto* old_acpi_tag = multiboot2::get_tag<multiboot2::TagAcpi>(multiboot2::TagType::ACPI_OLD);
    assert(old_acpi_tag, "New ACPI not supported");
    return *reinterpret_cast<RSDPDescriptor*>(old_acpi_tag->rsdp);
}

void rsdt_test()
{
    auto rsdt = RSDTable::get();
    auto madt = rsdt->get_table(dstd::String{"APIC", 4});
    serial::print("madt addr: ");
    serial::println(dstd::addr_to_string(madt.val));
    return;
}

}
