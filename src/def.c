#include "def.h"

#define __compile_assert_size(cond, b) char __assert_failed_##b[(cond) ? 1 : -1]
#define _compile_assert_size(cond, b) __compile_assert_size(cond, b)
#define compile_assert_size(cond) _compile_assert_size(cond, __COUNTER__)

// Assert sizes are correct
#define bit_to_byte(x) (x / 8)
#define assert_size_in_bits(type, bits)                                        \
  compile_assert_size(sizeof(type) == bit_to_byte(bits));

struct __attribute__((unused)) _ {
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
