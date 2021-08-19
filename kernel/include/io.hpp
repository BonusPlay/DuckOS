#pragma once
#include "dstd/cstdint.hpp"

constexpr uint32_t MSR_IA32_EFER = 0xC0000080;

inline void out(uint16_t port, uint8_t val)
{
    /* __asm__ volatile (
     *     ".intel_syntax;"
     *     "out %[port], %[value];"
     *     :
     *     : [value] "a" (val), [port] "Nd" (port)
     *     :); */
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

inline uint8_t inb(uint16_t port)
{
    // https://c9x.me/x86/html/file_module_x86_id_222.html
    uint8_t ret;
    /* __asm__ volatile (
     *     ".intel_syntax;"
     *     "in %[result], %[port];"
     *     : [result] "=a"(ret)
     *     : [port] "Nd"(port)
     *     :); */   
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

inline void wrmsr(uint64_t msr_id_, uint64_t value_)
{
	uint32_t low = value_ & 0xFFFFFFFF;
	uint32_t high = value_ >> 32;
	asm volatile (
		"wrmsr"
		:
		: "c"(msr_id_), "a"(low), "d"(high)
	);
}

inline uint64_t rdmsr(uint64_t msr_id_)
{
    uint32_t low;
    uint32_t high;
    asm volatile (
        "rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr_id_)
	);
    return (static_cast<uint64_t>(high) << 32) | low;
}
