#ifndef TSET_ELEMENT_HASHABLE_H
#define TSET_ELEMENT_HASHABLE_H
/** \file TSetElementHashable.h
 *  \brief Definice typu Hashable Basic SetElement a implementace API
 *  \author Petyovský
 *  \version 2024
 *  $Id: TSetElementHashable.h 3095 2025-04-25 15:11:26Z petyovsky $
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include "check.h"

/** \defgroup TSetElementHashable 1. Hashable SetElement
 *  \brief Definice datového typu Hashable SetElement a jeho funkcí
 *  \{
 */

extern size_t gSetElementComparisons;	///< Deklarace globální proměnné realizující počítadlo operací porovnání dvou hodnot typu SetElement

typedef int TSetElement;				///< Definice typu SetElement
#define TSET_ELEMENT_FRMSTR "%d"		///< Definice formátovacího řetězce pro souborové operace s typem SetElement

/** \brief Výpočet hash hodnoty elementu
 *  \details Provede výpočet hash hodnoty elementu předaného pomocí ukazatele.
 *  \param[in] aElement Ukazatel hodnotu elementu
 *  \return Hodnota typu \c size_t představující hash hodnotu elementu
 *  \attention Funkce ověřuje platnost ukazatele \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] static inline size_t set_element_hash_value(const TSetElement *aElement)
	{
	assert(aElement);
	size_t hash_value = 0;
	uint8_t *hash_value_ptr = (uint8_t *) &hash_value;
	const uint8_t *element_ptr = (const uint8_t *) aElement;

	for(size_t i = 0, j = 0; i < sizeof(TSetElement); ++i)
		{
		hash_value_ptr[j] += element_ptr[i];
		if(++j == sizeof(size_t))
			j = 0;
		}
	return hash_value;
	}

/** \brief Porovnání dvou elementů
 *  \details Provede trojcestné porovnání hodnot dvou elementů, předaných pomocí ukazatelů.
 *  \param[in] aLeft Ukazatel na levou porovnávanou hodnotu (tzv. LHS - Left Hand Side)
 *  \param[in] aRight Ukazatel na pravou porovnávanou hodnotu (tzv. RHS - Right Hand Side)
 *  \retval -1 Pokud (LHS < RHS)
 *  \retval  0 Pokud (LHS = RHS)
 *  \retval +1 Pokud (LHS > RHS)
 *  \attention Funkce ověřuje platnost obou ukazatelů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] static inline int set_element_comparator(const TSetElement *aLeft, const TSetElement *aRight)
	{
	assert(aLeft);
	assert(aRight);
	++gSetElementComparisons;
	if(*aLeft == *aRight)
		return 0;
	if(*aLeft < *aRight)
		return -1;
	return 1;
	}

/** \brief Načtení elementu ze souboru
 *  \details Načte hodnotu elementu z předem otevřeného souboru.
 *  \param[in,out] aElement Ukazatel na místo v paměti určené pro načtení hodnoty
 *  \param[in,out] aInputFile Ukazatel na soubor otevřený v módu pro čtení
 *  \return \c true pokud byla hodnota elementu ze souboru úspěšně načtena
 *  \attention Funkce ověřuje platnost obou ukazatelů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] static inline bool set_element_load_file(TSetElement *aElement, FILE *aInputFile)
	{
	assert(aElement);
	assert(aInputFile);
	return fscanf(aInputFile, TSET_ELEMENT_FRMSTR, aElement) == 1;
	}

/** \brief Uložení elementu do souboru
 *  \details Uloží hodnotu elementu do předem otevřeného souboru.
 *  \param[in] aElement Hodnota elementu určená pro uložení do souboru
 *  \param[in,out] aOutputFile Ukazatel na soubor otevřený v módu pro zápis
 *  \return \c true pokud byla hodnota elementu do souboru úspěšně uložena
 *  \attention Funkce ověřuje platnost ukazatele \p aOutputFile \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] static inline bool set_element_store_file(TSetElement aElement, FILE *aOutputFile)
	{
	assert(aOutputFile);
	return fprintf(aOutputFile, TSET_ELEMENT_FRMSTR " ", aElement) >= 0;
	}

/** \brief Vrací nový element s náhodnou hodnotou
 *  \details Vytváří a vrací nový element inicializovaný pomocí náhodné hodnoty.
 *  \return Nový element obsahující náhodnou hodnotu
 */
[[nodiscard]] static inline TSetElement set_element_random_value(void)
	{
	return (TSetElement) { (TSetElement)rand() };
	}

/** \} TSetElementHashable */

#endif /* TSET_ELEMENT_HASHABLE_H */
