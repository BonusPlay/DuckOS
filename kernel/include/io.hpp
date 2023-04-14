#pragma once
#include <dstd/cstdint.hpp>

namespace io
{

constexpr uint32_t MSR_IA32_APIC_BASE = 0x1B;
constexpr uint32_t MSR_IA32_EFER = 0xC0000080;
constexpr uint32_t MSR_IA32_STAR = 0xC0000081;
constexpr uint32_t MSR_IA32_LSTAR = 0xC0000082;

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

template<uint8_t num>
inline void interrupt()
{
    static_assert(num <128,  "Interrupt has to be below 128");
    asm volatile (
        "int %0"
        :
        : "N"(num)
    );
}

inline void syscall()
{
    asm volatile (
        "syscall"
    );
}

struct CPUID
{
    // cppcheck-suppress[uninitMemberVar]
    CPUID(uint32_t leaf, uint32_t subleaf)
        : leaf(leaf), subleaf(subleaf)
    {
        asm volatile (
            "cpuid"
            : "=a" (eax), "=b" (ebx), "=c" (ecx), "=d" (edx)
            : "a" (this->leaf), "c" (this->subleaf)
        );
    }

    uint32_t leaf;
    uint32_t subleaf;

    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
};

inline uint64_t get_cr3()
{
    uint64_t cr3;
    asm volatile (
        "mov %%cr3, %0;"
        : "=r" (cr3)
    );
    return cr3;
}

inline void set_cr3(uint64_t val)
{
    asm volatile (
        "mov %0, %%cr3;"
        :
        : "r" (val)
    );
}

}
