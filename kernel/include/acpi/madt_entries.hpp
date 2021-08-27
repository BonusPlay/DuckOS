#pragma once
#include <dstd/cstdint.hpp>
#include "memory/phys_addr.hpp"

namespace acpi
{

enum class MADEntryType : uint8_t
{
    PROC_LOCAL_APIC = 0,
    IO_ACPI = 1,
    IO_APIC_INTERRUPT_SRC_OVERRIDE = 2,
    IO_APIC_NMI_SRC = 3,
    LOCAL_APIC_NMI = 4,
    LOCAL_APIC_ADDR_OVERRIDE = 5,
    PROC_LOCAL_2XAPIC = 9,
};

struct MADEntry
{
    MADEntryType type;
    uint8_t record_len;
};

// Processor Local APIC
struct EntryType0 : MADEntry
{
    uint8_t proc_id;
    uint8_t apic_id;
    uint32_t flags;
};

// I/O APIC
struct EntryType1 : MADEntry
{
    uint8_t io_apic_id;
    uint8_t reserved;
    uint32_t io_apic_addr;
    uint32_t g_system_int_base;
};

// IO/APIC Interrupt Source Override
struct EntryType2 : MADEntry
{
    uint8_t bus_src;
    uint8_t irq_src;
    uint32_t g_system_int;
    uint16_t flags;
};

// IO/APIC Non-maskable interrupt source
struct EntryType3 : MADEntry
{
    uint8_t nmi_src;
    uint8_t reserved;
    uint16_t flags;
    uint32_t g_system_int;
};

// Local APIC Non-maskable interrupts
struct EntryType4 : MADEntry
{
    uint8_t acpi_proc_id;
    uint16_t flags;
    uint8_t lint;
};

// Local APIC Address Override
struct EntryType5 : MADEntry
{
    uint16_t reserved;
    memory::PhysicalAddress apic_addr;
};

// Processor Local x2APIC
struct EntryType9 : MADEntry
{
    uint16_t reserved;
    uint32_t proc_local_2xapic_id;
    uint32_t flags;
    uint32_t acpi_id;
};

}
