#pragma once
#include <dstd/cstdint.hpp>
#include "memory/phys_addr.hpp"

namespace acpi
{

void apic_init();
void ioapic_init(memory::PhysicalAddress addr);
void apic_eoi();

}
