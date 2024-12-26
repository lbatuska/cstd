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

// Assert sizes are correct
#define bit_to_byte(x) (x / 8)
#define assert_size_in_bits(type, bits)                                        \
  compile_assert_size(sizeof(type) == bit_to_byte(bits));

typedef signed char int8;
typedef unsigned char uint8;
typedef signed short int16;
typedef unsigned short uint16;
typedef signed int int32;
typedef unsigned int uint32;
typedef signed long long int64;
typedef unsigned long long uint64;
typedef unsigned long sizet;

static struct {
  assert_size_in_bits(int8, 8);
  assert_size_in_bits(uint8, 8);
  assert_size_in_bits(int16, 16);
  assert_size_in_bits(uint16, 16);
  assert_size_in_bits(int32, 32);
  assert_size_in_bits(uint32, 32);
  assert_size_in_bits(int64, 64);
  assert_size_in_bits(uint64, 64);
  assert_size_in_bits(sizet, WORDSIZE);
};

#undef compile_assert_size
#undef _compile_assert_size
#undef __compile_assert_size
#undef assert_size_in_bits
#undef bit_to_byte

#include "private/linkage_post.h"
#endif //_DEF_H_
