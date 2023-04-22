#include "memory/manager.hpp"
#include "memory/helpers.hpp"
#include "memory/phys_alloc.hpp"
#include "io.hpp"
#include "log.hpp"

namespace memory
{

[[nodiscard]]
VirtualAddress<void> map_4kb()
{
    const auto phys = physical::alloc(4096);
    return map_4kb(phys);
}

// base address chosen by fair dice roll
const auto base = 0x20000000_v;
auto top = base;

[[nodiscard]]
VirtualAddress<void> map_4kb(const PhysicalAddress& phys)
{
    const auto virt = top;
    top = top + 0x1000;
    map_4kb(phys, virt, 0);
    return virt;
}

void map_4kb(const PhysicalAddress& phys, const VirtualAddress<void>& virt, uint8_t flags)
{
    log::info("[memory]", "mapping", phys, "=>", virt, "(", flags, ")");

    const auto addr = uintptr_t(virt);
    const auto pml4t = io::get_cr3();
    const auto pml3t = get_pml_entry(pml4t, get_pml4t_index(addr));
    if (!(pml3t & 0x1))
    {
        log::info("[memory]", "allocate new pml3t, identity mapping", "(", pml3t, ")");
        set_pml_entry(pml4t, get_pml4t_index(addr), phys);
    }

    const auto pml2t = get_pml_entry(pml3t, get_pml3t_index(addr));
    if (!(pml2t & 0x1))
    {
        log::info("[memory]", "allocate new pml2t", "(", pml2t, ")");
        set_pml_entry(pml3t, get_pml3t_index(addr), phys);
    }

    const auto pml1t = get_pml_entry(pml2t, get_pml2t_index(addr));
    if (!(pml1t & 0x1))
    {
        log::info("[memory]", "allocate new pml1t", "(", pml1t, ")");
        set_pml_entry(pml2t, get_pml2t_index(addr), phys);
    }

    set_pml_entry(pml1t, get_pml1t_index(addr), phys);
}

}
