/** \file TQueue.c
 *  \brief Implementace API pro typ fronta (realizace pomocí kruhového pole)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TQueue.c 2615 2024-02-16 15:36:07Z petyovsky $
 */

#include <assert.h>
#include "TQueue.h"

void queue_init(struct TQueue *aQueue)
	{
	if(aQueue != NULL)
		aQueue->iFrontPos = aQueue->iBackPos = 0;
	return false;
	}

bool queue_is_empty(const struct TQueue *aQueue)
	{
	if(!aQueue)
		return true;
	assert((aQueue->iFrontPos < QUEUE_MAXCOUNT));
	assert((aQueue->iBackPos < QUEUE_MAXCOUNT));
	return (aQueue->iFrontPos == aQueue->iBackPos);
	}

bool /* TQueueIterator */ queue_front(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if(queue_is_empty(aQueue))
		return false;
	if(!aValue)
		return false;
	*aValue = aQueue->iValues[aQueue->iFrontPos];
	return true;
	}

bool /* TQueueIterator */ queue_back(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if(queue_is_empty(aQueue))
		return false;
	if(!aValue)
		return false;
	if(aQueue->iBackPos == 0)
		*aValue = aQueue->iValues[QUEUE_MAXCOUNT-1];
	else
		*aValue = aQueue->iValues[aQueue->iBackPos - 1];
	return true;
	}

bool queue_push(struct TQueue *aQueue, TQueueElement aValue)
	{
	if(!aQueue)
		return false;
	size_t nextBackPos = (aQueue->iBackPos + 1) % QUEUE_MAXCOUNT;
	if(nextBackPos == aQueue->iFrontPos)
		return false;
	aQueue->iValues[aQueue->iBackPos] = aValue;
	aQueue->iBackPos = nextBackPos;
	return true;
	}

bool queue_pop(struct TQueue *aQueue)
	{
	if(queue_is_empty(aQueue))
		return false;
	aQueue->iFrontPos = (aQueue->iFrontPos + 1) % QUEUE_MAXCOUNT;
	return true;
	}

void queue_destroy(struct TQueue *aQueue)
	{
	queue_init(aQueue);
	}

struct TQueueIterator queue_iterator_begin(const struct TQueue *aQueue)
	{
	if(queue_is_empty(aQueue))
		return (struct TQueueIterator) { .iQueue = NULL, .iPos = 0 };
	return (struct TQueueIterator) { .iQueue = aQueue, .iPos = aQueue->iFrontPos };
	}

bool queue_iterator_is_valid(const struct TQueueIterator *aIter)
	{
	if(queue_is_empty(aIter->iQueue))
		return false;
	if(!aIter)
		return false;
	return (aIter->iPos != aIter->iQueue->iBackPos);
	}

bool queue_iterator_to_next(struct TQueueIterator *aIter)
	{
	if(!aIter)
		return false;
	if(!aIter->iQueue)
		return false;
	if(aIter->iQueue->iFrontPos == aIter->iQueue->iBackPos)
		return false;
	aIter->iPos = (aIter->iPos + 1) % QUEUE_MAXCOUNT;
	if(aIter->iPos != aIter->iQueue->iBackPos)
		return true;
	aIter->iQueue = NULL;
	aIter->iPos = 0;
	return false;
	}

TQueueElement queue_iterator_value(const struct TQueueIterator *aIter)
	{
	if(queue_iterator_is_valid(aIter))
		return aIter->iQueue->iValues[aIter->iPos];
	return (TQueueElement) { 0 };
	}

bool queue_iterator_set_value(const struct TQueueIterator *aIter, TQueueElement aValue)
	{
	if(queue_iterator_is_valid(aIter))
		{
		((struct TQueue *)aIter->iQueue)->iValues[aIter->iPos] = aValue;
		return true;
		}
	return false;
	}
