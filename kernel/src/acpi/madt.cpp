#include "acpi/madt.hpp"
#include "acpi/madt_entries.hpp"
#include "log.hpp"

namespace acpi
{

memory::VirtualAddress<uint8_t> parse_entry(memory::VirtualAddress<uint8_t> ptr)
{
    auto type = *(ptr.val);
    log::info("Next entry:", type);

    switch(type)
    {
    case 0:
    {
        auto entry = ptr.force_as<EntryType0>();
        return ptr + sizeof(EntryType0);
    }
    case 1:
    {
        auto entry = ptr.force_as<EntryType1>();
        return ptr + sizeof(EntryType1);
    }
    case 2:
    {
        auto entry = ptr.force_as<EntryType2>();
        return ptr + sizeof(EntryType2);
    }
    case 3:
    {
        auto entry = ptr.force_as<EntryType3>();
        return ptr + sizeof(EntryType3);
    }
    case 4:
    {
        auto entry = ptr.force_as<EntryType4>();
        return ptr + sizeof(EntryType4);
    }
    case 5:
    {
        auto entry = ptr.force_as<EntryType5>();
        return ptr + sizeof(EntryType5);
    }
    case 9:
    {
        auto entry = ptr.force_as<EntryType9>();
        return ptr + sizeof(EntryType9);
    }
    default:
    {
        log::error("Unexpected MADT entry", type);
        assert(false, "Unknown entry");
    }
    };
}

void test_madt(memory::VirtualAddress<MADTable> madt)
{
    log::info("sig", madt->Signature, "len", madt->Length, "rev", madt->Revision, "checksum", madt->Checksum);
    log::info("lapic addr", madt->lapic_addr, "flags", madt->flags);

    auto start = (madt + 0x2C).force_as<uint8_t>();
    auto end = (madt + madt->Length).force_as<uint8_t>();

    for (auto entry = start; entry.val < end.val; entry = memory::VirtualAddress{*(entry.val + 4) + entry.val})
        parse_entry(entry);
}

}
