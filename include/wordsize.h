#ifndef _WORDSIZE_H_
#define _WORDSIZE_H_
#include "config.h"
#include "private/linkage_pre.h"

#ifdef WORDSIZE

#if WORDSIZE == 64

#define IS_64_BIT 1
#define IS_32_BIT 0
#if DEBUG_COMPILE
#warning "Word size is 64 bit."
#endif

#elif WORDSIZE == 32

#define IS_64_BIT 0
#define IS_32_BIT 1
#if DEBUG_COMPILE
#warning "Word size is 32 bit."
#endif

#else // WORDSIZE NOT 32 or 64

#undef IS_64_BIT
#undef IS_32_BIT
#if DEBUG_COMPILE
#warning "Word size is defined but not 32 or 64 bit."
#endif

#endif // WORDSIZE ==
#endif // IF WORDSIZE is defined
// ---------------------------------------------

#if !defined(WORDSIZE) && (defined(IS_64_BIT) && IS_64_BIT)

#define WORDSIZE 64
#define IS_32_BIT 0
#if DEBUG_COMPILE
#warning "Word size is 64 bit."
#endif

#endif
// ---------------------------------------------

#if !defined(WORDSIZE) && (defined(IS_32_BIT) && IS_32_BIT)

#define WORDSIZE 32
#define IS_64_BIT 0
#if DEBUG_COMPILE
#warning "Word size is 32 bit."
#endif

#endif

// ---------------------------------------------
#if !defined(WORDSIZE)

#if defined(__LP64__) || defined(_WIN64) ||                                    \
    (defined(__x86_64__) && !defined(__ILP32__)) || defined(_M_X64) ||         \
    defined(__ia64) || defined(_M_IA64) || defined(__aarch64__) ||             \
    defined(__powerpc64__) || defined(__ppc64__)
#define WORDSIZE 64
#define IS_64_BIT 1
#define IS_32_BIT 0
#if DEBUG_COMPILE
#warning "Word size determined as 64 bit."
#endif
#elif defined(__i386__) || defined(__x86__) || defined(_M_IX86) ||             \
    defined(__arm__) || defined(_M_ARM) || defined(__mips__) ||                \
    defined(_M_MRX000) || defined(__sh__) || defined(_M_SH) ||                 \
    defined(__alpha__) || defined(_M_ALPHA) || defined(__sparc__) ||           \
    defined(__hppa__) || defined(__s390__) || defined(_M_S390)
#define WORDSIZE 32
#define IS_64_BIT 0
#define IS_32_BIT 1
#if DEBUG_COMPILE
#warning "Word size determined as 32 bit."
#endif
#else
#if DEBUG_COMPILE
#warning "Failed to automatically determine word size!"
#endif
#endif

#endif // If WORDSIZE is not defined

#include "private/linkage_post.h"
#endif //_WORDSIZE_H_
