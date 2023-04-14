#pragma once
#include "dstd/type_traits/base.hpp"
#include "dstd/type_traits/enable_if.hpp"
#include "dstd/type_traits/is_array.hpp"
#include "dstd/type_traits/is_integral.hpp"
#include "dstd/type_traits/is_same.hpp"
#include "dstd/type_traits/is_void.hpp"
#include "dstd/type_traits/references.hpp"
#include "dstd/type_traits/qualifiers.hpp"

namespace dstd
{

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type {};

template< class T >
inline constexpr bool is_const_v = is_const<T>::value;

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type {};

template< class T >
inline constexpr bool is_volatile_v = is_volatile<T>::value;

template<class T>
struct is_function : integral_constant<
    bool,
    !is_const<const T>::value && !is_reference<T>::value
> {};

template< class T >
inline constexpr bool is_function_v = is_function<T>::value;

template<class T>
struct remove_extent { typedef T type; };

template<class T>
struct remove_extent<T[]> { typedef T type; };

template<class T, uint64_t N>
struct remove_extent<T[N]> { typedef T type; };

template< class T >
using remove_extent_t = typename remove_extent<T>::type;

template<bool B, class T, class F>
struct conditional { typedef T type; };

template<class T, class F>
struct conditional<false, T, F> { typedef F type; };

template< bool B, class T, class F >
using conditional_t = typename conditional<B,T,F>::type;

template< class T >
struct decay
{
// NOTE: this isn't fully std compliant as we don't handle
// function ptr case
private:
    typedef remove_reference_t<T> U;
public:
    typedef conditional_t<
        is_array_v<U>,
        remove_extent_t<U>*,
        U
    > type;
};

template< class T >
using decay_t = typename decay<T>::type;

}
