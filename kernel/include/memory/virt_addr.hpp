#pragma once
#include <dstd/cstdint.hpp>
#include <dstd/cassert.hpp>
#include <dstd/type_traits.hpp>

namespace memory
{

template<typename T = void>
struct VirtualAddress
{
    T* val;

    // note: some voodoo black magic forbits this from being constexpr
    explicit VirtualAddress(uint64_t addr_)
    {
        val = reinterpret_cast<T*>(addr_);
    }

    template<typename T_ = T>
    explicit constexpr VirtualAddress(void* addr_)
    requires(!dstd::is_void_v<T_>)
        : val(static_cast<void*>(addr_))
    {}

    explicit constexpr VirtualAddress(T* addr_)
        : val(addr_)
    {}

    explicit operator uint64_t() const
    {
        return reinterpret_cast<uint64_t>(val);
    }

    template<typename T_ = T>
    T_& operator*() const
    requires(!dstd::is_void_v<T_>)
    {
        assert(val != nullptr, "Attempted to deref nullptr");
        return this->val;
    }

    T* operator->() const
    {
        assert(val != nullptr, "Attempted to deref nullptr");
        return val;
    }

    template<typename U>
    constexpr VirtualAddress<U> as() const
    {
        return VirtualAddress<U>(static_cast<U*>(this->val));
    }
};

}

template<typename T>
inline bool operator==(const memory::VirtualAddress<T>& lhs, const memory::VirtualAddress<T>& rhs)
{
    return lhs.addr == rhs.addr;
}

inline memory::VirtualAddress<void> operator "" _v (unsigned long long addr)
{
    return memory::VirtualAddress<void>{addr};
}

template<typename T>
inline memory::VirtualAddress<T> operator+(const memory::VirtualAddress<T>& addr, uint64_t offset)
{
    return memory::VirtualAddress<T>{reinterpret_cast<uint64_t>(addr.val) + offset};
}
