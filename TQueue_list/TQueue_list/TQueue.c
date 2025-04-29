/** \file TQueue.c
 *  \brief Implementace API pro typ fronta (realizace pomocí lineárního jednosměrně vázaného seznamu)
 *  \author Petyovský
 *  \version 2024
 *  $Id: TQueue.c 2616 2024-02-16 15:36:28Z petyovsky $
 */

#include <assert.h>
#include "TQueue.h"

/** \brief Úplná definice privátního typu QueueNode
 *  \details Privátní typ QueueNode (nedostupný mimo funkce ze souboru TQueue.c) reprezentuje typ pro jednotlivé uzly lineárního jednosměrně vázaného seznamu.
 */
struct TQueueNode
	{
	struct TQueueNode *iNext;				///< Ukazatel na následující uzel lineárního jednosměrně vázaného seznamu
	TQueueElement iValue;					///< Element fronty uložený v uzlu lineárního jednosměrně vázaného seznamu
	};

void queue_init(struct TQueue *aQueue)
	{
	if(aQueue)
		{
		*aQueue = (struct TQueue) {.iFront = NULL, .iBack = NULL};
		}
	}

bool queue_is_empty(const struct TQueue* aQueue)
	{
	if(!aQueue)
		return true;
	assert((aQueue->iBack == NULL && aQueue->iFront == NULL) || (aQueue->iBack != NULL && aQueue->iFront != NULL));
	return aQueue->iFront == NULL;
	}

bool /* TQueueIterator */ queue_front(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if(queue_is_empty(aQueue))
		return false;
	if(!aValue)
		return false;
	*aValue = aQueue->iFront->iValue;
	return true;
	}

bool /* TQueueIterator */ queue_back(const struct TQueue *aQueue, TQueueElement *aValue)
	{
	if(queue_is_empty(aQueue))
		return false;
	if(!aValue)
		return false;
	*aValue = aQueue->iBack->iValue;
	return true;
	}

bool queue_push(struct TQueue *aQueue, TQueueElement aValue)
	{
	if(!aQueue)
		return false;
	struct TQueueNode* new_node = malloc(sizeof(struct TQueueNode));
	if(!new_node)
		return false;
	new_node->iNext = NULL;
	new_node->iValue = aValue;
	if(!aQueue->iFront)
		aQueue->iFront = new_node;
	else
		aQueue->iBack->iNext = new_node;
	aQueue->iBack = new_node;
	return true;
	}

bool queue_pop(struct TQueue *aQueue)
	{
	if(queue_is_empty(aQueue))
		return false;
	struct TQueueNode* old_node = aQueue->iFront;
	aQueue->iFront = old_node->iNext;
	free(old_node);
	if(!aQueue->iFront)
		aQueue->iBack = NULL;
	return true;
	}

void queue_destroy(struct TQueue *aQueue)
	{
	if(aQueue)
		{
		struct TqueueNode* act_node = aQueue->iFront;
		aQueue->iFront = NULL;
		while(act_node)
			{
			struct TQueueNode* old_node = act_node;
			act_node = old_node->iNext;
			free(old_node);
			}
		}
	}

struct TQueueIterator queue_iterator_begin(const struct TQueue *aQueue)
	{
	if(aQueue)
		return (struct TQueueIterator) { .iQueue = aQueue, .iActual = aQueue->iFront };
	return (struct TQueueIterator) { .iQueue = NULL, .iActual = NULL };
	}

bool queue_iterator_is_valid(const struct TQueueIterator *aIter)
	{
	if(aIter)
		if(aIter->iQueue)
			if(aIter->iQueue->iFront)
				if(aIter->iActual)
					return true;
	return false;
	}

bool queue_iterator_to_next(struct TQueueIterator *aIter)
	{
	if(queue_iterator_is_valid(aIter) == false)
		return false;
	aIter->iActual = aIter->iActual->iNext;
	return aIter->iActual != NULL;
	}

TQueueElement queue_iterator_value(const struct TQueueIterator *aIter)
	{
	if(queue_iterator_is_valid(aIter))
		return aIter->iActual->iValue;
	return (TQueueElement) { 0 };
	}

bool queue_iterator_set_value(const struct TQueueIterator *aIter, TQueueElement aValue)
	{
	if(queue_iterator_is_valid(aIter) == false)
		return false;
	aIter->iActual->iValue = aValue;
	return true;
	}
