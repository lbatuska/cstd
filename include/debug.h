#ifndef _DEBUG_H_
#define _DEBUG_H_
#include "config.h"
#include <stdio.h>

#include "private/linkage_pre.h"

extern int DEBUG;

#if DEBUG_MESSAGES
#define debug_printf(fmt, ...)                                                 \
  do {                                                                         \
    if (DEBUG) {                                                               \
      printf(fmt, ##__VA_ARGS__);                                              \
    }                                                                          \
  } while (0)

#define debug_fprintf(stream, fmt, ...)                                        \
  do {                                                                         \
    if (DEBUG) {                                                               \
      fprintf(stream, fmt, ##__VA_ARGS__);                                     \
    }                                                                          \
  } while (0)

#define debug_set(x) (DEBUG = x)
#else
#define debug_printf(fmt, ...)
#define debug_fprintf(stream, fmt, ...)
#define debug_set(x)
#endif

#include "private/linkage_post.h"
#endif //_DEBUG_H_
