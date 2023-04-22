#pragma once

#include <dstd/optional.hpp>
#include "memory/phys_addr.hpp"
#include "memory/virt_addr.hpp"

namespace memory
{

//  47    39 | 38   30 | 29   21 | 20   12 | 11      0
// ---------------------------------------------------|
// |  PML4T  |  PML3T  |  PML2T  |  PML1T  |  OFFSET  |
// ---------------------------------------------------|

[[nodiscard]]
dstd::Optional<PhysicalAddress> virt_to_phys(const VirtualAddress<void>& virt_addr);

[[nodiscard]]
dstd::Optional<VirtualAddress<void>> phys_to_virt(const PhysicalAddress& phys_addr);

[[nodiscard]]
constexpr size_t get_pml4t_index(const uintptr_t& virt);

[[nodiscard]]
constexpr size_t get_pml3t_index(const uintptr_t& virt);

[[nodiscard]]
constexpr size_t get_pml2t_index(const uintptr_t& virt);

[[nodiscard]]
constexpr size_t get_pml1t_index(const uintptr_t& virt);

[[nodiscard]]
constexpr size_t get_offset(const uintptr_t& virt);

[[nodiscard]]
uintptr_t get_pml_entry(const uintptr_t table_, size_t index_);

void set_pml_entry(const uintptr_t table_, size_t index_, uintptr_t value_);
void set_pml_entry(const uintptr_t table_, size_t index_, const PhysicalAddress& value_);

[[nodiscard]]
VirtualAddress<void> build_virt_ptr(const size_t& pml4t_index = 0, const size_t& pml3t_index = 0, const size_t& pml2t_index = 0, const size_t& pml1t_index = 0, const uintptr_t& offset = 0);

}
