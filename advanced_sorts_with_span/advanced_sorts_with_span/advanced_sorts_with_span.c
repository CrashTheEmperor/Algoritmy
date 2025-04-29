/** \file advanced_sorts_with_span.c
 *  \brief Implementace API účinnějších metod třídění využívající typ Span
 *  \author Petyovský
 *  \version 2025
 *  $Id: advanced_sorts_with_span.c 3047 2025-04-04 18:39:10Z petyovsky $
 */

#include "advanced_sorts_with_span.h"
#include "TSpan.h"

static struct TVectorIterator Vector_begin_it = { 0 };		///< Bohužel z důvodů tisku hodnot elementů, je zde třeba statická proměnná :-(

/** \brief Formátovaný tisk hodnoty elementu za předpokladu platné hodnoty predikátu
 *  \details Vytiskne formátovaně hodnotu elementu pokud je parametr \p aCondition platný, jinak se vytisknou zástupné znaky.
 *  \param[in] aCondition pokud je \c true bude hodnota vytisknuta, jinak se vytisknou zástupné znaky
 *  \param[in] aIter Ukazatel na iterátor určující element k vytisknutí
 */
[[maybe_unused]] static void vector_element_print_if(bool aCondition, const struct TVectorIterator *aIter)
	{
	if(!aCondition)
		fputs(". ", stdout);
	else
		if(!vector_element_store_file(vector_iterator_value(aIter), stdout))
			fputs("Function 'vector_element_store_file()' failed!\n", stderr);
	}

/** \brief Vnitřní a lokální funkce realizující rekurzivní funkci pro metodu (Quick Sort)
 *  \details Realizuje rekurzivní funkci pro třídicí metodu (Quick Sort) pro omezený rozsah elementů vektoru.
 *  \param[in,out] aSpan Omezený rozsah elementů vektoru
 */
static void quick_sort_with_span_worker(struct TSpan aSpan)
	{
    // Získáme počet prvků v daném span (pohled na vektor)
    size_t n = span_size(&aSpan);
    if (n <= 1)
        return;  // Pokud je rozsah prázdný nebo obsahuje pouze jeden prvek, není co řadit.

    // Vybereme pivot jako prostřední prvek
    size_t pivotIndex = n / 2;
    TVectorElement pivot = span_value(&aSpan, pivotIndex);

    size_t i = 0, j = n - 1;
    // Partitioning: posunujeme index i od začátku a j od konce, dokud se nepřekříží
    while (i <= j)
    {
        // Pohyb indexu i dopředu: hledáme prvek, který není menší než pivot
        while (i < n && span_compare_position_value(&aSpan, i, pivot) < 0)
            i++;
        // Pohyb indexu j dozadu: hledáme prvek, který není větší než pivot
        while (j > 0 && span_compare_position_value(&aSpan, j, pivot) > 0)
            j--;

        if (i > j)
            break;  // Když se indexy překříží, partitioning je hotový

        // Prohození prvků na indexech i a j
        span_swap_positions(&aSpan, i, &aSpan, j);
        i++;
        if (j == 0)  // Prevence podtečení
            break;
        j--;
    }
    // Rozdělení spanu na dvě části:
    // Levá část: indexy 0 až j; pro volání použijeme:
    // Pravá část: indexy i až (n-1). Potřebujeme subspan o velikosti (n - i).
    if (j > 0)
    {
        struct TSpan leftSpan = span_create_range_subspan(aSpan, 0, j);
        quick_sort_with_span_worker(leftSpan);
    }
    if (i < n)
    {
        struct TSpan rightSpan = span_create_range_subspan(aSpan, i, (n - i) - 1);
        quick_sort_with_span_worker(rightSpan);
    }
	//auto it = Vector_begin_it;		// auto since C23
	//struct TVectorIterator it = Vector_begin_it;
	//for(bool valid = vector_iterator_is_valid(&it); valid; valid = vector_iterator_to_next(&it))
	//	vector_element_print_if(vector_iterator_is_inside_span(&aSpan, &it), &it);
	//putchar('\n');
	}

void quick_sort_with_span(struct TVector *aVector)
	{
	if(vector_size(aVector) < 2) // Výraz v podmínce vhodně upravte :-)
		return;

	Vector_begin_it = vector_iterator_begin(aVector);

	quick_sort_with_span_worker(span_create(*aVector));
	}
