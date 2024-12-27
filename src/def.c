#include "def.h"

#define __compile_assert_size(cond, b) char __assert_failed_##b[(cond) ? 1 : -1]
#define _compile_assert_size(cond, b) __compile_assert_size(cond, b)
#define compile_assert_size(cond) _compile_assert_size(cond, __COUNTER__)

// Assert sizes are correct
#define bit_to_byte(x) (x / 8)
#define assert_size_in_bits(type, bits)                                        \
  compile_assert_size(sizeof(type) == bit_to_byte(bits));

#if defined __clang__ && !defined __cplusplus
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"

#elif defined __GNUC__ && !defined __cplusplus
#pragma GCC diagnostic push
#pragma gcc diagnostic ignored "-Wmissing-declarations"
#endif

static const struct __attribute__((unused)) {
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

#if defined __clang__ && !defined __cplusplus
#pragma clang diagnostic pop

#elif defined __GNUC__ && !defined __cplusplus
#pragma GCC diagnostic pop
#endif
