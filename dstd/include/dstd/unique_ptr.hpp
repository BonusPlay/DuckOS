#pragma once
#include "dstd/assert.hpp"
#include "dstd/utility.hpp"

namespace dstd
{

template<class T>
struct DefaultDeleter
{
    void operator()(T* ptr) const
    {
        delete ptr;
    }
};

template<class T, class Deleter = DefaultDeleter<T>>
class UniquePtr
{
public:
    constexpr UniquePtr();
    explicit UniquePtr(T* ptr);
    UniquePtr(const UniquePtr&) = delete;
    UniquePtr(UniquePtr&&);
    UniquePtr& operator=(const UniquePtr&) = delete;
    UniquePtr& operator=(UniquePtr&&);
    ~UniquePtr();

    T* release();
    void reset(T* ptr);
    void swap(UniquePtr<T, Deleter> other);

    T* get() const;
    explicit operator bool() const;
    T& operator*() const;
    T* operator->() const;

private:
    T* data_;
    Deleter deleter_;
};

template<class T, class D>
constexpr UniquePtr<T, D>::UniquePtr()
    : data_(nullptr)
{}

template<class T, class D>
UniquePtr<T,D>::UniquePtr(T* ptr)
    : data_(ptr)
{}

template<class T, class D>
UniquePtr<T,D>::UniquePtr(UniquePtr<T,D>&& other)
{
    this->reset(nullptr);
    this->swap(other);
}

template<class T, class D>
UniquePtr<T,D>& UniquePtr<T,D>::operator=(UniquePtr<T,D>&& other)
{
    this->reset(nullptr);
    this->swap(other);
    return *this;
}

template<class T, class D>
UniquePtr<T,D>::~UniquePtr()
{
    if (this->data_)
        this->deleter_(this->data_);
}

template<class T, class D>
T* UniquePtr<T,D>::release()
{
    const auto* ret = this->data_;
    this->data_ = nullptr;
    return ret;
}

template<class T, class D>
void UniquePtr<T,D>::reset(T* ptr)
{
    const auto* old_ptr = this->data_;
    this->data_ = ptr;
    if (old_ptr)
        this->deleter_(old_ptr);
}

template<class T, class D>
void UniquePtr<T,D>::swap(UniquePtr<T,D> other)
{
    dstd::swap(this->data_, other.data_);
    dstd::swap(this->deleter_, other.deleter_);
}

template<class T, class D>
T* UniquePtr<T,D>::get() const
{
    return this->data_;
}

template<class T, class D>
UniquePtr<T,D>::operator bool() const
{
    return this->data_ != nullptr;
}

template<class T, class D>
T& UniquePtr<T,D>::operator*() const
{
    assert(this->data_, "attempted to dereference nullptr");
    return *this->data_;
}

template<class T, class D>
T* UniquePtr<T,D>::operator->() const
{
    assert(this->data_, "attempted to dereference nullptr");
    return this->data_;
}

}
