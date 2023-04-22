#pragma once

#include "memory/phys_addr.hpp"

namespace memory::physical
{

[[nodiscard]]
PhysicalAddress alloc(uint64_t size);

void free(PhysicalAddress addr);

};
