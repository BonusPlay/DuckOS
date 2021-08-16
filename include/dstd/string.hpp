#pragma once
#include "dstd/cstdint.hpp"

namespace dstd {

class String
{
public:
    String(const char*);
    String(const String&);
    String(String&&);
    String& operator=(const String&);
    String& operator=(String&&);

    char& operator[](uint32_t index);
    const char& operator[](uint32_t index) const;
    const char* data() const;
    bool empty() const;
    uint32_t length() const;

private:
    uint32_t length_;
    char* raw_str_;
};

String to_string(const uint8_t);
String to_string(const uint16_t);
String to_string(const uint32_t);
String to_string(const uint64_t);

}

// TODO: make this constexpr
dstd::String operator "" _s(const char*, uint32_t);
