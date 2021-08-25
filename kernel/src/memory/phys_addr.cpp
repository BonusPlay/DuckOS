#include "memory/phys_addr.hpp"

namespace memory
{

PhysicalAddress::PhysicalAddress(uint64_t addr_)
    : addr(reinterpret_cast<void*>(addr_))
{}

constexpr PhysicalAddress::PhysicalAddress(uint64_t* addr_)
    : addr(static_cast<void*>(addr_))
{}

/* constexpr PhysicalAddress::PhysicalAddress(void* addr_)
 *     : addr(addr_)
 * {} */

}
