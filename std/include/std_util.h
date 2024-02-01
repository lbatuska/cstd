#ifndef STD_UTIL_H_INCLUDED
#define STD_UTIL_H_INCLUDED
#include "std_def.h"

_Static_assert(_Generic(0, default: 1), "_Generic is required to use this feature");

#define typename(x) _Generic((x),        /* Get the name of a type */             \
                                                                                  \
        COMPARER: "COMPARER", std_bool: "std_bool", \
        difference_type: "difference_type", pointer: "pointer", \
        const_pointer: "const_pointer",value_type:"value_type", \
        size_type:"size_type", \
\
default: "other")


// casts X into Y* then dereferences it to Y
#define cast_and_dereference(X,Y) *(Y*)X

#endif // STD_UTIL_H_INCLUDED
