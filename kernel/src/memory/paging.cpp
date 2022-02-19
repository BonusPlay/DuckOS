#include "memory/paging.hpp"
#include "log.hpp"

extern memory::PML2Table _PML2T_TABLE_;

namespace memory
{

PML1Table init_table __attribute__((aligned(4096)));

void init()
{
    // manually map 4kb which we're going to be using to place tables at
    init_table.fill(0x300000_p);
    // this is ok because 0-2MB are identity mapped
    _PML2T_TABLE_.insert_pml1t(0x1, PhysicalAddress(&init_table));
}

// OH GOD HOW BROKEN THIS IS
// REWRITE AND PURGE IT OFF THIS PLANET
VirtualAddress<void> map_4kb(const PhysicalAddress& phys_addr)
{
    // TODO: this doesn't work
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
    // 2 page tables aren't at 2MB, one from asm, one from init_table
    // and they need to be aligned at 4k
    auto pml1t = reinterpret_cast<PML1Table*>(0x200000 + (offset - 2) * 0x1000);

    pml1t->fill(phys_addr);
    _PML2T_TABLE_.insert_pml1t(offset, 0x300000_p + (offset - 2) * 0x1000);

    log::debug(
            "Memory mapped ",
            dstd::addr_to_string(phys_addr.addr),
            "_p => ",
            dstd::to_string(0x200000 * offset, 16),
            "_v");

    return VirtualAddress(static_cast<uint64_t>(0x200000 * offset));
}

/* PhysicalAddress virt_to_phys(const VirtualAddress& virt_addr)
 * {
 * }
 *
 * VirtualAddress phys_to_virt(const PhysicalAddress& phys_addr)
 * {
 * } */

}
