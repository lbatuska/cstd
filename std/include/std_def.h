#ifndef STD_DEF_H_INCLUDED
#define STD_DEF_H_INCLUDED

#include <stdlib.h> // size_t
#include <stddef.h> // ptrdiff_t
//#include <string.h>

typedef int std_bool;
#define false (0)
#define true (!0)

typedef ptrdiff_t difference_type;
typedef void * value_type;
typedef void ** pointer;
typedef void const ** const_pointer;
typedef size_t size_type;

typedef int (* COMPARER)(value_type , value_type); // (a,b) => a-b

#endif // STD_DEF_H_INCLUDED
