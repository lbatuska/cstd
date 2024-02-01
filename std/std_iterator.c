 #include "std_iterator.h"

value_type std_iter_at(std_iterator it, difference_type n)
{
	if (STD_IS_RANDOM_ACCESS_ITERATOR(it))
		return (it)._pft->std_iter_at(it,n);
	return NULL;
};

void std_iter_advance(std_piterator pit, difference_type n)
{
	if(STD_IS_RANDOM_ACCESS_ITERATOR(*pit))
        if(n >= 0)
            (*pit)._pft->std_iter_next_n(pit, n);
        else
            (*pit)._pft->std_iter_prev_n(pit, n);
	else if(STD_IS_BIDIRECTIONAL_ITERATOR(*pit))
	{
		if(n >= 0)
			while(n --)
                (*pit)._pft->std_iter_next(pit);
		else
			while(n ++)
                (*pit)._pft->std_iter_prev(pit);
	}
	else
		while(n --)
            (*pit)._pft->std_iter_next(pit);
};

// returns the distance between two iterators
difference_type std_iter_distance(std_iterator first, std_iterator last)
{
		if(STD_IS_RANDOM_ACCESS_ITERATOR(first) &&
		STD_IS_RANDOM_ACCESS_ITERATOR(last))
		return (first)._pft->std_iter_distance(first, last);
	else
	{
		difference_type n = 0;
		while(!(first)._pft->std_iter_equal(first, last))
		{
			(first)._pft->std_iter_next(&first);
			++ n;
		}
		return n;
	}
};

value_type std_iterator_referece_get(std_iterator x)
{
    return (x)._pft->std_iter_referece_get(x);
};

value_type std_iterator_referece_assign(std_iterator x, const value_type val)
{
    return (x)._pft->std_iter_referece_assign(x,val);
};

std_bool std_iter_equal(std_iterator x, std_iterator y)
{
    return (x)._pft->std_iter_equal(x,y);
};

std_bool std_iter_less(std_iterator x, std_iterator y)
{
    return (x)._pft->std_iter_less(x,y);
};
