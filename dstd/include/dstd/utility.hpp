#pragma once
#include "dstd/type_traits.hpp"

namespace dstd
{

template <typename T>
typename remove_reference<T>::type&& move(T&& arg)
{
    return static_cast<typename remove_reference<T>::type&&>(arg);
}

template<typename T>
void swap(T& t1, T& t2)
{
    T temp = move(t1);
    t1 = move(t2);
    t2 = move(temp);
}

template<class T>
constexpr T&& forward(dstd::remove_reference_t<T>& t)
{
    return static_cast<T&&>(t);
}

template<class T>
constexpr T&& forward(dstd::remove_reference_t<T>&& t)
{
    // TODO: assert this is not an lvalue
    return static_cast<T&&>(t);
}

// stolen from cppreference
template<class T>
constexpr T* addressof(T& arg)
{
    return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
}

[[noreturn]]
inline void unreachable()
{
#ifdef __GNUC__ // GCC, Clang, ICC
    __builtin_unreachable();
#elifdef _MSC_VER // MSVC
    __assume(false);
#endif
}

}
