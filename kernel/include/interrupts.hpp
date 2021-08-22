#pragma once
#include <dstd/cstdint.hpp>

namespace interrupts
{

enum class Interrupt : uint8_t
{
    DIVIDE_BY_ZERO = 0x0,
    DEBUG = 0x1,
    NMI = 0x2,
    BREAKPOINT = 0x3,
    OVERFLOW = 0x4,
    BOUND_RANGE_EXCEEDED = 0x5,
    INVALID_OPCODE = 0x6,
    DEVICE_NOT_AVAILABLE = 0x7,
    DOUBLE_FAULT = 0x8,
    INVALID_TSS = 0xA,
    SEGMENT_NOT_PRESENT = 0xB,
    STACK_SEGMENT_FAULT = 0xC,
    GENERAL_PROTECTION_FAULT = 0xD,
    PAGE_FAULT = 0xE,
    X86_FLOATING_POINT_EXCEPTION = 0x10,
    ALIGNMENT_CHECK = 0x11,
    MACHINE_CHECK = 0x12,
    SIMD_FLOATING_POINT_EXCEPTION = 0x13,
    VIRTUALIZATION_EXCEPTIOIN = 0x14,
    SECURITY_EXCEPTION = 0x1E,
};

struct PageFaultError
{
    bool protection : 1;
    // 0 => read
    // 1 => write
    bool write : 1;
    // 0 => CPL<3
    // 1 => CPL=3
    bool user : 1;
    // 0 => OK
    // 1 => reserved bit writen to
    bool reserved_write : 1;
    bool instruction_fetch : 1;
    uint32_t reserved : 28;

    static PageFaultError from_error_code(uint32_t);
};

static_assert(sizeof(PageFaultError) == 8);

}
