#include "memory/page_entry.hpp"

namespace memory
{

PhysicalAddress PageEntry::get_addr() const
{
    // clean bottom 12 bits
    return PhysicalAddress{this->addr << 12};
}

void PageEntry::set_addr(PhysicalAddress val)
{
    this->addr = static_cast<uint64_t>(val) >> 12;
}

}
