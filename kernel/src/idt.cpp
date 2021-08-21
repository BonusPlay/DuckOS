#include "idt.hpp"
#include <dstd/cstring.hpp>
#include "io.hpp"
#include "utility.hpp"
#include <dstd/string.hpp>
#include "serial.hpp"

// "injected" by linker
extern "C" void _int_handler();
extern idt::IDTEntry _IDT_TABLE_[0x100];

namespace idt
{

uint64_t IDTEntry::get_offset() const
{
    uint64_t offset = 0;
    offset |= static_cast<uint64_t>(this->offset_1);
    offset |= static_cast<uint64_t>(this->offset_2) << 16;
    offset |= static_cast<uint64_t>(this->offset_3) << 32;
    return offset;
}

void IDTEntry::set_offset(uint64_t offset_)
{
    this->offset_1 = offset_ & 0xFFFF;
    this->offset_2 = (offset_ & 0xFFFF0000) >> 16;
    this->offset_3 = offset_ >> 32;
}

void init()
{
    // zero initialize memory, so we don't have to zero initialize members of structs
    dstd::memset(&_IDT_TABLE_, 0, sizeof(IDTEntry) * 0x100);

    for (auto& entry : _IDT_TABLE_)
    {
        entry.selector.index = 1;
        entry.type_attr.present = 0x01;
        entry.type_attr.type = GateType::INTERRUPT_GATE;
        entry.set_offset(reinterpret_cast<uint64_t>(&_int_handler));
    }

    auto ptr = IDTRegister{};
    ptr.limit = sizeof(IDTEntry) * 0x100 - 1;
    ptr.base = reinterpret_cast<uint64_t>(&_IDT_TABLE_);

     __asm__ ("lidt %0" :: "m"(ptr));
}

}
