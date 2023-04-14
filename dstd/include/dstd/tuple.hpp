#pragma once
#include "dstd/assert.hpp"

namespace dstd
{

template<typename... Types>
class Tuple;

// Base case
template<>
class Tuple<>
{};

// Primary template
template<typename T, typename... Types>
class Tuple<T, Types...> : private Tuple<Types...>
{
public:
    [[nodiscard]]
    constexpr Tuple()
    {}

    [[nodiscard]]
    constexpr Tuple(T t, Types... ts)
        : Tuple<Types...>(ts...)
        , value(t)
    {}

    // Get element at index
    template<int Index>
    constexpr auto& get()
    {
        if constexpr (Index == 0)
            return value;
        else
            return Tuple<Types...>::template get<Index - 1>();
    }

    template<int Index>
    constexpr const auto& get() const
    {
        if constexpr (Index == 0)
            return value;
        else
            return Tuple<Types...>::template get<Index - 1>();
    }

private:
    T value;
};

template<typename A, typename B>
using Pair = Tuple<A, B>;

}
