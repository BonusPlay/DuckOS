#pragma once
#include "dstd/cstdint.hpp"
#include "dstd/cassert.hpp"
#include "dstd/cstring.hpp"
#include "dstd/utility.hpp"

namespace dstd
{

template<class T>
class Vector
{
public:
    constexpr Vector();
    constexpr explicit Vector(uint64_t size);
    constexpr Vector(const Vector&);
    constexpr Vector(Vector&&);
    constexpr Vector& operator=(const Vector&);
    constexpr Vector& operator=(Vector&&);
    constexpr ~Vector();

    constexpr T& operator[](uint64_t pos);
    constexpr const T& operator[](uint64_t pos) const;

    constexpr T* data();
    constexpr const T* data() const;

    constexpr bool empty() const;
    constexpr uint64_t size() const;
    constexpr uint64_t capacity() const;

    constexpr void clear();

private:
    uint64_t capacity_ = 0;
    uint64_t length_ = 0;
    T* data_ = nullptr;
};

template<class T>
constexpr Vector<T>::Vector()
    : Vector<T>::Vector(0)
{}

template<class T>
constexpr Vector<T>::Vector(uint64_t size)
    : capacity_(size), length_(size)
{
    if (this->capacity_ != 0)
        this->data_ = new T[this->capacity_];
}

template<class T>
constexpr Vector<T>::Vector(const Vector<T>& other)
{
    this->capacity_ = other.capacity_;
    this->length_ = other.length_;
    this->data_ = new T[this->capacity_];
    memcpy(this->data_, other->data_, sizeof(this->data_));
}

template<class T>
constexpr Vector<T>::Vector(Vector<T>&& other)
{
    this->capacity_ = other.capacity_;
    this->length_ = other.length_;
    this->data_ = move(other.data_);

    other.capacity_ = 0;
    other.length_ = 0;
    other.data_ = nullptr;
}

template<class T>
constexpr Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
    this->capacity_ = other.capacity_;
    this->length_ = other.length_;
    this->data = new T[this->capacity_];
    memcpy(this->data_, other->data_, sizeof(this->data_));
    return *this;
}

template<class T>
constexpr Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
    this->capacity_ = other.capacity_;
    this->length_ = other.length_;
    this->data = move(other.data_);

    other.capacity_ = 0;
    other.length_ = 0;
    other.data_ = nullptr;

    return *this;
}

template<class T>
constexpr Vector<T>::~Vector<T>()
{
    if (this->data_)
        delete[] this->data_;
}

template<class T>
constexpr T& Vector<T>::operator[](uint64_t pos)
{
    assert(pos > 0, "position has to be >0");
    assert(pos <= length_, "invalid position");
    return this->data_[pos];
}

template<class T>
constexpr const T& Vector<T>::operator[](uint64_t pos) const
{
    assert(pos > 0, "position has to be >0");
    assert(pos <= length_, "invalid position");
    return this->data_[pos];
}

template<class T>
constexpr T* Vector<T>::data()
{
    return data_;
}

template<class T>
constexpr const T* Vector<T>::data() const
{
    return data_;
}

template<class T>
constexpr bool Vector<T>::empty() const
{
    return length_ == 0;
}

template<class T>
constexpr uint64_t Vector<T>::size() const
{
    return length_;
}

template<class T>
constexpr uint64_t Vector<T>::capacity() const
{
    return capacity_;
}

template<class T>
constexpr void Vector<T>::clear()
{}

}
