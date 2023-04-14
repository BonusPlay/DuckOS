#include "utility.hpp"
#include "serial.hpp"

void dump_memory(uintptr_t& addr_from, uintptr_t& addr_to)
{
    dump_memory(reinterpret_cast<uint8_t*>(addr_from), reinterpret_cast<uint8_t*>(addr_to));
}

void dump_memory(uint8_t* addr_from, uint8_t* addr_to)
{
    for (uint8_t* addr_curr = addr_from; addr_curr < addr_to; ++addr_curr)
    {
        if (reinterpret_cast<uint64_t>(addr_curr) % 16 == 0)
        {
            serial::print("\n");
            serial::print(dstd::addr_to_string(addr_curr));
            serial::print(" ");
        }
        serial::print(dstd::to_string(*addr_curr, 16));
        serial::print(" ");
    }
    serial::print("\n");
}
