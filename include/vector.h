#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "compile.h"
#include "def.h"
#include "trace.h"
#include "wordsize.h"
#include <stdlib.h>
#include <string.h>

#include "private/linkage_pre.h"

struct vector {
  sizet cap;
  sizet size;
  const sizet elem_size;
  void *data; // should be allocated as cap * elem_size
};

#define VECTOR_INIT(name, capacity, element)                                   \
  trace_printf("VECTOR_INIT(%s, %s, %s)\n", #name, #capacity, #element);       \
  struct vector name = {.cap = capacity,                                       \
                        .size = 0,                                             \
                        .data = malloc(sizeof(element) * capacity),            \
                        .elem_size = sizeof(element)}

void __vector_expand_if_full(struct vector *vector);

#define vector_push_back(vector, element)                                      \
  {                                                                            \
    trace_printf_ascend("vector_push_back(%s, %s)\n", #vector, #element);      \
    __vector_expand_if_full(&vector);                                          \
    void *ptr = vector.data + (vector.size * vector.elem_size);                \
    memcpy(ptr, &element, vector.elem_size);                                   \
    vector.size++;                                                             \
    trace_descend();                                                           \
  }

#define vector_emplace_back(vector, element_type, ...)                         \
  {                                                                            \
    trace_printf_ascend("vector_emplace_back(%s, %s, ...)\n", #vector,         \
                        #element_type);                                        \
    __vector_expand_if_full(&vector);                                          \
    *(element_type *)(vector.data + (vector.size * vector.elem_size)) =        \
        (element_type){__VA_ARGS__};                                           \
    vector.size++;                                                             \
    trace_descend();                                                           \
  }

#define vector_push_front(vector, element)                                     \
  {                                                                            \
    trace_printf_ascend(                                                       \
        "vector_push_front(%s, element) -> Moving %zu bytes by %zu bytes\n",   \
        #vector, vector.size *vector.elem_size, vector.elem_size);             \
    __vector_expand_if_full(&vector);                                          \
    memmove(vector.data + vector.elem_size, vector.data,                       \
            vector.size * vector.elem_size);                                   \
    memcpy(vector.data, &element, vector.elem_size);                           \
    vector.size++;                                                             \
    trace_descend();                                                           \
  }

#define vector_for_each(pos, vector)                                           \
  trace_printf("vector_for_each(pos, %s)\n", #vector);                         \
  for (pos = vector.data;                                                      \
       pos != vector.data + (vector.size * vector.elem_size); pos++)

#if WORDSIZE >= 32
static inline void *vector_at(struct vector vec, sizet elem) {
  trace_printf("vector_at(vec, %lu)\n", elem);
  if (elem >= vec.size)
    return NULL;
  return (vec.data + (vec.elem_size * elem));
}
#else
// Probably we don't want to pass around a 32bit struct if word size is smaller
#define vector_at(vec, elem)                                                   \
  {(elem >= vec.size) ? NULL : (vec.data + (vec.elem_size * elem))};           \
  trace_printf("vector_at(vec, %lu)\n", elem);

#endif

#define vector_pop(vector, elem)                                               \
  {                                                                            \
    trace_printf("vector_pop(vector, %lu)\n", elem);                           \
    elem = *(typeof(elem) *)vector_at(vector, vector.size - 1);                \
    vector.size--;                                                             \
  }

#include "private/linkage_post.h"
#endif //_VECTOR_H_
