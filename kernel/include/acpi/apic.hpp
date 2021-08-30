#pragma once
#include <dstd/cstdint.hpp>
#include "memory/virt_addr.hpp"

namespace acpi
{

void apic_init();
void ioapic_init(memory::VirtualAddress<void> addr);

}
