#pragma once

extern void assert_fail(const char* info);

#ifdef NDEBUG
#define assert(cond, info) ((void)0)
#else
// TODO: print to screen
#define assert(cond, info) if(!(cond)) \
{ assert_fail(info); }

//__FUNCTION__

#endif
