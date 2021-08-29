#pragma once

#ifdef NDEBUG
#define assert(cond, info) ((void)0)
#else
// TODO: print to screen
#define assert(cond, info) if(!(cond)) \
{ __asm__(".byte 0xCC"); }

//__FUNCTION__
#endif
