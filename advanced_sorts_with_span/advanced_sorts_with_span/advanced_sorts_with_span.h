#ifndef ADVANCED_SORTS_WITH_SPAN_H
#define ADVANCED_SORTS_WITH_SPAN_H
/** \file advanced_sorts_with_span.h
 *  \brief Deklarace API účinnějších metod třídění využívající typ Span
 *  \author Petyovský
 *  \version 2025
 *  $Id: advanced_sorts_with_span.h 3047 2025-04-04 18:39:10Z petyovsky $
 */

#include "TVector.h"

/** \defgroup AdvancedSortsWithSpan 6.1. Účinnější metody třídění využívající typ Span
 *  \brief Deklarace API účinnějších metod třídění využívající typ Span
 *  \ingroup AdvancedSorts
 *  \{
 */

/** \brief Rychlé třídění výměnou (Quick Sort with span) s volbou prostředního prvku jako pivota a využívající typu Span
 *  \details Setřídí vzestupně elementy ve vektoru \p aVector pomocí metody rychlého třídění výměnou s volbou prostředního prvku jako pivota.
 *  \param[in,out] aVector Ukazatel na tříděný vektor hodnot
 */
void quick_sort_with_span(struct TVector *aVector);

/** \} AdvancedSortsWithSpan */

#endif /* ADVANCED_SORTS_WITH_SPAN_H */
