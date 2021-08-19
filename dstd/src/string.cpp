#include "dstd/string.hpp"
#include "dstd/cassert.hpp"
#include "dstd/cstring.hpp"
#include "dstd/utility.hpp"

namespace dstd
{

String::String(const char* str)
{
    this->length_ = strlen(str);
    const auto size = this->length_ == 0
        ? 0
        : this->length_ + 1;

    this->raw_str_ = new char[size];
    strcpy(this->raw_str_, str, size);
}

String::String(const String& other)
{
    this->length_ = other.length_;
    const auto size = this->length_ == 0
        ? 0
        : this->length_ + 1;

    this->raw_str_ = new char[size];
    strcpy(this->raw_str_, other.raw_str_, size);
}

String::String(String&& other_)
{
    this->length_ = other_.length_;
    this->raw_str_ = move(other_.raw_str_);

    other_.length_ = 0;
    other_.raw_str_ = nullptr;
}

String& String::operator=(const String& other_)
{
    this->length_ = other_.length_;
    const auto size = this->length_ == 0
        ? 0
        : this->length_ + 1;

    this->raw_str_ = new char[size];
    strcpy(this->raw_str_, other_.raw_str_, size);
    return *this;
}

String& String::operator=(String&& other_)
{
    this->length_ = other_.length_;
    this->raw_str_ = move(other_.raw_str_);

    other_.length_ = 0;
    other_.raw_str_ = nullptr;

    return *this;
}

char& String::operator[](uint32_t index_)
{
    assert(index_ >= this->length_);
    return this->raw_str_[index_];
}

const char& String::operator[](uint32_t index_) const
{
    assert(index_ >= this->length_);
    return this->raw_str_[index_];
}

const char* String::data() const
{
    return this->raw_str_;
}

bool String::empty() const
{
    return this->length_ == 0;
}

uint32_t String::length() const
{
    return this->length_;
}

}

#ifdef DSTD_GLOBAL_INTS
dstd::String operator"" _s(const char* str, [[maybe_unused]] uint32_t size)
#else
dstd::String operator"" _s(const char* str, [[maybe_unused]] dstd::uint32_t size)
#endif
{
    return dstd::String(str);
}