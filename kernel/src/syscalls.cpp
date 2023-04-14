#include "syscalls.hpp"
#include "io.hpp"
#include "log.hpp"
#include <dstd/assert.hpp>

extern uint64_t _SYSCALL_ENTRY_;

namespace syscalls
{

void syscall_handler()
{
    log::debug("sycall handler");
}

void setup()
{
    // test for syscall instruction support
    const auto info = io::CPUID(0x80000001, 0);
    const auto supported = ((info.edx >> 11) & 1) != 0;
    log::debug("eax: ", info.eax, " ebx: ", info.ebx, " ecx: ", info.ecx, " edx: ", info.edx);
    assert(supported, "SYSCALL not supported by CPU");

    {
        // enable syscalls
        auto tmp = io::rdmsr(io::MSR_IA32_EFER); 
        tmp |= 1;
        io::wrmsr(io::MSR_IA32_EFER, tmp);
    }

    {
        // setup STAR msr

        /*
         * 63                 48 47                 32 31               0
         * --------------------------------------------------------------
         * |                    |                     |                 |
         * |   SYSRET CS & SS   |   SYSCALL CS & SS   |   32bit stuff   | 
         * |                    |                     |                 |
         * --------------------------------------------------------------
         *
         *  we don't use 32 bit stuff
         *
         *  segments in GDT:
         *  0x00 => Kernel_Null
         *  0x08 => Kernel_Code
         *  0x10 => Kernel_Data
         *  0x18 => User_Null
         *  0x20 => User_Code
         *  0x28 => User_Data
         *
         *  We load null segemnts into MSR, because CPU loads +8 and +16 respectively.
         */
        // cppcheck-suppress[badBitmaskCheck]
        auto star = (static_cast<uint64_t>(0x00) << 48) | (static_cast<uint64_t>(0x00) << 32);
        io::wrmsr(io::MSR_IA32_STAR, star);
    }

    {
        // setup LSTAR msr
        // contains target RIP for syscall
        log::debug("_SYSCALL_ENTRY_ at: ", reinterpret_cast<uint64_t>(&_SYSCALL_ENTRY_));
        io::wrmsr(io::MSR_IA32_LSTAR, reinterpret_cast<uint64_t>(&_SYSCALL_ENTRY_));
    }
}

}
