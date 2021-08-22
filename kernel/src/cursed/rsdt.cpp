#include "cursed/rsdt.hpp"
#include <dstd/cstdint.hpp>
#include <dstd/cstring.hpp>
#include "serial.hpp"

namespace rsdt
{
const constexpr char* RSDP_MAGIC = "RSD PTR ";

uint8_t* find_pointer(uint8_t* addr_from, uint8_t* addr_to)
{
    for(uint8_t* cur_addr = static_cast<uint8_t*>(addr_from); cur_addr < addr_to; ++cur_addr)
    {
        if (*cur_addr == RSDP_MAGIC[0])
        {
            if (dstd::strcmp(reinterpret_cast<const char*>(cur_addr), RSDP_MAGIC) == 0)
                return cur_addr;
        }
    }
    return nullptr;
}

void test()
{

}

}
