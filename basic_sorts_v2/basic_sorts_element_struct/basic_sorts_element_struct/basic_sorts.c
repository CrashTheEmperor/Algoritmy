/** \file basic_sorts.c
 *  \brief Implementace API přímých metod třídění
 *  \author Petyovský
 *  \version 2025
 *  $Id: basic_sorts.c 2996 2025-03-13 16:22:55Z petyovsky $
 */

#include "basic_sorts.h"

void print_element(const struct TVectorIterator *aIter)
	{
	if(!vector_element_store_file(vector_iterator_value(aIter), stdout))
		fprintf(stderr, "Function 'vector_element_store_file()' failed!\n");
	}

void insert_sort(struct TVector *aVector)
	{
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');

	if (aVector == NULL)
		return;

	for (size_t i = 1; i < aVector->iSize; i++)
		{
		// vector_for_each(vector_iterator_begin(aVector), print_element);
		// putchar('\n');

		TVectorElement tmp = vector_value(aVector, i); // vyběr hodnoty a porovnání v nesetrizene oblasti
		size_t j = i;
		for (; j > 0; --j) // Iterace nesetridenou oblasti <- |
			{
			if (vector_compare_position_value(aVector, j - 1, tmp) <= 0)
				break;
			vector_move_positions(aVector, j, aVector, j - 1);
			}
		vector_set_value(aVector, j, tmp);
		}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void select_sort(struct TVector *aVector)
	{
	if (aVector == NULL)
		return;

	for (size_t i = 0; i < aVector->iSize - 1; i++) // ukazatel na prvni prvek nesetridene oblasti
		{
		 //vector_for_each(vector_iterator_begin(aVector), print_element);
		 //putchar('\n');
		size_t minPos = i;

		for (size_t j = i + 1; j < aVector->iSize; j++) // prochazeni nesetridene oblasti (od druheho prvku po poslední)
			{
			if (vector_compare_positions(aVector, j, aVector, minPos) < 0) // Nejmenší hodnota
				minPos = j;
			}
		vector_swap_positions(aVector, i, aVector, minPos); // Přehoď hodnotu min na začátek
		}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void bubble_sort(struct TVector *aVector)
	{
	if (aVector == NULL)
		return;

	for (size_t i = 0; i < (aVector->iSize - 1); i++) // i - pocet prvku setridene oblasti // setrizená oblast je vlevo
		{
		 //vector_for_each(vector_iterator_begin(aVector), print_element);
		 //putchar('\n');

		for (size_t j = 0; j < aVector->iSize - i - 1; j++) // Iterace nesetridene oblasti (nesetridena oblast se zkracuje (-i))
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0) // Hodnota je větší
				vector_swap_positions(aVector, j, aVector, j + 1);
		}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void bubble_sort_optimized(struct TVector *aVector)
	{
	if (aVector == NULL)
		return;

	bool again = true; // swap ??

	for (size_t i = 0; i < (aVector->iSize - 1) && again == true; i++) // i - pocet prvku setridene oblasti // setrizená oblast je vlevo
		{
		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n'); 
		again = false;

		for (size_t j = 0; j < aVector->iSize - i - 1; j++) // Iterace nesetridene oblasti (nesetridena oblast se zkracuje (-i))
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0) // Hodnota je větší
				{
				vector_swap_positions(aVector, j, aVector, j + 1);
				again = true;
				}
		}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void bubble_sort_optimized2(struct TVector *aVector)
	{
	if (aVector == NULL)
		return;

	size_t maxpos = aVector->iSize - 1;

	while (maxpos > 0)
		{
		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n');

		size_t swap_lastpos = 0;

		for (size_t j = 0; j < maxpos; j++) // Iterace nesetridene oblasti (nesetridena oblast se zkracuje (-i))
			{
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0) // Hodnota je větší
				{
				vector_swap_positions(aVector, j, aVector, j + 1);
				swap_lastpos = j;
				}
			}
		maxpos = swap_lastpos;
		}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void shaker_sort(struct TVector *aVector)
	{
	if (aVector == NULL)
		return;

	size_t maxpos = aVector->iSize - 1;
	size_t minpos = 0;
	size_t swap_lastpos = 0;

	while (minpos < maxpos) // Musím dojet do středu
		{
		//vector_for_each(vector_iterator_begin(aVector), print_element);
		//putchar('\n');

		// zleva do prava
		for (size_t j = minpos; j < maxpos; j++) // Iterace nesetridene oblasti (nesetridena oblast se zkracuje (-i))
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0) // Hodnota je větší
				{
				vector_swap_positions(aVector, j, aVector, j + 1);
				swap_lastpos = j;
				}
		maxpos = swap_lastpos;

		// zprava do leva
		for (size_t j = maxpos; j > minpos; j--) // Iterace nesetridene oblasti (nesetridena oblast se zkracuje (-i))
			if (vector_compare_positions(aVector, j - 1, aVector, j) > 0) // Hodnota je větší
				{
				vector_swap_positions(aVector, j - 1, aVector, j);
				swap_lastpos = j;
				}
		minpos = swap_lastpos;
		}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}
