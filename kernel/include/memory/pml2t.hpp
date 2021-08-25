#pragma once
#include "memory/pml1t.hpp"

namespace memory
{

struct PML2Table
{
    void insert_pml1t(uint32_t index, PhysicalAddress addr)
    {
        const auto table_addr = (static_cast<uint64_t>(addr) | 0x23);
        entries[index] = reinterpret_cast<PML1Table*>(table_addr);
    }

    uint16_t next_free_entry() const
    {
        for (uint16_t i = 0; i < 0x200; ++i)
        {
            if (entries[i] == nullptr)
                return i;
        }

        // TODO: assert
        return 0x200;
    }

    PML1Table* entries[0x200];
};

}
