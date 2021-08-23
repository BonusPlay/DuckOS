#include "memory/virt_addr.hpp"

namespace memory
{

VirtualAddress::VirtualAddress(uint64_t addr_)
    : addr(reinterpret_cast<void*>(addr_))
{}

constexpr VirtualAddress::VirtualAddress(uint64_t* addr_)
    : addr(static_cast<void*>(addr_))
{}

constexpr VirtualAddress::VirtualAddress(void* addr_)
    : addr(addr_)
{}

}

memory::VirtualAddress operator "" _v (unsigned long long addr)
{
    return memory::VirtualAddress{addr};
}
