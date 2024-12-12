#ifndef _VECTOR_H
#define _VECTOR_H
#include "compile.h"
#include "wordsize.h"
#include <stdlib.h>
#include <string.h>

#include "private/linkage_pre.h"

static const int grow_factor = 2;

struct vector {
  size_t cap;
  size_t size;
  const size_t elem_size;
  void *data; // should be allocated as cap * elem_size
};

#define VECTOR_INIT(name, capacity, element)                                   \
  struct vector name = {.cap = capacity,                                       \
                        .size = 0,                                             \
                        .data = malloc(sizeof(element) * capacity),            \
                        .elem_size = sizeof(element)}

#define __vector_expand_if_full(vector)                                        \
  {                                                                            \
    if (vector.cap == vector.size) {                                           \
      vector.cap = vector.cap * grow_factor;                                   \
      vector.data = realloc(vector.data, vector.cap * vector.elem_size);       \
    }                                                                          \
  }

#define vector_push_back(vector, element)                                      \
  {                                                                            \
    __vector_expand_if_full(vector);                                           \
    void *ptr = vector.data + (vector.size * vector.elem_size);                \
    memcpy(ptr, &element, vector.elem_size);                                   \
    vector.size++;                                                             \
  }

#define vector_push_front(vector, element)                                     \
  {                                                                            \
    __vector_expand_if_full(vector);                                           \
    memmove(vector.data + vector.elem_size, vector.data,                       \
            vector.size * vector.elem_size);                                   \
    memcpy(vector.data, &element, vector.elem_size);                           \
    vector.size++;                                                             \
  }

#define vector_for_each(pos, vector)                                           \
  for (pos = vector.data;                                                      \
       pos != vector.data + (vector.size * vector.elem_size); pos++)

#if WORDSIZE >= 32

static inline void *vector_at(struct vector vec, size_t elem) {
  if (elem >= vec.size)
    return NULL;
  return (vec.data + (vec.elem_size * elem));
}
#else
// Probably we don't want to pass around a 32bit struct if word size is smaller
#define vector_at(vec, elem)                                                   \
  {(elem >= vec.size) ? NULL : (vec.data + (vec.elem_size * elem))}

#endif

#define vector_pop(vector, elem)                                               \
  {                                                                            \
    elem = *(typeof(elem) *)vector_at(vector, vector.size - 1);                \
    vector.size--;                                                             \
  }

#include "private/linkage_post.h"
#endif //_VECTOR_H
