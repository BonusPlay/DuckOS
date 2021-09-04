#include "acpi/madt.hpp"
#include "log.hpp"
#include "acpi/apic.hpp"
#include "memory/paging.hpp"

namespace acpi
{

void test_madt(memory::VirtualAddress<MADTable> madt)
{
    log::info("sig", madt->Signature, "len", madt->Length, "rev", madt->Revision, "checksum", madt->Checksum);
    log::info("lapic addr", madt->lapic_addr, "flags", madt->flags);

    auto start = (madt + 0x2C).force_as<uint8_t>();
    auto end = (madt + madt->Length).force_as<uint8_t>();

    // we increment the pointer at the end of the loop
    for (auto entry_addr = start; entry_addr.val < end.val;)
    {
        auto entry = entry_addr.force_as<MADEntry>();
        log::debug(entry_addr, entry->type, entry->record_len);

        switch (entry->type)
        {
        // Processor Local APIC
        case 0:
            log::debug("Found Processor Local APIC", "ACPI proc ID", *((entry_addr + 0x2).val), "APIC ID", *((entry_addr + 0x3).val), "Flags", *((entry_addr + 0x4).force_as<uint32_t>().val));
            break;

        // I/O APIC
        case 1:
        {
            const auto ioapic_phys = memory::PhysicalAddress{*(entry_addr + 0x4).force_as<uint32_t>().val};
            log::debug("Found I/O APIC", "I/O APIC ID", *(entry_addr.val), "I/O APIC base addr", ioapic_phys);
            ioapic_init(ioapic_phys);
            /* [> ioapic_init((entry_addr + 0x4).force_as<void>()); <] */
            break;
        }
        // IO/APIC Interrupt Source Override
        case 2:
            log::debug("Found IO/APIC Interrupt Source Override", "bus src", *((entry_addr + 0x2).val), "irq src", *((entry_addr + 0x3).val), "global system interrupt", *((entry_addr + 0x4).force_as<uint32_t>().val));
            break;

        case 4:
            log::debug("Found Local APIC Non-maskable interrupts", "ACPI Processor ID", *((entry_addr + 0x2).val), "Flags", *((entry_addr + 0x3).force_as<uint16_t>().val), "LINT#", *((entry_addr + 0x5).val));
            break;

        default:
            log::debug("Unknown MADT entry", entry->type, entry->record_len);
            // HACK: wolp, we exit early I guess
            return;
        }

        // increment pointer
        entry_addr = entry_addr + entry->record_len;
    }

    log::debug("Finished parsing MADT");
}

}
