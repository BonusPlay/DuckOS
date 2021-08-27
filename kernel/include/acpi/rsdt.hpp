#pragma once
#include <dstd/cstdint.hpp>
#include <dstd/string.hpp>
#include "memory/virt_addr.hpp"

// Root System Description Table
// https://wiki.osdev.org/RSDT
namespace acpi
{

struct RSDPDescriptor
{
    char Signature[8];
    uint8_t Checksum;
    char OEMID[6];
    uint8_t Revision;
    uint32_t RsdtAddress;

    static RSDPDescriptor& get();
};

struct ACPISDTHeader
{
    char Signature[4];
    uint32_t Length;
    uint8_t Revision;
    uint8_t Checksum;
    char OEMID[6];
    char OEMTableID[8];
    uint32_t OEMRevision;
    uint32_t CreatorID;
    uint32_t CreatorRevision;
};

struct RSDTable
{
    ACPISDTHeader header;
    // we cannot do it like this in C++
    /* uint32_t PointerToOtherSDT[(header.Length - sizeof(header)) / 4]; */
    uint32_t table_ptrs[0];

    static memory::VirtualAddress<RSDTable> get();
    memory::VirtualAddress<ACPISDTHeader> get_table(const dstd::String& signature);
};

void rsdt_test();

}
