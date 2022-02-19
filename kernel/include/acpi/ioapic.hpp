#pragma once
#include "memory/virt_addr.hpp"

namespace acpi
{

struct IoApicRedEntry
{
    enum class DeliveryMode
    {
        NORMAL = 0b000,
        LOW_PRIO = 0b001,
        SMI = 0b010,
        NMI = 0b100,
        INIT = 0b101,
        EXTINT = 0b111,
    };

    enum class DestinationMode
    {
        PHYSICAL = 0,
        LOGICAL = 1,
    };

    enum class PinPolarity
    {
        ACTIVE_HIGH = 0,
        ACTIVE_LOW = 1,
    };

    enum class TriggerMode
    {
        EDGE = 0,
        LEVEL = 1,
    };

    uint8_t vector;
    DeliveryMode delivery_mode : 3;
    DestinationMode destination_mode : 1;
    // false => IRQ no event or processing
    // true => sent and waiting to be processed
    bool delivery_status : 1;
    PinPolarity pin_polarity : 1;    
    bool remote_irr : 1;
    TriggerMode trigger_mode : 1;
    bool masked : 1;
    uint64_t unused : 39;
    uint8_t destination;

    uint32_t lower_bits()
    {
        return reinterpret_cast<uint32_t>(*reinterpret_cast<uint32_t*>(this));
    }

    uint32_t upper_bits()
    {
        return reinterpret_cast<uint32_t>(*(reinterpret_cast<uint32_t*>(this) + 1));
    }
} __attribute__((packed));

static_assert(sizeof(IoApicRedEntry) == 8);

class IoApic
{
public:
    IoApic(memory::VirtualAddress<uint32_t> addr)
        : addr_(addr)
    {}

    void set(uint8_t lower_reg, IoApicRedEntry entry)
    {
        write_reg(lower_reg, entry.lower_bits());
        write_reg(lower_reg + 1, entry.upper_bits());
    }

    void write_reg(uint8_t num, uint32_t val)
    {
        *(static_cast<volatile uint32_t*>(addr_.val)) = num;
        *(static_cast<volatile uint32_t*>((addr_ + 0x10).val)) = val;
    }

private:
    memory::VirtualAddress<uint32_t> addr_;
};

}
