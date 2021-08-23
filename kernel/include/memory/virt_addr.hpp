#pragma once
#include <dstd/cstdint.hpp>

namespace memory
{

struct VirtualAddress
{
    void* addr;

    // note: some voodoo black magic forbits this from being constexpr
    explicit VirtualAddress(uint64_t addr_);
    explicit constexpr VirtualAddress(uint64_t* addr_);
    explicit constexpr VirtualAddress(void* addr_);

    explicit operator uint64_t() const
    {
        return reinterpret_cast<uint64_t>(addr);
    }
};

}

memory::VirtualAddress operator "" _v (unsigned long long addr);
