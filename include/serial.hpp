#pragma once
#include "dstd/string.hpp"

namespace serial
{

constexpr uint16_t PORT_COM1 = 0x3F8;

bool init(uint16_t port = PORT_COM1);
void test();
void regs();
void xdd(uint32_t);
void print(const dstd::String&);

}
