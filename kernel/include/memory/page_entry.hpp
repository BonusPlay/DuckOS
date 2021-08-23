#pragma once
#include <dstd/cstdint.hpp>
#include "memory/phys_addr.hpp"

namespace memory
{

struct PageEntry
{
    bool preset : 1;
    bool read_write : 1;
    bool user_supervisor : 1;
    bool page_level_writethrough : 1;
    bool page_level_cache_disable : 1;
    bool accessed : 1;
    bool dirty : 1;
    bool some_magic : 2;
    uint8_t unused_1 : 3;
    uint64_t addr : 40;
    uint16_t unused_2 : 11;
    bool no_execute : 1;

    PhysicalAddress get_addr() const;
    void set_addr(PhysicalAddress val);
}__attribute__((packed));

static_assert(sizeof(PageEntry) == 8);

}
