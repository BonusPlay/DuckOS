#include "acpi/madt.hpp"
#include "log.hpp"

namespace acpi
{

void test_madt(memory::VirtualAddress<MADTable> madt)
{
    log::info("sig", madt->Signature, "len", madt->Length, "rev", madt->Revision, "checksum", madt->Checksum);
    log::info("lapic addr", madt->lapic_addr, "flags", madt->flags);

    auto start = (madt + 0x2C).force_as<uint8_t>();
    auto end = (madt + madt->Length).force_as<uint8_t>();

    for (auto entry_addr = start; entry_addr.val < end.val;)
    {
        auto entry = entry_addr.force_as<MADEntry>();
        log::info("Entry type", entry->type);

        entry_addr = entry_addr + entry->record_len;
    }
}

}
