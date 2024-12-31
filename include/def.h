#ifndef _DEF_H_
#define _DEF_H_
#include "config.h"
#include "private/linkage_pre.h"
#include "wordsize.h"
#include <stdint.h>

// For unsigned types: max = all bits set to 1, min = 0
// For signed types: max = (2^bits - 1), min = -(2^bits - 1) - 1

typedef signed char int8;
#define MAX_INT8 ((int8)((1 << (sizeof(int8) * 8 - 1)) - 1))
#define MIN_INT8 ((int8)(-(1 << (sizeof(int8) * 8 - 1))))
typedef unsigned char uint8;
#define MAX_UINT8 ((uint8)(~(uint8)0))
#define MIN_UINT8 (0)

typedef signed short int16;
#define MAX_INT16 ((int16)((1 << (sizeof(int16) * 8 - 1)) - 1))
#define MIN_INT16 ((int16)(-(1 << (sizeof(int16) * 8 - 1))))
typedef unsigned short uint16;
#define MAX_UINT16 ((uint16)(~(uint16)0))
#define MIN_UINT16 (0)

typedef signed int int32;
#define MAX_INT32 ((int32)((1 << (sizeof(int32) * 8 - 1)) - 1))
#define MIN_INT32 ((int32)(-(1 << (sizeof(int32) * 8 - 1))))
typedef unsigned int uint32;
#define MAX_UINT32 ((uint32)(~(uint32)0))
#define MIN_UINT32 (0)

typedef signed long long int64;
#define MAX_INT64 ((int64)((1LL << (sizeof(int64) * 8 - 1)) - 1))
#define MIN_INT64 ((int64)(-(1LL << (sizeof(int64) * 8 - 1))))
typedef unsigned long long uint64;
#define MAX_UINT64 ((uint64)(~(uint64)0))
#define MIN_UINT64 (0)

typedef unsigned long sizet;
#define MAX_SIZET ((sizet)(~(sizet)0))
#define MIN_SIZET (0)

typedef typeof((void *)0 - (void *)0) ptrdifft;
#define MAX_PTRDIFF ((ptrdifft)((1 << (sizeof(ptrdifft) * 8 - 1)) - 1))
#define MIN_PTRDIFF ((ptrdifft)(-(1 << (sizeof(ptrdifft) * 8 - 1))))

typedef unsigned long uintptrt;
#define MAX_UINTPTRT ((uintptrt)(~(uintptrt)0))
#define MIN_UINTPTRT (0)

typedef long intptrt;
#define MAX_INTPTRT ((intptrt)((1L << (sizeof(intptrt) * 8 - 1)) - 1))
#define MIN_INTPTRT ((intptrt)(-(1L << (sizeof(intptrt) * 8 - 1))))

#include "private/linkage_post.h"
#endif //_DEF_H_
