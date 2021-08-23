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

template< class T >
constexpr T&& forward( dstd::remove_reference_t<T>& t ) noexcept;

template< class T >
constexpr T&& forward( dstd::remove_reference_t<T>&& t ) noexcept;

}
