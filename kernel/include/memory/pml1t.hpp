#pragma once
#include "memory/page_entry.hpp"
#include "memory/phys_addr.hpp"
#include "memory/virt_addr.hpp"

namespace memory
{

struct PML1Table
{
    void fill(const PhysicalAddress& start_addr);

    bool present() const;
    PhysicalAddress base_phys_addr() const;
    VirtualAddress base_virt_addr() const;

// TODO: private
//private:
    PageEntry entries[0x200];
};

}
