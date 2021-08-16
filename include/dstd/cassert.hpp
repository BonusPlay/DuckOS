#pragma once
#include "serial.hpp"

#ifdef NDEBUG
#define assert(cond) ((void)0)
#else
// TODO: print to screen
#define assert(cond) ((void)0) //__FUNCTION__
#endif
