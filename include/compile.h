#ifndef _COMPILE_H_
#define _COMPILE_H_
#include "config.h"
#include "private/linkage_pre.h"

#include "private/compile.h"

// Drops all qualifiers but keeps signedness, char is distinct from signed char
#define typeof_unqualified_scalar(x)                                           \
  typeof(_Generic((x),                                                         \
      char: (char)0,                                                           \
      __unsigned_signed_type_expression(char),                                 \
      __unsigned_signed_type_expression(short),                                \
      __unsigned_signed_type_expression(int),                                  \
      __unsigned_signed_type_expression(long),                                 \
      __unsigned_signed_type_expression(long long),                            \
      default: (x)))

#define same_type(a, b) __builtin_types_compatible_p(typeof(a), typeof(b))

#define compiletime_assert_msg(condition,                                      \
                               msg) /*Breaks compilation on false condition*/  \
  _compiletime_assert(condition, msg, __compiletime_assert_, __COUNTER__)

#define compiletime_assert(                                                    \
    condition) /*Breaks compilation on false condition*/                       \
  compiletime_assert_msg(condition, #condition)

#define static_assert(expr, ...) /*Breaks compilation on false condition*/     \
  __static_assert(expr, ##__VA_ARGS__, #expr)

#define break_compile_msg(condition,                                           \
                          msg) /*Breaks compilation on true condition*/        \
  compiletime_assert_msg(!(condition), msg)

#define break_compile(condition) /*Breaks compilation on true condition*/      \
  break_compile_msg(condition, #condition)

#define is_native_word(t)                                                      \
  (sizeof(t) == sizeof(char) || sizeof(t) == sizeof(short) ||                  \
   sizeof(t) == sizeof(int) || sizeof(t) == sizeof(long))

#define is_native_word_64(t)                                                   \
  (is_native_word(t) || sizeof(t) == sizeof(long long))

#define compiletime_assert_atomic_type(t)                                      \
  compiletime_assert_msg(is_native_word(t),                                    \
                         "Need native word sized stores/loads for atomicity.")

#define compiletime_assert_atomic_type_64(t)                                   \
  compiletime_assert_msg(is_native_word_64(t),                                 \
                         "Need native word sized stores/loads for atomicity.")

// https://scaryreasoner.wordpress.com/2009/02/28/checking-sizeof-at-compile-time/
// #define BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2 * !!(condition)]))

#include "private/linkage_post.h"
#endif //_COMPILE_H_
