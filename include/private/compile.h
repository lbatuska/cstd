#ifndef _COMPILE_PRIVATE_H_
#define _COMPILE_PRIVATE_H_
#include "config.h"
#include "private/linkage_pre.h"

// preamble

#ifndef __has_builtin
#define __has_builtin(x) 0
#if DEBUG_COMPILE
#warning "No __has_builtin!"
#endif
#endif

#ifndef __has_attribute
#define __has_attribute(x) 0
#if DEBUG_COMPILE
#warning "No __has_attribute!"
#endif
#endif

#if __has_attribute(__noreturn__)
#define __noreturn __attribute__((__noreturn__))
#else
#define __noreturn
#endif

#if __has_attribute(__warn_unused_result__)
#define __nodiscard __attribute__((__warn_unused_result__))
#else
#define __nodiscard
#endif

#if __has_attribute(__error__)
#define __compiletime_error(msg) __attribute__((__error__(msg)))
#else
#define __compiletime_error(msg)
#endif

// internal functions

#if !OPTIMIZE
#define __compiletime_assert(condition, msg, prefix, suffix)                   \
  do {                                                                         \
    __noreturn extern void prefix##suffix(void) __compiletime_error(msg);      \
    if (!(condition))                                                          \
      prefix##suffix();                                                        \
  } while (0)
#else
#define __compiletime_assert(condition, msg, prefix, suffix)                   \
  do {                                                                         \
  } while (0)
#endif

// double indirection to let the macros expand correctly
#define _compiletime_assert(condition, msg, prefix, suffix)                    \
  __compiletime_assert(condition, msg, prefix, suffix)

#define __static_assert(expr, msg, ...) _Static_assert(expr, msg)

#define __unsigned_signed_type_expression(T)                                   \
  unsigned T : (unsigned T)0, signed T : (signed T)0

#include "private/linkage_post.h"
#endif //_COMPILE_PRIVATE_H_
