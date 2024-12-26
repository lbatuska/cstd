#include "vector.h"
#include "trace.h"

static const uint32 grow_factor = 2;

void __vector_expand_if_full(struct vector *vector) {
  if (vector->cap == vector->size) {
    trace_printf_ascend("__vector_expand_if_full() -> Expanded!\n");
    vector->cap = vector->cap * grow_factor;
    vector->data = realloc(vector->data, vector->cap * vector->elem_size);
  } else {
    trace_printf_ascend("__vector_expand_if_full() -> Not full\n");
  }
  trace_descend();
}
