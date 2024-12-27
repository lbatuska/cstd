#ifndef _TRACE_H_
#define _TRACE_H_
#include "config.h"
#include "def.h"
#include <stdio.h>

#include "private/linkage_pre.h"

extern uint8 TRACE_RUNTIME;

#if TRACE
#define trace_set(x) (TRACE_RUNTIME = x)
void __trace_ascend();
void __trace_descend();
int trace_depth_get();

#define trace_ascend() __trace_ascend();
#define trace_descend() __trace_descend();

#define trace_printf(fmt, ...)                                                 \
  do {                                                                         \
    if (TRACE_RUNTIME) {                                                       \
      for (int i = 0; i < trace_depth_get(); ++i) {                            \
        printf("\t");                                                          \
      }                                                                        \
      printf("|> ");                                                           \
      printf(fmt, ##__VA_ARGS__);                                              \
    }                                                                          \
  } while (0)

#define trace_fprintf(stream, fmt, ...)                                        \
  do {                                                                         \
    if (TRACE_RUNTIME) {                                                       \
      for (int i = 0; i < trace_depth_get(); ++i) {                            \
        fprintf(stream, "\t");                                                 \
      }                                                                        \
      fprintf(stream, "|> ");                                                  \
      fprintf(stream, fmt, ##__VA_ARGS__);                                     \
    }                                                                          \
  } while (0)

#define trace_printf_ascend(fmt, ...)                                          \
  {                                                                            \
    trace_ascend();                                                            \
    trace_printf(fmt, ##__VA_ARGS__);                                          \
  }

#define trace_fprintf_ascend(stream, fmt, ...)                                 \
  {                                                                            \
    trace_ascend();                                                            \
    trace_fprintf(stream, fmt, ##__VA_ARGS__);                                 \
  }
#else
#define trace_set(x)
#define trace_printf(fmt, ...)
#define trace_fprintf(stream, fmt, ...)
#define trace_printf_ascend(fmt, ...)
#define trace_fprintf_ascend(stream, fmt, ...)
#define trace_ascend()
#define trace_descend()
#endif

#include "private/linkage_post.h"
#endif //_TRACE_H_
