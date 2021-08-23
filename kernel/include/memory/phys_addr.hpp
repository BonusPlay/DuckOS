#pragma once
#include <dstd/cstdint.hpp>

namespace memory
{

struct PhysicalAddress
{
    void* addr;

    // note: some voodoo black magic forbits this from being constexpr
    explicit PhysicalAddress(uint64_t addr_);
    explicit constexpr PhysicalAddress(uint64_t* addr_);
    explicit constexpr PhysicalAddress(void* addr_)
        : addr(addr_)
    {}

    explicit operator uint64_t() const
    {
        return reinterpret_cast<uint64_t>(addr);
    }
};

}

inline bool operator==(const memory::PhysicalAddress& lhs, const memory::PhysicalAddress& rhs)
{
    return lhs.addr == rhs.addr;
}

memory::PhysicalAddress operator "" _p (unsigned long long addr);
