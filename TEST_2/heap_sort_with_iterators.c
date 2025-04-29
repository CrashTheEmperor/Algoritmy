/** \file heap_sort_with_iterators.c
 *  \brief Implementace API výkonnější metody třídění (Heap sort), využívající iterátorové API pro přístup k uzlům haldy
 *  \author Petyovský
 *  \version 2025
 *  $Id: heap_sort_with_iterators.c 3073 2025-04-11 18:31:37Z petyovsky $
 */

#include "heap_sort_with_iterators.h"
#include "THeap.h"

/** \brief Vnitřní a lokální funkce zajišťující vložení hodnoty do zvoleného uzlu haldy, při zachování podmínek haldy
 *  \details Lokální funkce zajišťuje vložení hodnoty do zvoleného uzlu haldy, při zachování podmínek haldy (prosívání hodnoty směrem k listům).
 *  \param[in] aValue Hodnota vkládáná do haldy
 *  \param[in] aParent Iterátor na uzel haldy určený pro vložení hodnoty \p aValue (hodnota v tomto uzlu bude přepsána)
 */
static inline void sift_down(THeapElement aValue, struct THeapIterator aParent)
	{
	struct THeapIterator parent = aParent;
	struct THeapIterator left_child = parent;
	while (heap_iterator_to_left(&left_child))
	{
		struct THeapIterator largest_child = left_child;
		struct THeapIterator right_child = parent;

		if (heap_iterator_to_right(&right_child) &&
			heap_compare_with_iterators(&left_child, &right_child) < 0)
		{
			largest_child = right_child;
		}

		if (heap_compare_with_iterator_value(&largest_child, aValue) > 0)
		{
			heap_move_with_iterators(&parent, &largest_child);
			parent = largest_child;
			left_child = parent;
		}
		else
			break; // Heap podmínka splněna
	}
	heap_iterator_set_value(&parent, aValue);
	}

/** \brief Vnitřní a lokální funkce realizující uspořádání elementů vektoru do haldy
 *  \details Lokální funkce zajišťuje uspořádání elementů vektoru do haldy, pomocí volání funkce sift_down().
 *  \param[in,out] aHeap Ukazatel na vytvářenou haldu
 */
static void heapify(struct THeap *aHeap)
	{
	size_t size = heap_size(aHeap);
	if (size < 2)
		return;

	size_t pos = heap_pos_to_parent(size - 1);

	do {
		struct TVectorIterator vec_iter = vector_iterator_pos(&aHeap->iVector, pos);
		struct THeapIterator heap_iter = { .iVectorIter = vec_iter };
		THeapElement value = heap_iterator_value(&heap_iter);

		sift_down(value, heap_iter);
	} while (pos--);

//	fputs("Heapify:", stdout);
//	heap_dump(aHeap, stdout);;
	}

void heap_sort_with_iterators(struct TVector *aVector)
	{
//	for(size_t i = 0; i < vector_size(aVector); ++i)
//		if(!vector_element_store_file(aVector->iValues[i], stdout))
//			fputs("Function 'vector_element_store_file()' failed!\n", stderr);
//	putchar('\n');

	if(vector_size(aVector) < 2)
		return;

	//auto heap = heap_create(*aVector);		// auto since C23
	struct THeap heap = heap_create(*aVector);

//	heap_dump(&heap, stdout);

	heapify(&heap);

//	heap_dump(&heap, stdout);

//	fputs("Heapify stats:\n", stdout);
//	vector_print_sortstats(aVector);

	const struct THeapIterator root = heap_iterator_begin(&heap);
	size_t heapsize = heap_size(&heap);

	while(heapsize > 1)
		{
		const struct THeapIterator last = heap_iterator_last(&heap);

//		heap_dump(&heap, stdout);

		const THeapElement value = heap_iterator_value(&last);
		heap_move_with_iterators(&last, &root);

		heapsize = heap_decrement_size(&heap);

//		fprintf(stdout, "Value: " TVECTOR_ELEMENT_FRMSTR "\n", value);
//		heap_dump(&heap, stdout);

		sift_down(value, root);

//		heap_dump(&heap, stdout);
		}
	}
