#include "memory/page_entry.hpp"

namespace memory
{

PhysicalAddress PageEntry::get_addr() const
{
    // clean bottom 12 bits
    const auto self_addr = (reinterpret_cast<uint64_t>(this) >> 12) << 12;
    const auto self = reinterpret_cast<PageEntry*>(self_addr);
    return PhysicalAddress{self->addr << 12};
}

void PageEntry::set_addr(PhysicalAddress val)
{
    // clean bottom 12 bits
    const auto self_addr = (reinterpret_cast<uint64_t>(this) >> 12) << 12;
    const auto self = reinterpret_cast<PageEntry*>(self_addr);
    self->addr = static_cast<uint64_t>(val) >> 12;
}

}
