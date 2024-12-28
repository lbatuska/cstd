#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "compile.h"
#include "def.h"
#include "trace.h"
#include "wordsize.h"
#include <stdint.h>
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
  struct vector name = {                                                       \
      .cap = (capacity ? capacity : 1),                                        \
      .size = 0,                                                               \
      .data = malloc(sizeof(element) * (capacity ? capacity : 1)),             \
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
static inline void *vector_at(struct vector vec, sizet index) {
  trace_printf("vector_at(vec, %lu)\n", index);
  if (index >= vec.size)
    return NULL;
  return (vec.data + (vec.elem_size * index));
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

static inline void vector_erase(struct vector *vec, sizet index) {
  if (index >= vec->size) {
    trace_printf("vector_erase(vector, %lu) -> Nothing to do!\n", index);
    goto end;
  }
  trace_printf("vector_erase(vector, %lu)\n", index);
  if (index == vec->size - 1) {
    vec->size--;
    goto end;
  }
  // dest (base + index*elem size)
  // src (base + (index+1) * elem size)
  // , src, size -> size-index * elem_size
  //
  memmove(vec->data + (index * vec->elem_size),
          vec->data + ((index + 1) * vec->elem_size),
          (vec->size - (index + 1)) * vec->elem_size);
  vec->size--;
end:
  trace_descend();
  return;
}

// First element
static inline void *vector_front(struct vector *vec) { return vec->data; }

// Last element
static inline void *vector_back(struct vector *vec) {
  return (vec->data + ((vec->size - 1) * vec->elem_size));
}

// Next element
static inline void *vector_next(struct vector *vec, void *elem) {
  return (elem + vec->elem_size);
}

// Previous
static inline void *vector_prev(struct vector *vec, void *elem) {
  return (elem - vec->elem_size);
}

static inline int8 vector_valid_ptr(struct vector *vec, void *ptr) {
  if (ptr < vec->data)
    goto no;
  if (ptr > (vec->data + (vec->size - 1) * vec->elem_size))
    goto no;
  // If in bounds memory has to be divisable by elem_size
  if ((uintptrt)(ptr - vec->data) % vec->elem_size != 0)
    goto no;

  return 1;
// Not valid
no:
  return 0;
}

#include "private/linkage_post.h"
#endif //_VECTOR_H_
