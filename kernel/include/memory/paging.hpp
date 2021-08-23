#pragma once
#include "memory/pml2t.hpp"
#include "memory/virt_addr.hpp"

namespace memory
{

void init();

VirtualAddress map_4kb(const PhysicalAddress& phys_addr);

/* PhysicalAddress virt_to_phys(const VirtualAddress& virt_addr);
 * VirtualAddress phys_to_virt(const PhysicalAddress& phys_addr); */

}
