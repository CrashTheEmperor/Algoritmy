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

void insert_sort(struct TVector *aVector)
	{
	if (!aVector)
		return;
	TVectorElement tmp;
	for (size_t i = 0; i < aVector->iSize; i++)
	{
		tmp = vector_value(aVector,i);
		size_t j = i;
		
		for (; j ; --j)
		{
			if (vector_compare_position_value(aVector, j-1, tmp) < 0)
				break;
			
			vector_move_positions(aVector, j, aVector, j-1);
			
		}
		vector_set_value(aVector, j, tmp);
	}
	
	
	
	
	
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void select_sort(struct TVector *aVector)
	{
	if (!aVector)
		return;
	for (size_t i = 0; i < aVector->iSize; i++)
	{
		size_t minPos = i;
		size_t j = i;
		for (; j < aVector->iSize; j++)
		{
			if (vector_compare_positions(aVector, minPos, aVector, j) > 0)
				minPos = j;
		}
		vector_swap_positions(aVector, i, aVector, minPos);
	}
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void bubble_sort(struct TVector *aVector)
	{
	if (!aVector)
		return;

	for (size_t i = 0; i < aVector->iSize ; i++)
	{
		for (size_t j = 0; j < aVector->iSize-i-1; j++)
		{
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0)
				vector_swap_positions(aVector, j + 1, aVector, j);
		}
	
	}
	
	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}

void bubble_sort_optimized(struct TVector *aVector)
	{
	if (aVector == NULL)
		return;

	bool again = true; // Indikace jestli došlo ke swapu nebo ne

	for (size_t i = 0; i < (aVector->iSize - 1) && again == true; i++) // i je poceft prvku setridene oblasti // setrizená oblast je vlevo
	{
		// vector_for_each(vector_iterator_begin(aVector), print_element);
		// putchar('\n'); 
		again = false;

		for (size_t j = 0; j < aVector->iSize - i - 1; j++) // Prochází nesetridene oblasti (nesetridena oblast se postupne zkracuje o 1 (-i))
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0) // Hodnota je větší
			{
				vector_swap_positions(aVector, j, aVector, j + 1);
				again = true;
			}
	}
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

		for (size_t j = 0; j < maxpos; j++) // Prochází nesetridene oblasti (nesetridena oblast se postupne zkracuje o 1 (-i))
		{
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0) // Hodnota je větší
			{
				vector_swap_positions(aVector, j, aVector, j + 1);
				swap_lastpos = j;
			}
		}
		maxpos = swap_lastpos;
	}
	}

void shaker_sort(struct TVector *aVector)
	{
	
	if (!aVector)
		return;
	
	size_t MaxPos = aVector->iSize - 1;
	size_t Min_pos = 0;
	size_t Swap_pos = 0;
	
	
	//printf("%zu %zu %zu\n", MaxPos, MinPos, SwapPos);
	while(Min_pos < MaxPos){
		
		Min_pos = Swap_pos;
		
		for (size_t j = Min_pos; j < MaxPos; j++)
		{
			if (vector_compare_positions(aVector, j, aVector, j + 1) > 0)
			{
				vector_swap_positions(aVector, j + 1, aVector, j);
				Swap_pos = j;
			}
		}
		MaxPos = Swap_pos;
		
		for (size_t j = MaxPos; j > Min_pos; j--)
		{
			if (vector_compare_positions(aVector, j, aVector, j - 1) < 0)
			{
				vector_swap_positions(aVector, j , aVector, j - 1);
				Swap_pos = j;
			}
		}
	
	}






	//vector_for_each(vector_iterator_begin(aVector), print_element);
	//putchar('\n');
	}
