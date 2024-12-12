#ifndef _CONTAINER_OF_H_
#define _CONTAINER_OF_H_
#include "config.h"

#include "compile.h"

#include "private/linkage_pre.h"

#include <stddef.h>

#define container_of(member_ptr, container_type, container_member)             \
  ({                                                                           \
    static_assert(                                                             \
        same_type(*(member_ptr), ((container_type *)0)->container_member) ||   \
            same_type(*(member_ptr), void),                                    \
        "pointer type mismatch in container_of()");                            \
    ((container_type *)(((void *)(member_ptr)) -                               \
                        offsetof(container_type, container_member)));          \
  })

// A very simplistic implementation with no type safety
// #define c_of(ptr, container, member) \
//   ((container *)((void *)(ptr) - offsetof(container, member)))

#include "private/linkage_post.h"
#endif
