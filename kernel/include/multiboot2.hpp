#pragma once
#include <dstd/cstdint.hpp>
#include <dstd/assert.hpp>
#include "serial.hpp"

namespace multiboot2
{

enum class TagType : uint32_t
{
    END              = 0,
    CMDLINE          = 1,
    BOOT_LOADER_NAME = 2,
    MODULE           = 3,
    BASIC_MEMINFO    = 4,
    BOOTDEV          = 5,
    MMAP             = 6,
    VBE              = 7,
    FRAMEBUFFER      = 8,
    ELF_SECTIONS     = 9,
    APM              = 10,
    EFI32            = 11,
    EFI64            = 12,
    SMBIOS           = 13,
    ACPI_OLD         = 14,
    ACPI_NEW         = 15,
    NETWORK          = 16,
    EFI_MMAP         = 17,
    EFI_BS           = 18,
    EFI32_IH         = 19,
    EFI64_IH         = 20,
    LOAD_BASE_ADDR   = 21,
};

static_assert(sizeof(TagType) == 4);

struct Tag
{
    TagType type;
    uint32_t size;
};

struct TagAcpi
{
    uint32_t type;
    uint32_t size;
    uint8_t rsdp[0];
};

extern void* mb2_struct_ptr;

void init(void* mb2_struct_ptr_);

template<typename T>
T* get_tag(const TagType& type)
{
    for(auto* tag = reinterpret_cast<Tag*>(reinterpret_cast<uint64_t>(mb2_struct_ptr) + 8);
        tag->type != TagType::END;
        tag = reinterpret_cast<Tag*>(((uint8_t *) tag + ((tag->size + 7) & ~7))))
    {
        if (tag->type == type)
            return reinterpret_cast<T*>(tag);
    }
    return nullptr;
}

}
