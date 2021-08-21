#pragma once
#include "dstd/cstdint.hpp"

// IDT => Interrupt Descriptor Table

namespace idt
{

enum class TableIndicator
{
    GDT = 0x0,
    LDT = 0x1,
} __attribute__((packed));

struct SegmentSelector
{
    uint8_t rpl : 2;
    TableIndicator table_indicator : 1;
    uint16_t index : 13;
} __attribute__((packed));

enum class GateType : uint8_t
{
    CALL_GATE = 0xC,
    INTERRUPT_GATE = 0xE,
    TRAP_GATE = 0xF,
} __attribute__((packed));

struct GateAttr
{
    GateType type : 4;
    uint8_t zero : 1;
    uint8_t dpl : 2;
    uint8_t present : 1;    
} __attribute__((packed));

struct IDTEntry
{
    uint16_t offset_1; // offset bits 0..15
    SegmentSelector selector; // a code segment selector in GDT or LDT
    /* uint16_t selector; */
    uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
    GateAttr type_attr; // type and attributes
    uint16_t offset_2; // offset bits 16..31
    uint32_t offset_3; // offset bits 32..63
    uint32_t zero;

    uint64_t* get_offset() const;
    void set_offset(uint64_t* offset_);
} __attribute__((packed));

static_assert(sizeof(IDTEntry::offset_1) == 2);
static_assert(sizeof(IDTEntry::selector) == 2);
static_assert(sizeof(IDTEntry::ist) == 1);
static_assert(sizeof(IDTEntry::type_attr) == 1);
static_assert(sizeof(IDTEntry::offset_2) == 2);
static_assert(sizeof(IDTEntry::offset_3) == 4);
static_assert(sizeof(IDTEntry::zero) == 4);
static_assert(sizeof(IDTEntry) == 16);

struct IDTRegister
{
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

void init();

extern "C"
void interrupt_handler();

}
