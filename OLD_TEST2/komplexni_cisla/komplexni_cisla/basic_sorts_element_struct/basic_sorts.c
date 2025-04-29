/** \file basic_sorts.c
 *  \brief Implementace API přímých metod třídění
 *  \author Petyovský
 *  \version 2024
 *  $Id: basic_sorts.c 2631 2024-03-08 16:40:08Z petyovsky $
 */

#include "basic_sorts.h"

void print_element(const struct TVectorIterator *aIter)
	{
	vector_element_store_file(vector_iterator_value(aIter), stdout);
	}

static inline vector_invariant(struct TVector* aVector)
	{
	return !aVector->iValues && !aVector->iSize || aVector->iValues && aVector->iSize;
	}

void insert_sort(struct TVector* aVector)
	{
	assert(vector_invariant(aVector));

	if (!aVector)
		return;

	vector_for_each(vector_iterator_begin(aVector), print_element);
	putchar('\n');

	for (size_t sorted = 1; sorted < aVector->iSize; sorted++)
		{
		const TVectorElement tmp = vector_value(aVector, sorted);
		size_t i = sorted;
		for (; i != 0; i--)
			{
			if (vector_compare_position_value(aVector, i - 1, tmp) <= 0)
				break;
			vector_move_positions(aVector, i, aVector, i - 1);
			}

		vector_set_value(aVector, i, tmp);

		vector_for_each(vector_iterator_begin(aVector), print_element);
		putchar('\n');
		}
	}

void select_sort(struct TVector* aVector)
	{
	assert(vector_invariant(aVector));

	if (vector_size(aVector) < 2)
		return;

	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');

	for (size_t sorted = 0; sorted < aVector->iSize - 1; sorted++)
		{
		size_t min_pos = sorted;
		for (size_t i = sorted + 1; i < aVector->iSize; i++)
			if (vector_compare_positions(aVector, min_pos, aVector, i) == 1)
				min_pos = i;

		vector_swap_positions(aVector, sorted, aVector, min_pos);

		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n');
		}
	}

void bubble_sort(struct TVector* aVector)
	{
	assert(vector_invariant(aVector));

	if (vector_size(aVector) < 2)
		return;

	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');

	for (size_t unsorted = aVector->iSize - 1; unsorted > 0; unsorted--)
		{
		for (size_t i = 0; i < unsorted; i++)
			if (vector_compare_positions(aVector, i, aVector, i + 1) == 1)
				vector_swap_positions(aVector, i, aVector, i + 1);

		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n');
		}
	}

void bubble_sort_optimized(struct TVector* aVector)
	{
	assert(vector_invariant(aVector));

	if (vector_size(aVector) < 2)
		return;

	for (size_t unsorted = aVector->iSize - 1; unsorted > 0; unsorted--)
		{
		bool is_sorted = true;
		for (size_t i = 0; i < unsorted; i++)
			if (vector_compare_positions(aVector, i, aVector, i + 1) == 1)
				{
				vector_swap_positions(aVector, i, aVector, i + 1);
				is_sorted = false;
				}
		if (is_sorted)
			break;
		}
	}

void bubble_sort_optimized2(struct TVector* aVector)
	{
	assert(vector_invariant(aVector));

	if (vector_size(aVector) < 2)
		return;

	for (size_t unsorted = aVector->iSize - 1; unsorted > 0; unsorted--)
		{
		size_t last_swap = 0;
		for (size_t i = 0; i < unsorted; i++)
			if (vector_compare_positions(aVector, i, aVector, i + 1) == 1)
				{
				vector_swap_positions(aVector, i, aVector, i + 1);
				last_swap = i;
				}
		unsorted = last_swap + 1;
		}
	}

void shaker_sort(struct TVector* aVector)
	{
	assert(vector_invariant(aVector));

	if (vector_size(aVector) < 2)
		return;

	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');

	for (size_t unsorted = aVector->iSize - 1, sorted = 0; unsorted > sorted; unsorted--, sorted++)
		{
		size_t last_swap = 0;

		for (size_t i = sorted; i < unsorted; i++)
			if (vector_compare_positions(aVector, i, aVector, i + 1) == 1)
				{
				vector_swap_positions(aVector, i, aVector, i + 1);
				last_swap = i;
				}
		unsorted = last_swap + 1;

		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n');

		for (size_t i = unsorted - 1; i > sorted; i--)
			if (vector_compare_positions(aVector, i - 1, aVector, i) == 1)
				{
				vector_swap_positions(aVector, i - 1, aVector, i);
				last_swap = i;
				}
		sorted = last_swap - 1;

		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n');
		}
	}