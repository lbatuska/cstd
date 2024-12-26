#ifndef _DEF_H_
#define _DEF_H_
#include "config.h"
#include "private/linkage_pre.h"
#include "wordsize.h"

#if defined __clang__ && !defined __cplusplus
#pragma clang diagnostic ignored "-Wmissing-declarations"
#elif defined __GNUC__ && !defined __cplusplus
#pragma gcc diagnostic ignored "-Wmissing-declarations"
#endif

#define __compile_assert_size(cond, b) char __assert_failed_##b[(cond) ? 1 : -1]
#define _compile_assert_size(cond, b) __compile_assert_size(cond, b)
#define compile_assert_size(cond) _compile_assert_size(cond, __COUNTER__)

// Assert sizes are correct before typedefs
static struct {
  compile_assert_size(sizeof(long long) == (64 / 8));
  compile_assert_size(sizeof(long) == (WORDSIZE / 8));
  compile_assert_size(sizeof(int) == (32 / 8));
  compile_assert_size(sizeof(short) == (16 / 8));
  compile_assert_size(sizeof(char) == (8 / 8));
};

#undef compile_assert_size
#undef _compile_assert_size
#undef __compile_assert_size

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long long int64;
typedef unsigned long long uint64;
typedef unsigned long sizet;

#include "private/linkage_post.h"
#endif //_DEF_H_
