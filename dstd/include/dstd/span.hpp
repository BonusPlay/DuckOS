#pragma once
#include "dstd/assert.hpp"
#include "dstd/cstdint.hpp"
#include "dstd/array.hpp"

namespace dstd
{

inline constexpr size_t dynamic_extent = -1;

template<class T, size_t Extent = dynamic_extent>
class Span
{
public:
    static constexpr size_t extent = Extent;

    // deduction guides
    template<class X, size_t N>
    Span(X (&)[N]) -> Span<X, N>;

    template<class X, size_t N>
    Span(Array<X, N>&) -> Span<X, N>;

    template<class X, size_t N>
    Span(const Array<X, N>&) -> Span<const X, N>;
};

}
