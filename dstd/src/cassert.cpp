#include "dstd/cassert.hpp"

void assert_fail(const char* info)
{
    __asm__("hlt;");
    /* __asm__(".byte 0xCC"); */
}
