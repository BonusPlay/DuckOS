#pragma once
#include "dstd/assert.hpp"
#include "dstd/utility.hpp"
#include "dstd/type_traits.hpp"
#include "dstd/impl/storage.hpp"

namespace dstd
{

template<class T, class E>
class Expected
{
public:
    static_assert(!is_same_v<T, E>, "[Expected] Value type T and Error type E can't be same");

    [[nodiscard]]
    constexpr explicit Expected(T value_);
    [[nodiscard]]
    constexpr explicit Expected(E error_);

    constexpr const T* operator->() const;
    constexpr T* operator->();
    constexpr const T& operator*() const&;
    constexpr T& operator*() &;
    constexpr const T&& operator*() const&&;
    constexpr T&& operator*() &&;

    constexpr explicit operator bool() const;
    constexpr bool has_value() const;

    constexpr const E& error() const&;
    constexpr E& error() &;
    constexpr const E&& error() const&&;
    constexpr E&& error() &&;

    // TODO: T must meet the requirements of CopyConstructible in order to use overload (1).
    // TODO: T must meet the requirements of MoveConstructible in order to use overload (2).
    // TODO: U&& must be convertible to T
    /* template<class U> */
    /* constexpr T value_or(U&& default_value) const&; */

    /* template<class U> */
    /* constexpr T value_or(U&& default_value) &&; */

private:
    bool empty;
    impl::storage_t<T> storage_value;
    impl::storage_t<E> storage_error;
};

template<class T, class E>
Expected<T, E> Unexpected(E error_)
{
    return Expected<T, E>{forward<E>(error_)};
}

template<class T, class E>
constexpr Expected<T, E>::Expected(T value_)
    : empty(false),
      storage_value(forward<T>(value_)),
      storage_error(impl::dummy_init)
{}

template<class T, class E>
constexpr Expected<T, E>::Expected(E error_)
    : empty(true),
      storage_value(impl::dummy_init),
      storage_error(forward<E>(error_))
{}

template<class T, class E>
constexpr Expected<T, E>::operator bool() const
{
    return !empty;
}

template<class T, class E>
constexpr bool Expected<T, E>::has_value() const
{
    return !empty;
}

template<class T, class E>
constexpr const T* Expected<T, E>::operator->() const
{
    assert(!this->empty, "dereferenced empty Expected");
    return &this->storage_value.value;
}

template<class T, class E>
constexpr T* Expected<T, E>::operator->()
{
    assert(!this->empty, "dereferenced empty Expected");
    return &this->storage_value.value;
}

template<class T, class E>
constexpr const T& Expected<T, E>::operator*() const&
{
    assert(!this->empty, "dereferenced empty Expected");
    return this->storage_value.value;
}

template<class T, class E>
constexpr T& Expected<T, E>::operator*() &
{
    assert(!this->empty, "dereferenced empty Expected");
    return this->storage_value.value;
}

template<class T, class E>
constexpr const T&& Expected<T, E>::operator*() const&&
{
    assert(!this->empty, "dereferenced empty Expected");
    return move(this->storage_value.value);
}

template<class T, class E>
constexpr T&& Expected<T, E>::operator*() &&
{
    assert(!this->empty, "dereferenced empty Expected");
    return move(this->storage_value.value);
}

template<class T, class E>
constexpr const E& Expected<T, E>::error() const&
{
    assert(this->empty, "attempted to get error from not empty Expected");
    return this->storage_error.value;
}

template<class T, class E>
constexpr E& Expected<T, E>::error() &
{
    assert(this->empty, "attempted to get error from not empty Expected");
    return this->storage_error.value;
}

template<class T, class E>
constexpr const E&& Expected<T, E>::error() const&&
{
    assert(this->empty, "attempted to get error from not empty Expected");
    return move(this->storage_error.value);
}

template<class T, class E>
constexpr E&& Expected<T, E>::error() &&
{
    assert(this->empty, "attempted to get error from not empty Expected");
    return &this->storage_error.value;
}

}
