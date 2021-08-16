#pragma once
#include "dstd/cstdint.hpp"

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
