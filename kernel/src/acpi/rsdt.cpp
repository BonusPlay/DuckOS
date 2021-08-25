#include "acpi/rsdt.hpp"
#include <dstd/cstdint.hpp>
#include <dstd/cstring.hpp>
#include "serial.hpp"
#include "memory/phys_addr.hpp"

namespace acpi
{
const constexpr char* RSDP_MAGIC = "RSD PTR ";

memory::PhysicalAddress find_pointer(memory::PhysicalAddress addr_from, memory::PhysicalAddress addr_to)
{
    for(uint8_t* cur_addr = static_cast<uint8_t*>(addr_from.addr); cur_addr < addr_to.addr; ++cur_addr)
    {
        if (*cur_addr == RSDP_MAGIC[0])
        {
            if (dstd::strcmp(reinterpret_cast<const char*>(cur_addr), RSDP_MAGIC) == 0)
                return memory::PhysicalAddress{cur_addr};
        }
    }
    return memory::PhysicalAddress{nullptr};
}

void test()
{

}

}
