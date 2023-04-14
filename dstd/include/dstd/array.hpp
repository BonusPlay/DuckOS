#pragma once
#include "dstd/assert.hpp"
#include "dstd/cstdint.hpp"

namespace dstd
{

template<class T, size_t N>
struct Array
{
    T data[N];

    [[nodiscard]]
    constexpr T& operator[](size_t pos);

    [[nodiscard]]
    constexpr T& operator[](size_t pos) const;

    constexpr size_t size() const;
};

template<class T, size_t N>
constexpr T& Array<T, N>::operator[](size_t pos)
{
    assert(pos > 0, "position has to be >0");
    assert(pos < N, "out of bounds access");
    return data[pos];
}

template<class T, size_t N>
constexpr T& Array<T, N>::operator[](size_t pos) const
{
    assert(pos > 0, "position has to be >0");
    assert(pos < N, "out of bounds access");
    return data[pos];
}

template<class T, size_t N>
constexpr size_t Array<T, N>::size() const
{
    return N;
}

}
