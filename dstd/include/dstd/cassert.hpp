#pragma once

#ifdef NDEBUG
#define assert(cond, info) ((void)0)
#else
// TODO: print to screen
#define assert(cond, info) ((void)0) //__FUNCTION__
#endif
