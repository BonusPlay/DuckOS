#pragma once
#include "acpi/rsdt.hpp"

// Multiple APIC Description Table
// https://wiki.osdev.org/MADT
namespace acpi
{

struct MADTable : ACPISDT
{
    uint32_t lapic_addr;
    uint32_t flags;
};

void test_madt(memory::VirtualAddress<MADTable> madt);

}
