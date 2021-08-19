#pragma once

// it's REAAAAAAALY annoying not to have these types global,
// while it's required to namespace them for unit tests
#ifndef DSTD_GLOBAL_INTS
namespace dstd
{
#endif

using int8_t   = signed char;
using int16_t  = signed short;
using int32_t  = signed long;
using int64_t  = signed long long;
using uint8_t  = unsigned char;
using uint16_t = unsigned short;
using uint32_t = unsigned long;
using uint64_t = unsigned long long;

#ifndef DSTD_GLOBAL_INTS
}
#endif
