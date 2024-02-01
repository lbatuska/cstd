#ifndef STD_ITERATOR_H_INCLUDED
#define STD_ITERATOR_H_INCLUDED
#include "std_def.h"

// ITERATOR and POINTER DECLARATION
typedef struct std_iterator std_iterator, * std_piterator;

// CONSTANT ITERATOR DECLARATION
typedef const std_iterator std_const_iterator;

// ITERATOR FUNCTION TABLE and POINTER DECLARATION
typedef struct std_iterator_ft std_iterator_ft, * std_iterator_pft;

// ITERATOR DEFINITON
struct std_iterator
{
	std_iterator_pft _pft;
	value_type _i;
};

// ITERATOR FUNCTION TABLE DEFINITON
struct std_iterator_ft
{

    // returns (iterator + n)-th value_type value
    value_type (*std_iter_at)(std_iterator thiz, difference_type n);

    // advances / increments the iterator
    std_iterator (*std_iter_next)(std_piterator pit);
    // retreats / decreases the iterator
    std_iterator (*std_iter_prev)(std_piterator pit);

    // advances / increments the iterator by n
    std_iterator (*std_iter_next_n)(std_piterator pit, difference_type n);
    // retreats / decreases the iterator by n
    std_iterator (*std_iter_prev_n)(std_piterator pit, difference_type n);

    // returns the distance between two iterators
    difference_type (*std_iter_distance)(std_iterator first, std_iterator last);

    // returns the value_type value in the underlying data of the iterator
    value_type (*std_iter_referece_get)(std_iterator it);
    // assigns value_type value of the underlying data
    value_type (*std_iter_referece_assign)(std_iterator it, const value_type val);

    // checks if the 2 iterators equal (compare function table and underlying data pointer)
    std_bool (*std_iter_equal)(std_iterator first, std_iterator second);
    // makes sense for contiguous data, usually returns if the underlying pointer points to a smaller address (or bigger in case of reverse iterators)
    std_bool (*std_iter_less)(std_iterator first, std_iterator second);
};


// REVERSE ITERATOR TESTING
// ITERATOR and POINTER DECLARATION
typedef struct std_iterator std_reverse_iterator, * std_reverse_piterator;

// CONSTANT ITERATOR DECLARATION
typedef const std_reverse_iterator std_const_reverse_iterator;

// ITERATOR FUNCTION TABLE and POINTER DECLARATION
typedef struct std_iterator_ft std_reverse_iterator_ft, * std_reverse_iterator_pft;
// REVERSE ITERATOR TESTING


// COMMON OPERATION ON ALL ITERATORS
// returns (iterator + n)-th value_type value
value_type std_iter_at(std_iterator it, difference_type n);

// advances an iterator by given distance (in place)
void std_iter_advance(std_piterator pit, difference_type n);

// returns the distance between two iterators
difference_type std_iter_distance(std_iterator first, std_iterator last);

// returns the value_type value in the underlying data of the iterator
value_type std_iterator_referece_get(std_iterator it);
// assigns value_type value of the underlying data
value_type std_iterator_referece_assign(std_iterator it, const value_type val);

// checks if the 2 iterators equal (compare function table and underlying data pointer)
std_bool std_iter_equal(std_iterator first, std_iterator second);
// makes sense for contiguous data, usually returns if the underlying pointer points to a smaller address (or bigger in case of reverse iterators)
std_bool std_iter_less(std_iterator first, std_iterator second);
// COMMON OPERATION ON ALL ITERATORS

// ITERATOR TYPE HELPERS
#define STD_IS_FORWARD_ITERATOR(X)           ((X)._pft->std_iter_next)
#define STD_IS_REVERSE_ITERATOR(X)           ((X)._pft->std_iter_prev)
#define STD_IS_BIDIRECTIONAL_ITERATOR(X)     ((X)._pft->std_iter_next && (X)._pft->std_iter_prev)
#define STD_IS_RANDOM_ACCESS_ITERATOR(X)     ((X)._pft->std_iter_at && (X)._pft->std_iter_distance)
#define STD_IS_INPUT_ITERATOR(X)             ((X)._pft->std_iter_referece_get)
#define STD_IS_OUTPUT_ITERATOR(X)            ((X)._pft->std_iter_referece_assign)
// ITERATOR TYPE HELPERS

#endif // STD_ITERATOR_H_INCLUDED
