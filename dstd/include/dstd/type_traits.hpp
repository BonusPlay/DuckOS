#pragma once
#include "dstd/cstdint.hpp"

namespace dstd
{

template<class T, T v>
struct integral_constant
{
    static constexpr T value = v;
    using value_type = T;
    using type = integral_constant;
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator()() const noexcept { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template< class T > struct remove_reference      {typedef T type;};
template< class T > struct remove_reference<T&>  {typedef T type;};
template< class T > struct remove_reference<T&&> {typedef T type;};

template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };

template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };

template< class T > struct remove_volatile             { typedef T type; };
template< class T > struct remove_volatile<volatile T> { typedef T type; };

template<typename>
struct __is_void_helper
    : public false_type
{};

template<>
struct __is_void_helper<void>
    : public true_type
{};

template<typename _Tp>
struct is_void
    : public __is_void_helper<typename remove_cv<_Tp>::type>::type
{};

template<typename>
struct __is_integral_helper
    : public false_type
{};

// WTF why is bool counted as an int
template<>
struct __is_integral_helper<bool>
    : public true_type{};

template<>
struct __is_integral_helper<int>
    : public true_type{};

template<>
struct __is_integral_helper<unsigned int>
    : public true_type{};

template<>
struct __is_integral_helper<int8_t>
    : public true_type{};

template<>
struct __is_integral_helper<uint8_t>
    : public true_type{};

template<>
struct __is_integral_helper<int16_t>
    : public true_type{};

template<>
struct __is_integral_helper<uint16_t>
    : public true_type{};

template<>
struct __is_integral_helper<int32_t>
    : public true_type{};

template<>
struct __is_integral_helper<uint32_t>
    : public true_type{};

template<>
struct __is_integral_helper<int64_t>
    : public true_type{};

template<>
struct __is_integral_helper<uint64_t>
    : public true_type{};

template<typename _Tp>
struct is_integral
    : public __is_integral_helper<typename remove_cv<_Tp>::type>::type
{};

template<class T>
inline constexpr bool is_integral_v = is_integral<T>::value;

}