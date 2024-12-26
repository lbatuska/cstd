#ifndef _TRACE_H_
#define _TRACE_H_
#include "config.h"
#include <stdio.h>

#include "private/linkage_pre.h"

#if TRACE
// We place the trace_depth definition inside the if because it was not meant to
// be manipulated from external code
extern int trace_depth;
#define trace_ascend()                                                         \
  do {                                                                         \
    trace_depth++;                                                             \
  } while (0)

#define trace_descend()                                                        \
  do {                                                                         \
    trace_depth--;                                                             \
  } while (0)

#define trace_printf(fmt, ...)                                                 \
  do {                                                                         \
    for (int i = 0; i < trace_depth; ++i) {                                    \
      printf("\t");                                                            \
    }                                                                          \
    printf("|> ");                                                             \
    printf(fmt, ##__VA_ARGS__);                                                \
  } while (0)

#define trace_fprintf(stream, fmt, ...)                                        \
  do {                                                                         \
    for (int i = 0; i < trace_depth; ++i) {                                    \
      fprintf(stream, "\t");                                                   \
    }                                                                          \
    fprintf(stream, "|> ");                                                    \
    fprintf(stream, fmt, ##__VA_ARGS__);                                       \
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
#define trace_printf(fmt, ...)
#define trace_fprintf(stream, fmt, ...)
#define trace_printf_ascend(fmt, ...)
#define trace_fprintf_ascend(stream, fmt, ...)
#define trace_ascend()
#define trace_descend()
#endif

#include "private/linkage_post.h"
#endif //_TRACE_H_
