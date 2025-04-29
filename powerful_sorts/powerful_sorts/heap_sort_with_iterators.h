#ifndef HEAP_SORT_WITH_ITERATORS_H
#define HEAP_SORT_WITH_ITERATORS_H
/** \file heap_sort_with_iterators.h
 *  \brief Deklarace API výkonnější metody třídění (Heap sort), využívající iterátorové API pro přístup k uzlům haldy
 *  \author Petyovský
 *  \version 2025
 *  $Id: heap_sort_with_iterators.h 3073 2025-04-11 18:31:37Z petyovsky $
 */

#include "TVector.h"

/** \addtogroup PowerfulSorts
 *  \{
 */

/** \brief Třídění pomocí haldy (Heap Sort) využívající iterátorové API pro přístup k elementům vektoru
 *  \details Setřídí vzestupně elementy ve vektoru \p aVector metodou třídění pomocí haldy.
 *  \param[in,out] aVector Ukazatel na tříděný vektor hodnot
 */
void heap_sort_with_iterators(struct TVector *aVector);

/** \} PowerfulSorts */

#endif /* HEAP_SORT_WITH_ITERATORS_H */
