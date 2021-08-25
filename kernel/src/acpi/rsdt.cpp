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
    for(auto* cur_addr = static_cast<char*>(addr_from.addr); cur_addr < addr_to.addr; ++cur_addr)
    {
        if (*cur_addr == RSDP_MAGIC[0])
        {
            if (dstd::strcmp(reinterpret_cast<const char*>(cur_addr), RSDP_MAGIC) == 0)
                return memory::PhysicalAddress{static_cast<void*>(cur_addr)};
        }
    }
    return memory::PhysicalAddress{nullptr};
}

void rsdt_test()
{
    auto addr_1 = find_pointer(0x00000000_p, 0x00000400_p);
    serial::print("RSDP: ");
    serial::println(dstd::addr_to_string(addr_1.addr));

    auto addr_2 = find_pointer(0x000E0000_p, 0x000FFFFF_p);
    serial::print("RSDP: ");
    serial::println(dstd::addr_to_string(addr_2.addr));
}

}
