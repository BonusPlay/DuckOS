#include "memory/helpers.hpp"
#include "io.hpp"

namespace memory
{

[[nodiscard]]
constexpr size_t get_pml4t_index(const uintptr_t& virt)
{
    return (virt >> 39) & 0x1FF;
}

[[nodiscard]]
constexpr size_t get_pml3t_index(const uintptr_t& virt)
{
    return (virt >> 30) & 0x1FF;
}

[[nodiscard]]
constexpr size_t get_pml2t_index(const uintptr_t& virt)
{
    return (virt >> 21) & 0x1FF;
}

[[nodiscard]]
constexpr size_t get_pml1t_index(const uintptr_t& virt)
{
    return (virt >> 12) & 0x1FF;
}

[[nodiscard]]
constexpr size_t get_offset(const uintptr_t& virt)
{
    return virt & 0xFFF;
}

[[nodiscard]]
uintptr_t get_pml_entry(const uintptr_t table_, size_t index_)
{
    const auto table = reinterpret_cast<uintptr_t*>(table_ & ~0xFFF);
    return reinterpret_cast<uintptr_t>(table[index_]);
}

void set_pml_entry(const uintptr_t table_, size_t index_, uintptr_t value_)
{
    auto table = reinterpret_cast<uintptr_t*>(table_ & ~0xFFF);
    table[index_] = value_;
}

void set_pml_entry(const uintptr_t table_, size_t index_, const PhysicalAddress& value_)
{
    set_pml_entry(table_, index_, uintptr_t(value_));
}

[[nodiscard]]
VirtualAddress<void> build_virt_ptr(const size_t& pml4t_index, const size_t& pml3t_index, const size_t& pml2t_index, const size_t& pml1t_index, const uintptr_t& offset)
{
    const auto p4 = pml4t_index << 39;
    const auto p3 = pml3t_index << 30;
    const auto p2 = pml2t_index << 21;
    const auto p1 = pml1t_index << 12;
    return VirtualAddress<void>(p4 | p3 | p2 | p1 | get_offset(offset));
}

[[nodiscard]]
dstd::Optional<PhysicalAddress> virt_to_phys(const VirtualAddress<void>& virt_addr)
{
    const auto addr = uintptr_t(virt_addr);
    const auto pml4t = io::get_cr3();
    if (!(pml4t & 0x1))
        return dstd::Optional<PhysicalAddress>{};

    const auto pml3t = get_pml_entry(pml4t, get_pml4t_index(addr));
    if (!(pml3t & 0x1))
        return dstd::Optional<PhysicalAddress>{};

    const auto pml2t = get_pml_entry(pml3t, get_pml3t_index(addr));
    if (!(pml2t & 0x1))
        return dstd::Optional<PhysicalAddress>{};

    const auto pml1t = get_pml_entry(pml2t, get_pml2t_index(addr));
    if (!(pml1t & 0x1))
        return dstd::Optional<PhysicalAddress>{};

    const auto page = get_pml_entry(pml1t, get_pml1t_index(addr));
    if (!(page & 0x1))
        return dstd::Optional<PhysicalAddress>{};

    return dstd::Optional<PhysicalAddress>(PhysicalAddress(page + get_offset(addr)));
}

[[nodiscard]]
dstd::Optional<VirtualAddress<void>> phys_to_virt(const PhysicalAddress& phys_addr)
{
    const auto pml4t = uintptr_t(io::get_cr3());

    for (auto pml4t_index = 0; pml4t_index < 0x200; ++pml4t_index)
    {
        const auto pml3t = get_pml_entry(pml4t, pml4t_index);

        // skip empty entries
        if (!(pml3t & 0x1))
            continue;

        for (auto pml3t_index = 0; pml3t_index < 0x200; ++pml3t_index)
        {
            const auto pml2t = get_pml_entry(pml3t, pml3t_index);

            // skip empty entries
            if (!(pml2t & 0x1))
                continue;

            for (auto pml2t_index = 0; pml2t_index < 0x200; ++pml2t_index)
            {
                const auto pml1t = get_pml_entry(pml2t, pml2t_index);

                // skip empty entries
                if (!(pml1t & 0x1))
                    continue;

                for (auto pml1t_index = 0; pml1t_index < 0x200; ++pml1t_index)
                {
                    const auto page = get_pml_entry(pml1t, pml1t_index);

                    if ((page & ~0xFFF) == (uintptr_t(phys_addr) & ~0xFFF))
                    {
                        return dstd::Optional<VirtualAddress<void>>(build_virt_ptr(pml4t_index, pml3t_index, pml2t_index, pml1t_index, get_offset(uintptr_t(phys_addr))));
                    }

                    // noop, go to next entry
                }

                // noop, go to next entry
            }

            // noop, go to next entry
        }

        // noop, go to next entry
    }

    // not found :(
    return dstd::Optional<VirtualAddress<void>>{};
}

}
