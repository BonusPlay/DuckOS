#include "acpi/madt.hpp"
#include "acpi/madt_entries.hpp"
#include "log.hpp"

namespace acpi
{

memory::VirtualAddress<uint8_t> parse_entry(memory::VirtualAddress<uint8_t> ptr)
{
    auto type = *(ptr.val);

    switch(type)
    {
    case 0:
    {
        auto entry = ptr.force_as<EntryType0>();
    }
    case 1:
    {
        auto entry = ptr.force_as<EntryType1>();
        break;
    }
    };
}

void test_madt(memory::VirtualAddress<MADTable> madt)
{
    log::info("sig", madt->Signature, "len", madt->Length, "rev", madt->Revision, "checksum", madt->Checksum);
    log::info("lapic addr", madt->lapic_addr, "flags", madt->flags);

    auto entry_list = (madt + 0x2C).force_as<uint8_t>();
    log::info("type", *(entry_list.val));
}

}
