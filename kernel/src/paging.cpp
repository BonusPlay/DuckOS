#include "paging.hpp"
#include "serial.hpp"
#include "io.hpp"
#include <dstd/cstring.hpp>

extern uint64_t* _PML4T_TABLE_[0x1000];
extern uint64_t* _PML3T_TABLE_[0x1000];
extern uint64_t* _PML2T_TABLE_[0x1000];

namespace paging
{
uint64_t* PageEntry::get_addr()
{
    return reinterpret_cast<uint64_t*>(this->addr << 12);
}

void PageEntry::set_addr(uint64_t* val)
{
    this->addr = reinterpret_cast<uint64_t>(val) >> 12;
}

VirtAddr VirtAddr::from_addr(uint64_t* addr)
{
    VirtAddr ret{};
    const auto val = reinterpret_cast<uint64_t>(addr);
    ret.page_offset = val & 0xFFF;
    ret.pml1t_offset = (val & (static_cast<uint64_t>(0x1FF) << 12)) >> 12;
    ret.pml2t_offset = (val & (static_cast<uint64_t>(0x1FF) << 21)) >> 21;
    ret.pml3t_offset = (val & (static_cast<uint64_t>(0x1FF) << 30)) >> 30;
    ret.pml4t_offset = (val & (static_cast<uint64_t>(0x1FF) << 39)) >> 39;
    ret.sign_extend = val >> 48;
    return ret;
}

PageEntry hack[0x1000] __attribute__((aligned(4096)));

void dump_table(uint64_t* addr_from)
{
    for(uint64_t* cur_addr = addr_from; cur_addr < addr_from + 0x200; ++cur_addr)
    {
        serial::print(dstd::addr_to_string(cur_addr));
        serial::print(" ");
        serial::println(dstd::to_string(*cur_addr, 16));
    }
}

void setup_hack()
{
    serial::print("hacked page: ");
    serial::println(dstd::addr_to_string(&hack));
    dstd::memset(static_cast<void*>(&hack), 0, sizeof(PageEntry) * 0x1000);

    for (uint64_t i = 0; i < 0x200; ++i)
    {
        auto& entry = hack[i];
        entry.set_addr(reinterpret_cast<uint64_t*>(0xffe00000 + 0x1000 * i));
        entry.preset = true;
        entry.read_write = true;
    }
    _PML2T_TABLE_[0x7f] = reinterpret_cast<uint64_t*>(&hack);

    /* dump_table(reinterpret_cast<uint64_t*>(&hack)); */
}

}
