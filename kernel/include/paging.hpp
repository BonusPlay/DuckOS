#pragma once
#include <dstd/cstdint.hpp>

namespace paging
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

    uint64_t* get_addr();
    void set_addr(uint64_t* val);
}__attribute__((packed));

static_assert(sizeof(PageEntry) == 8);

struct VirtAddr
{
    uint16_t sign_extend;
    uint16_t pml4t_offset : 9;
    uint16_t pml3t_offset : 9;
    uint16_t pml2t_offset : 9;
    uint16_t pml1t_offset : 9;
    uint16_t page_offset : 12;

    static VirtAddr from_addr(uint64_t* val);
}__attribute__((packed));

static_assert(sizeof(VirtAddr) == 8);

void setup_hack();
void perform_hack();
void undo_hack();

}
