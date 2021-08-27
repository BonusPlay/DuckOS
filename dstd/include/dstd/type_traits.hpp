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
    constexpr operator value_type() const { return value; }
    constexpr value_type operator()() const { return value; }
};

using true_type = integral_constant<bool, true>;
using false_type = integral_constant<bool, false>;

template< class T > struct remove_reference      { typedef T type; };
template< class T > struct remove_reference<T&>  { typedef T type; };
template< class T > struct remove_reference<T&&> { typedef T type; };

template< class T >
using remove_reference_t = typename remove_reference<T>::type;

template< class T > struct remove_cv                   { typedef T type; };
template< class T > struct remove_cv<const T>          { typedef T type; };
template< class T > struct remove_cv<volatile T>       { typedef T type; };
template< class T > struct remove_cv<const volatile T> { typedef T type; };

template< class T >
using remove_cv_t = typename remove_cv<T>::type;

template< class T > struct remove_const                { typedef T type; };
template< class T > struct remove_const<const T>       { typedef T type; };

template< class T >
using remove_const_t = typename remove_const<T>::type;

template< class T > struct remove_volatile             { typedef T type; };
template< class T > struct remove_volatile<volatile T> { typedef T type; };

template< class T >
using remove_volatile_t = typename remove_volatile<T>::type;

template< class T >
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};

template< class T >
using remove_cvref_t = typename remove_cvref<T>::type;

template<class T, class U>
struct is_same : false_type {};

template<class T>
struct is_same<T, T> : true_type {};

template< class T, class U >
inline constexpr bool is_same_v = is_same<T, U>::value;

template< class T >
struct is_void : is_same<void, typename remove_cv<T>::type>
{};

template< class T >
inline constexpr bool is_void_v = is_void<T>::value;

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

template <class T> struct is_reference      : false_type {};
template <class T> struct is_reference<T&>  : true_type {};
template <class T> struct is_reference<T&&> : true_type {};

template< class T >
inline constexpr bool is_reference_v = is_reference<T>::value;

template <class T> struct is_const          : false_type {};
template <class T> struct is_const<const T> : true_type {};

template< class T >
inline constexpr bool is_const_v = is_const<T>::value;

template <class T> struct is_volatile             : false_type {};
template <class T> struct is_volatile<volatile T> : true_type {};

template< class T >
inline constexpr bool is_volatile_v = is_volatile<T>::value;

template<class T>
struct is_array : false_type {};
 
template<class T>
struct is_array<T[]> : true_type {};
 
template<class T, uint64_t N>
struct is_array<T[N]> : true_type {};

template< class T >
inline constexpr bool is_array_v = is_array<T>::value;

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

template<bool B, class T = void>
struct enable_if {};

template<class T>
struct enable_if<true, T> { typedef T type; };

template< bool B, class T = void >
using enable_if_t = typename enable_if<B,T>::type;

}
