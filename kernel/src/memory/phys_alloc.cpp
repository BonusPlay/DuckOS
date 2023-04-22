#include "memory/phys_alloc.hpp"

namespace memory::physical
{

// base address chosen by fair dice roll
const auto base = 0x10000000_p;
auto top = base;

[[nodiscard]]
PhysicalAddress alloc(uint64_t size)
{
    auto ret = top;
    top = top + (size & (~0xFFF));
    return ret;
}

void free(PhysicalAddress addr)
{
    // TODO: implement actual physical pages allocator
    (void) addr;
}

};
