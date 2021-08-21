#include "idt.hpp"
#include <dstd/cstring.hpp>
#include "io.hpp"
#include "utility.hpp"
#include <dstd/string.hpp>
#include "serial.hpp"

// "injected" by linker
extern "C" void _int_handler();
extern uint64_t* _ISR_STUB_TABLE_[32];
extern idt::IDTEntry _IDT_TABLE_[0x100];

namespace idt
{

uint64_t* IDTEntry::get_offset() const
{
    uint64_t offset = 0;
    offset |= static_cast<uint64_t>(this->offset_1);
    offset |= static_cast<uint64_t>(this->offset_2) << 16;
    offset |= static_cast<uint64_t>(this->offset_3) << 32;
    return reinterpret_cast<uint64_t*>(offset);
}

void IDTEntry::set_offset(uint64_t* offset_)
{
    auto offset = reinterpret_cast<uint64_t>(offset_);
    this->offset_1 = offset & 0xFFFF;
    this->offset_2 = (offset & 0xFFFF0000) >> 16;
    this->offset_3 = offset >> 32;
}

void init()
{
    // zero initialize memory, so we don't have to zero initialize members of structs
    dstd::memset(&_IDT_TABLE_, 0, sizeof(IDTEntry) * 0x100);

    for (uint16_t i = 0; i < 0x100; ++i)
    {
        auto& entry = _IDT_TABLE_[i];
        entry.selector.index = 1;
        entry.type_attr.present = 0x01;
        entry.type_attr.type = GateType::INTERRUPT_GATE;
        entry.set_offset(_ISR_STUB_TABLE_[i]);
    }

    auto ptr = IDTRegister{};
    ptr.limit = sizeof(IDTEntry) * 0x100 - 1;
    ptr.base = reinterpret_cast<uint64_t>(&_IDT_TABLE_);

     __asm__ ("lidt %0" :: "m"(ptr));
}

void interrupt_handler(uint8_t interrupt_num, uint64_t error_code, void* interrupt_frame)
{
    serial::println("Hello from interrupt");
    serial::println(dstd::to_string(interrupt_num, 16));
    serial::println(dstd::to_string(error_code, 16));
    serial::println(dstd::addr_to_string(static_cast<void*>(interrupt_frame)));
}

}
