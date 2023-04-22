#include "dstd/assert.hpp"
#include "dstd/utility.hpp"

[[noreturn]]
void assert_fail([[maybe_unused]] const char* info)
{
    __asm__("hlt;");
    dstd::unreachable();
    /* __asm__(".byte 0xCC"); */
}
