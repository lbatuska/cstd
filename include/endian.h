#ifndef _ENDIAN_H_
#define _ENDIAN_H_
#include "config.h"
#include "private/linkage_pre.h"

// We can also include the system endian.h
// #ifdef __GNUC__
// #include_next <endian.h>
// #endif

#define __little_endian 0x41424344UL
#define __big_endian 0x44434241UL
#define __pdp_endian 0x42414443UL
#define __endian_order ('ABCD')

#if __endian_order == __big_endian
#define IS_LITTLE_ENDIAN 0
#define IS_BIG_ENDIAN 1
#if DEBUG_COMPILE
#warning "Big endian system!"
#endif
#elif __endian_order == __little_endian
#define IS_LITTLE_ENDIAN 1
#define IS_BIG_ENDIAN 0
#if DEBUG_COMPILE
#warning "Little endian system!"
#endif
#elif __endian_order == __pdp_endian
#error "PDP endian unsupported!"
#else
#error "Unknown endianness!"
#endif

#include "private/linkage_post.h"

#endif //_ENDIAN_H_
