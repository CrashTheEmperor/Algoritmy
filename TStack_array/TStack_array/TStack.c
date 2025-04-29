/** \file TStack.c
 *  \brief Implementace API pro typ zásobník (realizace pomocí pole)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TStack.c 2592 2024-02-09 17:45:42Z petyovsky $
 */

#include "TStack.h"

void stack_init(struct TStack *aStack)
	{
	if(aStack != NULL)
		aStack->iCount = 0;
	}

bool stack_is_empty(const struct TStack *aStack)
	{
	if(!aStack)
		return true;
	return aStack->iCount == 0;
	}

bool /* TStackIterator */ stack_top(const struct TStack *aStack, TStackElement *aValue)
	{
	if(!aValue)
		return false;
	if(stack_is_empty(aStack))
		return false;
	*aValue = aStack->iValues[aStack->iCount - 1];
	return true;
	}

bool stack_push(struct TStack *aStack, TStackElement aValue)
	{
	if(!aStack)
		return false;
	if(aStack->iCount >= STACK_MAXCOUNT)
		return false;
	aStack->iValues[aStack->iCount++] = aValue;
	return true;
	}

bool stack_pop(struct TStack *aStack)
	{
	if(stack_is_empty(aStack))
		return false;
	--aStack->iCount;
	return true;
	}

void stack_destroy(struct TStack *aStack)
	{
	stack_init(aStack);
	}

struct TStackIterator stack_iterator_begin(const struct TStack *aStack)
	{
	if(stack_is_empty(aStack))
		return (struct TStackIterator) { .iStack = NULL, .iPos = 0 };
	return (struct TStackIterator) { .iStack = aStack, .iPos = aStack->iCount - 1};
	}

bool stack_iterator_is_valid(const struct TStackIterator *aIter)
	{
	if(aIter)
		if(aIter->iStack)
			if(aIter->iPos < aIter->iStack->iCount)
				return true;
	return false;
	}

bool stack_iterator_to_next(struct TStackIterator *aIter)
	{
	if(aIter && aIter->iStack)
		{
		if(aIter->iPos != 0 && aIter->iPos < aIter->iStack->iCount)
			{
			--aIter->iPos;
			return true;
			}
		*aIter = (struct TStackIterator) { .iStack = NULL, .iPos = 0 };
		}
	return false;
	}

TStackElement stack_iterator_value(const struct TStackIterator *aIter)
	{
	if(stack_iterator_is_valid(aIter))
		return aIter->iStack->iValues[aIter->iPos];
	return (TStackElement) { 0 };
	}
