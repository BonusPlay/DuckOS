#include "memory/paging.hpp"
#include "serial.hpp"

extern memory::PML2Table _PML2T_TABLE_;

namespace memory
{

PML1Table init_table __attribute__((aligned(4096)));

void init()
{
    // manually map 4kb which we're going to be using to place tables at
    init_table.fill(0x300000_p);
    for (auto& entry : init_table.entries)
        serial::println(dstd::to_string(static_cast<uint64_t>(entry.get_addr()), 16));
    _PML2T_TABLE_.insert_pml1t(0x1, &init_table);
}

VirtualAddress map_4kb(const PhysicalAddress& phys_addr)
{
    // check if not already mapped
    for (const auto& pml2t_entry : _PML2T_TABLE_.entries)
    {
        if (!pml2t_entry->present())
            continue;

        if (pml2t_entry->base_phys_addr() == phys_addr)
            return pml2t_entry->base_virt_addr();
    }

    // create new pml1t
    const auto offset = _PML2T_TABLE_.next_free_entry();
    // page tables at 2MB - 4MB
    auto pml1t = reinterpret_cast<PML1Table*>(0x200000 + offset * sizeof(PML1Table));
    pml1t->fill(phys_addr);
    _PML2T_TABLE_.insert_pml1t(offset, pml1t);

    return VirtualAddress(0x200000 * offset);
}

/* PhysicalAddress virt_to_phys(const VirtualAddress& virt_addr)
 * {
 * }
 *
 * VirtualAddress phys_to_virt(const PhysicalAddress& phys_addr)
 * {
 * } */

}
