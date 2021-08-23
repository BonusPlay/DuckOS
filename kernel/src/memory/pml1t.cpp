#include "memory/pml1t.hpp"

extern uint64_t _PML2T_TABLE_[0x200];

namespace memory
{

void PML1Table::fill(const PhysicalAddress& start_addr)
{
    volatile auto self_addr = (reinterpret_cast<uint64_t>(this) >> 12) << 12;
    auto& self = *reinterpret_cast<PML1Table*>(self_addr);

    for (uint64_t i = 0; i < 0x200; ++i)
    {
        auto& entry = self.entries[i];
        entry.set_addr(static_cast<PhysicalAddress>(static_cast<uint64_t>(start_addr) + 0x1000 * i));
        entry.preset = true;
        entry.read_write = true;
    }
}

PhysicalAddress PML1Table::base_phys_addr() const
{
    // clean bottom 12 bits
    const auto self_addr = (reinterpret_cast<uint64_t>(this) >> 12) << 12;
    const auto& self = *reinterpret_cast<PML1Table*>(self_addr);
    return PhysicalAddress{self.entries[0].get_addr()};
}

VirtualAddress PML1Table::base_virt_addr() const
{
    for (uint64_t i = 0; i < 0x200; ++i)
    {
        if (_PML2T_TABLE_[i] == reinterpret_cast<uint64_t>(this))
            return 0x200000_v;
    }

    // TODO: assert here
    // return nullptr
    return 0x0_v;
}

bool PML1Table::present() const
{
    return reinterpret_cast<uint64_t>(this) & 0x23;
}

}
