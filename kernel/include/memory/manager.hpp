#pragma once

#include <dstd/optional.hpp>
#include "memory/phys_addr.hpp"
#include "memory/virt_addr.hpp"

namespace memory
{

[[nodiscard]]
VirtualAddress<void> map_4kb();

[[nodiscard]]
VirtualAddress<void> map_4kb(const PhysicalAddress& phys);

void map_4kb(const PhysicalAddress& phys, const VirtualAddress<void>& virt, uint8_t flags);

};
