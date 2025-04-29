/** \file TSet.c
 *  \brief Implementace API pro typ Set (realizace množiny pomocí setříděného flexibilního dynamicky alokovaného pole)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TSet.c 2703 2024-04-12 15:38:04Z petyovsky $
 */

#include "TSet.h"
#include "check.h"

void set_init(struct TSet *aSet)
	{
	if(aSet)
		*aSet = (struct TSet) { .iSize = 0, .iFlexArray = NULL };
	}

size_t set_size(const struct TSet *aSet)
	{
	if(aSet)
		return aSet->iSize;
	return 0;
	}

bool set_insert(struct TSet *aSet, TSetElement aValue)
	{
	if(!aSet)
		return false;

	if(!set_flex_array_insert(&aSet->iFlexArray, aValue, aSet->iSize))
		return false;

	++aSet->iSize;
	return true;
	}

bool set_erase(struct TSet *aSet, TSetElement aValue)
	{
	if(!set_size(aSet))
		return false;

	if(!set_flex_array_erase(&aSet->iFlexArray, aValue, aSet->iSize))
		return false;

	--aSet->iSize;
	return true;

	}

bool set_is_element_of(const struct TSet *aSet, TSetElement aValue)
	{
	if(!set_size(aSet))
		return false;

	size_t pos = 0;
	return set_flex_array_search(aSet->iFlexArray, aValue, &pos, aSet->iSize) == 0;
	}

struct TSetIterator set_find(const struct TSet *aSet, TSetElement aValue)
	{
	if(set_size(aSet))
		{
		size_t pos = 0;
		if(set_flex_array_search(aSet->iFlexArray, aValue, &pos, aSet->iSize) == 0)
			return (struct TSetIterator) { .iSet = aSet, .iPos = pos };	// success
		}

	return (struct TSetIterator) { .iSet = NULL, .iPos = 0 };	// fail
	}

void set_destroy(struct TSet *aSet)
	{
	if(!aSet)
		return;

	set_flex_array_destroy(aSet->iFlexArray);
	*aSet = (struct TSet) { .iSize = 0, .iFlexArray = NULL };
	}

struct TSetIterator set_iterator_begin(const struct TSet *aSet)
	{
	if(aSet)
		return (struct TSetIterator) { .iSet = aSet, .iPos = set_flex_array_begin_pos(aSet->iFlexArray) };

	return (struct TSetIterator) { .iSet = NULL, .iPos = 0 };
	}

bool set_iterator_is_valid(const struct TSetIterator *aIter)
	{
	if(aIter)
		if(aIter->iSet)
			return set_flex_array_is_valid_pos(aIter->iSet->iFlexArray, aIter->iPos, aIter->iSet->iSize);

	return false;
	}

bool set_iterator_to_next(struct TSetIterator *aIter)
	{
	bool valid = set_iterator_is_valid(aIter);
	if(valid)
		{
		aIter->iPos = set_flex_array_next_pos(aIter->iSet->iFlexArray, aIter->iPos);
		valid = set_flex_array_is_valid_pos(aIter->iSet->iFlexArray, aIter->iPos, aIter->iSet->iSize);
		}

	return valid;
	}

TSetElement set_iterator_value(const struct TSetIterator *aIter)
	{
	if(set_iterator_is_valid(aIter))
		return set_flex_array_value_at_pos(aIter->iSet->iFlexArray, aIter->iPos);

	return (TSetElement) { 0 };
	}
/*
bool set_intersection(struct TSet* aNewSet, const struct TSet* aSetA, const struct TSet* aSetB)
{
	if ((aNewSet && !aSetA && !aSetB) || (!aNewSet && aSetA && !aSetB) || (!aNewSet && !aSetA && aSetB))
		return false;
	if (!aNewSet && !aSetA && !aSetB)
		return true;

	if (aNewSet->iFlexArray)
		return false;

	size_t ssize = aSetA->iSize;

	if (aSetA->iSize > aSetB->iSize)
		ssize = aSetB->iSize;


	aNewSet->iFlexArray = malloc(ssize * sizeof(TSetElement));

	if (!aNewSet)
		return false;

	struct TSetIterator itA = set_iterator_begin(aSetA);
	struct TSetIterator itB = set_iterator_begin(aSetB);
	size_t i = 0;

	while (set_iterator_is_valid(&itA) && set_iterator_is_valid(&itB))
	{
		TSetElement a = set_iterator_value(&itA);
		TSetElement b = set_iterator_value(&itB);
		if (set_element_comparator(&a, &b) > 0)
		{
			set_iterator_to_next(&itB);
		}
		else if (set_element_comparator(&a, &b) < 0)
		{
			set_iterator_to_next(&itA);
		}
		else
		{
			set_flex_array_insert(&(aNewSet->iFlexArray), set_iterator_value(&itA), aNewSet->iSize);
			aNewSet->iSize++;
			//set_iterator_value(&itC) = set_iterator_value(&itA);
			set_iterator_to_next(&itA);
			set_iterator_to_next(&itB);
		}
	}
	if (aNewSet->iSize == 0)
	{
		free(aNewSet);
	}

	return true;

}*/

/*

bool set_intersection(struct TSet* aNewSet, const struct TSet* aLeftSet, const struct TSet* aRightSet) 
	{
	
	if (!aNewSet && !aLeftSet && !aRightSet)
		return true;
	else if (!aNewSet || !aLeftSet || !aRightSet || !set_is_empty(aNewSet))
		return false;
		
	size_t New_Size = (aLeftSet->iSize < aRightSet->iSize) ? (aLeftSet->iSize) : (aRightSet->iSize);
	
	//aNewSet->iFlexArray = malloc(New_Size * sizeof(TSetElement));
	//struct TSetSortedFlexArray* act = malloc(sizeof(struct TSetElement*) *New_Size);
//	struct TSet * act = malloc(sizeof(struct TSet) * New_Size);
	//mozna chyba :(

	//if (!aNewSet->iFlexArray)
	//	return false;
	//	
	size_t k = 0;

	//while (i < aLeftSet->iSize && j < aRightSet->iSize) {}
	for (size_t i = 0; i < aLeftSet->iSize; i++)
		for (size_t j = 0; j < aRightSet->iSize; ++j)
		{
			//const TSetElement* a = set_flex_array_value_at_pos(aLeftSet, i), b = set_flex_array_value_at_pos(aRightSet, j);
				//printf("%d\n", a);
			TSetElement a = set_flex_array_value_at_pos(aLeftSet->iFlexArray, i), b = set_flex_array_value_at_pos(aRightSet->iFlexArray, j);
			printf("%d %d %zu\n", a, b,aNewSet->iSize);
			if (set_element_comparator(&a,&b) == 0)
			{
				if (!set_insert(aNewSet,a))
					return false;
			}
		}
	if (set_is_empty(aNewSet->iFlexArray))
	{
		//printf("spadne to sem");
		free(aNewSet->iFlexArray);
		return false;
	}
	return true;
	}
*/
bool set_equal(struct TSet* aLeft, struct TSet* aRight) {
	if (!aLeft && !aRight)
		return true;
	if (!aLeft || !aRight)
		return false;

	if (aLeft->iSize != aRight->iSize)
		return false;

	// OPTION 1
#if 0 // staci zmenit nulu na jednicku, protoze jsme v kodu kde pole je sorted tak staci najit prvni prvky kde se to lisi a pak break
	for (size_t k = 0; k < aRight->iSize; k++)
	{
		TSetElement a = set_flex_array_value_at_pos(aLeft->iFlexArray, k);
		TSetElement b = set_flex_array_value_at_pos(aRight->iFlexArray, k);
		if (set_element_comparator(&a, &b) != 0)
			return false;
	}
#endif
#if 1 // zapomocí funkce set_is element of
	for (size_t i = 0; i < aLeft->iSize; i++)
		if (!set_is_element_of(aRight, set_flex_array_value_at_pos(aLeft->iFlexArray, i)))
			return false;

	return true;
#endif
}