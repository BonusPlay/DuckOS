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

/* inline bool operator==(const memory::PhysicalAddress& lhs, const memory::PhysicalAddress& rhs)
 * {
 *     return lhs.addr == rhs.addr;
 * } */

memory::PhysicalAddress operator "" _p (unsigned long long addr)
{
    return memory::PhysicalAddress{addr};
}
