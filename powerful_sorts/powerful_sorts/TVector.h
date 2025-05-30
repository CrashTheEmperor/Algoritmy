#ifndef TVECTOR_H
#define TVECTOR_H
/** \file TVector.h
 *  \brief Definice typu Sortable Vector with shareable sortstats
 *  \author Petyovský
 *  \version 2025
 *  $Id: TVector.h 3058 2025-04-11 10:04:11Z petyovsky $
 */

#include <stdio.h>
#include <stdbool.h>
#include <stddef.h>
#include "TVectorElement.h"
#include "check.h"

/** \defgroup TVector 2. Vector
 *  \brief Definice datového typu Vector a jeho funkcí
 *  \{
 */

/** \defgroup sortable_TVector 2.1. Rozšíření pro Sortable Vector
 *  \brief Definice typu Vector (sortable), popis jeho nově doplněných vlastností a funkcí
 *  \{
 */

/** \brief Definice typu VectorSortStatItem
 *  \details Typ VectorSortStatsItem spravuje statistiky o celkovém počtu operací: porovnání, výměn, přesunů, přečtení nebo zapsání hodnot elementů vektoru.
 */
struct TVectorSortStatsItem
	{
	size_t iComparisons;			///< Celkový počet operací porovnání hodnot mezi dvěma elementy vektoru
	size_t iSwaps;					///< Celkový počet operací výměny hodnot mezi dvěma elementy vektoru
	size_t iMoves;					///< Celkový počet operací přesunu hodnoty mezi dvěma elementy vektoru
	size_t iGets;					///< Celkový počet operací přečtení hodnoty z elementu vektoru
	size_t iSets;					///< Celkový počet operací zápisu hodnoty do elementu vektoru
	};

/** \brief Definice typu VectorSortStats
 *  \details Typ VectorSortStats spravuje statistiky o celkovém počtu operací: porovnání, výměn, přesunů, přečtení nebo zapsání hodnot elementů vektoru rozdělených dále dle provedení pomocí pozičního nebo iteračního API.
 */
struct TVectorSortStats
	{
	struct TVectorSortStatsItem iByPosition;	///< Statistika o počtech operací provedených pomocí pozičního API
	struct TVectorSortStatsItem iByIterator;	///< Statistika o počtech operací provedených pomocí iteračního API
	};

/** \} sortable_TVector */

/** \brief Definice typu Vector
 *  \details Typ Vector spravuje dynamicky alokované pole prvků typu VectorElement a umožňuje s nimi pracovat pomocí definovaného API.
 *  \invariant Obecně platný a testovatelný předpoklad: `(iValues == NULL && iSize == 0 && iStats != NULL)` nebo `(iValues != NULL && iSize != 0 && iStats != NULL)`.
 */
struct TVector
	{
	TVectorElement *iValues;		///< Ukazatel na počáteční prvek pole hodnot typu VectorElement
	size_t iSize;					///< Počet elementů vektoru
	struct TVectorSortStats *iStats;///< Statistika počtu operací s elementy Sortable vektoru (_mutable položka - může se měnit i když je Vektor konstantní strukturou_)
	bool iStatsAttached;			///< Příznak označující, že ukazatel iStats odkazuje na statistiky počtu operací patřící jinému vektoru
	};

/** \defgroup sortable_TVector_with_shareable_sortstats 2.2. Doplnění pro Sortable Vector o vlastnost sdílení statistik třídění
 *  \brief Definice typu Vector (sortable_with_shareable_sortstats), popis jeho nově doplněných vlastností a funkcí
 *  \{
 */

/** \brief Napojení statistik o počtu operací s elementy jednoho vektoru na statistiky jiného vektoru
 *  \details Provede trvalé napojení statistik o počtu operací s elementy jednoho vektoru na statistiky jiného vektoru. Počty operací budou od tohoto okamžiku trvale sdíleny mezi oběma vektory.
 *  \param[in] aFromVector Ukazatel na existující zdrojový vektor jehož statistiky chceme využívat
 *  \param[in,out] aToVector Ukazatel na cílového vektor jenž má mít přistup ke statistikám vektoru \p aFromVector
 *  \return \c true pokud byly statistiky vektoru aToVector úspěšně napojeny na vektor aFromVector
 */
[[nodiscard]] bool vector_attach_sortstats(const struct TVector *aFromVector, struct TVector *aToVector);
/** \} sortable_TVector_with_shareable_sortstats */

/** \brief Alokace vektoru a inicializace jeho elementů na hodnotu 0
 *  \details Dynamicky alokuje paměť pro pole o zadaném počtu elementů, inicializuje elementy na hodnotu 0.
 *  \param[in,out] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[in] aSize Požadovaný počet elementů vektoru
 *  \return \c true pokud byl vektor úspěšně alokován a inicializován
 */
[[nodiscard]] bool vector_init(struct TVector *aVector, size_t aSize);

/** \brief Alokace vektoru a inicializace jeho elementů na náhodné hodnoty
 *  \details Dynamicky alokuje paměť pro pole o zadaném počtu elementů, inicializuje elementy na náhodné hodnoty.
 *  \param[in,out] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[in] aSize Požadovaný počet elementů vektoru
 *  \return \c true pokud byl vektor úspěšně alokován a inicializován
 */
[[nodiscard]] bool vector_init_random(struct TVector *aVector, size_t aSize);

/** \brief Alokace vektoru a inicializace jeho elementů ze souboru
 *  \details Načte ze souboru počet elementů vektoru, dynamicky alokuje paměť pro vektor o načteném počtu elementů, načte ze souboru hodnoty jednotlivých elementů.
 *  \param[in,out] aVector Ukazatel na místo v paměti určené pro inicializaci vektoru
 *  \param[in,out] aInputFile Ukazatel na soubor otevřený v módu pro čtení
 *  \return \c true pokud byl vektor z dat v souboru úspěšně alokován a inicializován
 */
[[nodiscard]] bool vector_init_file(struct TVector *aVector, FILE *aInputFile);

/** \brief Vytvoření úplné kopie vektoru
 *  \details Dynamicky alokuje paměť pro nové pole o shodném počtu elementů, nakopíruje hodnoty všech elementů ze starého do nového vektoru.
 *  \param[in] aVector Ukazatel na místo v paměti obsahující zdrojový vektor
 *  \param[in,out] aVectorClone Ukazatel na místo v paměti určené pro vytvořenou kopii
 *  \return \c true pokud byl nový vektor úspěšně alokován a inicializován
 */
[[nodiscard]] bool vector_clone(const struct TVector *aVector, struct TVector *aVectorClone);

/** \brief Uložení vektoru a jeho elementů do souboru
 *  \details Uloží do souboru počet elementů vektoru a hodnoty jednotlivých elementů.
 *  \param[in] aVector Ukazatel na existující vektor
 *  \param[in,out] aOutputFile Ukazatel na soubor otevřený v módu pro zápis
 *  \return \c true pokud byl vektor a jeho elementy úspěšně uloženy do souboru
 */
[[nodiscard]] bool vector_store_file(const struct TVector *aVector, FILE *aOutputFile);

/** \brief Přečtení hodnoty elementu z vektoru na požadované pozici
 *  \details Vrací hodnotu elementu z požadované pozice (indexu) vektoru.
 *  \param[in] aVector Ukazatel na existující vektor určený pro přečtení hodnoty elementu
 *  \param[in] aPos Požadovaná pozice (index) elementu
 *  \return Hodnota elementu uložená ve vektoru \p aVector na pozici \p aPos
 *  \attention Funkce ověřuje platnost ukazatele a rozsah parametru \p aPos \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] TVectorElement vector_value(const struct TVector *aVector, size_t aPos);

/** \brief Zapsání hodnoty elementu do vektoru na požadovanou pozici
 *  \details Zápis nové hodnoty elementu do vektoru na požadovanou pozici (index).
 *  \param[in,out] aVector Ukazatel na existující vektor určený pro zapsání hodnoty elementu
 *  \param[in] aPos Požadovaná pozice (index) elementu
 *  \param[in] aValue Nová hodnota elementu
 *  \attention Funkce ověřuje platnost ukazatele a rozsah parametru \p aPos \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_set_value(struct TVector *aVector, size_t aPos, TVectorElement aValue);

/** \brief Přečtení počtu elementů vektoru
 *  \details Vrací velikost (počet elementů) vektoru.
 *  \param[in] aVector Ukazatel na existující vektor
 *  \return Počet elementů vektoru nebo hodnota 0 v případě chyby
 */
[[nodiscard]] size_t vector_size(const struct TVector *aVector);

/** \brief Zjištění, zda je vektor prázdný
 *  \details Funkce (predikát) vracející \c bool hodnotu reprezentující test, zda je vektor prázdný (tj. má nulový počet elementů).
 *  \param[in] aVector Ukazatel na existující vektor
 *  \return \c true pokud je vektor prázdný
 */
[[nodiscard]] static inline bool vector_is_empty(const struct TVector *aVector)
	{
	return !vector_size(aVector);
	}

/** \brief Změna velikosti existujícího vektoru
 *  \details Změna počtu elementů vektoru, alokace nové dynamické paměti pro pole o novém počtu prvků, kopie prvků z původního pole, inicializace doplněných prvků na hodnoty 0, dealokace dynamické paměti původního pole.
 *  \param[in,out] aVector Ukazatel na existující vektor
 *  \param[in] aNewSize Nový počet elementů vektoru
 *  \return \c true pokud byl vektor úspěšně přealokován a všechny elementy nového vektoru byly úspěšně inicializovány
 */
[[nodiscard]] bool vector_resize(struct TVector *aVector, size_t aNewSize);

/** \addtogroup sortable_TVector
 *  \{
 */

/** \brief Přesun hodnoty elementu vektoru
 *  \details Přesun hodnoty elementu vektoru z/do libovolné pozice nebo případně i mezi různými vektory. Parametry \p aToVector a \p aFromVector mohou být stejné.
 *  \param[in,out] aToVector Ukazatel na cílový vektor
 *  \param[in] aToPos Cílová pozice (index) elementu ve vektoru \p aToVector
 *  \param[in] aFromVector Ukazatel na zdrojový vektor
 *  \param[in] aFromPos Zdrojová pozice (index) elementu ve vektoru \p aFromVector
 *  \attention Funkce ověřuje platnost ukazatelů a rozsah indexů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_move_positions(struct TVector *aToVector, size_t aToPos, const struct TVector *aFromVector, size_t aFromPos);

/** \brief Porovnání hodnot elementů vektorů
 *  \details Trojcestně porovná hodnoty elementů mezi zvolenými pozicemi nebo případně i mezi různými vektory. Parametry \p aLeftVector a \p aRightVector mohou být stejné.
 *  \param[in] aLeftVector Ukazatel na levý vektor při porovnání
 *  \param[in] aLeftPos Pozice (index) (LHS) elementu ve vektoru \p aLeftVector 
 *  \param[in] aRightVector Ukazatel na pravý vektor při porovnání
 *  \param[in] aRightPos Pozice (index) (RHS) elementu ve vektoru \p aRightVector 
 *  \retval -1 Pokud (LHS < RHS)
 *  \retval  0 Pokud (LHS = RHS)
 *  \retval +1 Pokud (LHS > RHS)
 *  \attention Funkce ověřuje platnost ukazatelů a rozsah indexů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] int vector_compare_positions(const struct TVector *aLeftVector, size_t aLeftPos, const struct TVector *aRightVector, size_t aRightPos);

/** \brief Porovnání mezi hodnotou elementu vektoru a hodnotou typu VectorElement
 *  \details Trojcestně porovná hodnotu elementu vektoru na zvolené pozici se zadanou hodnotou \p aValue.
 *  \param[in] aVector Ukazatel na vektor při porovnání
 *  \param[in] aPos Pozice (index) (LHS) elementu ve vektoru \p aVector
 *  \param[in] aValue Hodnota stojící při porovnání na pravé straně (RHS)
 *  \retval -1 Pokud (LHS < RHS)
 *  \retval  0 Pokud (LHS = RHS)
 *  \retval +1 Pokud (LHS > RHS)
 *  \attention Funkce ověřuje platnost ukazatele a rozsah indexu vektoru \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] int vector_compare_position_value(const struct TVector *aVector, size_t aPos, TVectorElement aValue);

/** \brief Výměna hodnot elementů vektorů
 *  \details Vzájemně zamění hodnoty elementů mezi zvolenými pozicemi nebo případně i mezi různými vektory. Parametry \p aLeftVector a \p aRightVector mohou být stejné.
 *  \param[in,out] aLeftVector Ukazatel na levý vektor pro záměnu hodnoty elementu
 *  \param[in] aLeftPos Pozice (index) (LHS) elementu ve vektoru \p aLeftVector
 *  \param[in,out] aRightVector Ukazatel na pravý vektor při záměně hodnoty elementu
 *  \param[in] aRightPos Pozice (index) (RHS) elementu ve vektoru \p aRightVector
 *  \attention Funkce ověřuje platnost ukazatelů a rozsah indexů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_swap_positions(struct TVector *aLeftVector, size_t aLeftPos, struct TVector *aRightVector, size_t aRightPos);

/** \brief Výměna mezi hodnotou elementu vektoru a proměnnou typu VectorElement
 *  \details Vzájemně zamění hodnotu elementu vektoru na zvolené pozici se zadanou hodnotou v proměnné typu VectorElement.
 *  \param[in,out] aVector Ukazatel na vektor pro záměnu hodnoty elementu
 *  \param[in] aPos Pozice (index) elementu ve vektoru \p aVector
 *  \param[in,out] aValue Ukazatel na hodnotu proměnné typu VectorElement pro záměnu
 *  \attention Funkce ověřuje platnost obou ukazatelů a rozsah indexu vektoru \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_swap_position_value(struct TVector *aVector, size_t aPos, TVectorElement *aValue);

/** \brief Ověření korektního setřídění vektoru
 *  \details Ověřuje správnost vzestupného setřídění zadaného vektoru. Také ověřuje, zda setříděný vektor obsahuje shodné hodnoty elementů jako nesetříděný vektor.
 *  \param[in] aUnsortedVector Ukazatel na původní (nesetříděný) vektor
 *  \param[in] aSortedVector Ukazatel na nový (setříděný) vektor
 *  \return \c true pokud nový vektor \p aSortedVector obsahuje všechny hodnoty elementů jako původního vektor \p aUnsortedVector a tyto elementy jsou vzestupně setříděny
 */
[[nodiscard]] bool vector_is_ascendantly_sorted(const struct TVector *aUnsortedVector, const struct TVector *aSortedVector);

/** \brief Zobrazení hodnoty statistik počtu operací s elementy vektoru
 *  \details Vytiskne na konzolu (stdout) celkové počty operací provedené s elementy vektoru.
 *  \param[in] aVector Ukazatel na vektor, jehož statistiky chceme zobrazit
 *  \return \c true pokud byl ukazatel na vektor platný a statistiky byly zobrazeny na konzolu
 */
[[nodiscard]] bool vector_print_sortstats(const struct TVector *aVector);

/** \} sortable_TVector */

/** \brief Dealokace vektoru
 *  \details Dealokace dynamicky alokovaného pole, nastavení počtu elementů i ukazatele na hodnotu 0 (NULL).
 *  \param[in,out] aVector Ukazatel na existující vektor
 */
void vector_destroy(struct TVector *aVector);
/** \} TVector */

/** \defgroup TVectorIterator 4. Iterátor vektoru
 *  \brief Definice datového typu VectorIterator a jeho funkcí
 *  \{
 */

/** \brief Definice typu VectorIterator
 *  \details VectorIterator se při vzniku naváže na zvolený vektor a následně umožňuje přistupovat k jednotlivým elementům pomocí definovaného API.
 */
struct TVectorIterator
	{
	struct TVector *iVector;	///< Ukazatel na navázaný vektor (mutable iterátor - umožňuje měnit elementy VectorElement)
	size_t iPos;				///< Aktuální pozice pro indexaci elementu v navázaném vektoru
	};

/** \brief Vytvoření nového iterátoru ukazujícího na počáteční element
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný vektor a ukazuje na jeho počáteční element.
 *  \param[in] aVector Ukazatel na existující vektor
 *  \return Nový iterátor asociovaný s vektorem \p aVector ukazující na počáteční element vektoru
 */
[[nodiscard]] struct TVectorIterator vector_iterator_begin(const struct TVector *aVector);

/** \brief Vytvoření nového iterátoru ukazujícího na zadanou pozici
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný vektor a ukazuje na element na zadané pozici.
 *  \param[in] aVector Ukazatel na existující vektor
 *  \param[in] aPos Zadaná pozice
 *  \return Nový iterátor asociovaný s vektorem \p aVector ukazující na element na zadané pozici \p aPos
 */
[[nodiscard]] struct TVectorIterator vector_iterator_pos(const struct TVector *aVector, size_t aPos);

/** \brief Vytvoření nového iterátoru ukazujícího na poslední element
 *  \details Vytvoří a vrací nový iterátor, který je navázán (asociován) na zadaný vektor a ukazuje na jeho poslední element.
 *  \param[in] aVector Ukazatel na existující vektor
 *  \return Nový iterátor asociovaný s vektorem \p aVector ukazující na poslední element vektoru
 */
[[nodiscard]] struct TVectorIterator vector_iterator_last(const struct TVector *aVector);

/** \brief Zjištění platnosti iterátoru
 *  \details Funkce (predikát) vracející \c bool hodnotu definující platnost iterátoru.
 *  \param[in] aIter Ukazatel na existující iterátor
 *  \return \c true pokud je iterátor platný a ukazuje na platné místo v asociovaném vektoru
 */
[[nodiscard]] bool vector_iterator_is_valid(const struct TVectorIterator *aIter);

/** \brief Posunutí iterátoru vpřed
 *  \details Funkce ověří platnost iterátoru, a pokud je platný, zajistí jeho posun vpřed (tj. na následující element v asociovaném vektoru).
 *  \param[in,out] aIter Ukazatel na existující iterátor
 *  \return \c true pokud je iterátor platný a ukazuje i po posunutí na platné místo v asociovaném vektoru
 */
bool vector_iterator_to_next(struct TVectorIterator *aIter);

/** \brief Posunutí iterátoru vzad
 *  \details Funkce ověří platnost iterátoru, a pokud je platný, zajistí jeho posun vzad (tj. na předchozí element v asociovaném vektoru).
 *  \param[in,out] aIter Ukazatel na existující iterátor
 *  \return \c true pokud je iterátor platný a ukazuje i po posunutí na platné místo v asociovaném vektoru
 */
bool vector_iterator_to_prev(struct TVectorIterator *aIter);

/** \brief Přečtení hodnoty elementu z vektoru pomocí iterátoru
 *  \details Vrací hodnotu elementu vektoru z pozice (indexu) určeného iterátorem.
 *  \param[in] aIter Ukazatel na existující iterátor
 *  \return Hodnota elementu vektoru z pozice, na kterou ukazuje iterátor \p aIter, nebo nulový element (pokud je iterátor neplatný).
 */
[[nodiscard]] TVectorElement vector_iterator_value(const struct TVectorIterator *aIter);

/** \brief Zapsání hodnoty elementu do vektoru pomocí iterátoru
 *  \details Zápis nové hodnoty elementu do vektoru na pozici určenou iterátorem.
 *  \param[in] aIter Ukazatel na existující iterátor
 *  \param[in] aValue Nová hodnota elementu
 *  \return \c true pokud je iterátor platný a zápis mohl proběhnout na platné místo v asociovaném vektoru
 */
bool vector_iterator_set_value(const struct TVectorIterator *aIter, TVectorElement aValue);

/** \defgroup sortable_TVectorIterator 4.1. Rozšíření pro Sortable VectorIterator
 *  \brief Definice datového typu VectorIterator (sortable), popis jeho rozšiřujících vlastností a funkcí
 *  \{
 */

/** \brief Přesun hodnoty elementu vektoru určené dvěma iterátory
 *  \details Přesun hodnoty elementu vektoru z/do pozice určené iterátory.
 *  \param[in] aToIter Iterátor na cílový element vektoru
 *  \param[in] aFromIter Iterátor na zdrojový element vektoru
 *  \attention Funkce ověřuje platnost obou iterátorů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_move_with_iterators(const struct TVectorIterator *aToIter, const struct TVectorIterator *aFromIter);

/** \brief Porovnání hodnot elementů vektorů určených dvěma iterátory
 *  \details Trojcestně porovná hodnoty elementů určených dvěma iterátory.
 *  \param[in] aLeftIter Iterátor určující levý element při porovnání (LHS)
 *  \param[in] aRightIter Iterátor určující pravý element při porovnání (RHS)
 *  \retval -1 Pokud (LHS < RHS)
 *  \retval  0 Pokud (LHS = RHS)
 *  \retval +1 Pokud (LHS > RHS)
 *  \attention Funkce ověřuje platnost obou iterátorů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] int vector_compare_with_iterators(const struct TVectorIterator *aLeftIter, const struct TVectorIterator *aRightIter);

/** \brief Porovnání mezi hodnotou elementu vektoru určenou iterátorem a hodnotou typu VectorElement
 *  \details Trojcestně porovná hodnotu elementu vektoru na pozici iterátorem se zadanou hodnotou \p aValue.
 *  \param[in] aIter Iterátor určující levý element při porovnání (LHS)
 *  \param[in] aValue Hodnota stojící při porovnání na pravé straně (RHS)
 *  \retval -1 Pokud (LHS < RHS)
 *  \retval  0 Pokud (LHS = RHS)
 *  \retval +1 Pokud (LHS > RHS)
 *  \attention Funkce ověřuje platnost iterátoru \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] int vector_compare_with_iterator_value(const struct TVectorIterator *aIter, TVectorElement aValue);

/** \brief Výměna hodnot elementů vektorů určených dvěma iterátory
 *  \details Vzájemně zamění hodnoty elementů určených dvěma iterátory.
 *  \param[in] aLeftIter Iterátor určující levý element vektoru
 *  \param[in] aRightIter Iterátor určující pravý element vektoru
 *  \attention Funkce ověřuje platnost obou iterátorů \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_swap_with_iterators(const struct TVectorIterator *aLeftIter, const struct TVectorIterator *aRightIter);

/** \brief Výměna mezi hodnotou elementu vektoru určenou iterátorem a proměnnou typu VectorElement
 *  \details Vzájemně zamění hodnotu elementu vektoru určenou iterátorem se zadanou hodnotou v proměnné typu VectorElement.
 *  \param[in] aIter Iterátor určující element vektoru pro záměnu
 *  \param[in] aValue Ukazatel na hodnotu proměnné typu VectorElement pro záměnu
 *  \attention Funkce ověřuje platnost iterátoru a ukazatele \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
void vector_swap_with_iterator_value(const struct TVectorIterator *aIter, TVectorElement *aValue);

/** \brief Test shodnosti dvou iterátorů
 *  \details Vzájemně porovná hodnotu dvou iterátorů. Oba iterátory musí vzniknout ze stejného vektoru.
 *  \ingroup sortable_TVector_with_shareable_sortstats
 *  \param[in] aLeftIter Levý iterátor
 *  \param[in] aRightIter Pravý iterátor
 *  \return \c true pokud oba iterátory odkazují na element na stejné pozici a ve stejném vektoru, nebo pokud jsou oba iterátory neplatné
 */
[[nodiscard]] bool vector_iterator_is_equal(const struct TVectorIterator *aLeftIter, const struct TVectorIterator *aRightIter);

/** \brief Porovnání dvou iterátorů
 *  \details Provede trojcestné porovnání hodnot dvou iterátorů, předaných pomocí ukazatelů. Oba iterátory musí vzniknout ze stejného vektoru.
 *  \ingroup sortable_TVector_with_shareable_sortstats
 *  \param[in] aLeftIter Levý iterátor (tzv. LHS - Left Hand Side)
 *  \param[in] aRightIter Pravý iterátor (tzv. RHS - Right Hand Side)
 *  \retval -1 Pokud je pozice v \p aLeftIter \b < než pozice v \p aRightIter, nebo je \p aLeftIter \b neplatný a \p aRightIter platný
 *  \retval  0 Pokud je pozice v \p aLeftIter \b = pozici v \p aRightIter, nebo jsou oba iterátory \b neplatné
 *  \retval +1 Pokud je pozice v \p aLeftIter \b > než pozice v \p aRightIter, nebo je \p aLeftIter platný a \p aRightIter \b neplatný
 *  \attention Funkce ověřuje, že oba iterátory vznikly ze stejného vektoru \b pouze při překladu v režimu `Debug`, kdy pomocí `assert` hlásí běhovou chybu!
 */
[[nodiscard]] int vector_iterator_comparator(const struct TVectorIterator *aLeftIter, const struct TVectorIterator *aRightIter);

/** \} sortable_TVectorIterator */

/** \} TVectorIterator */

/** \defgroup IteratorAlgorithms 5. Univerzální funkce pro práci s iterátory
 *  \brief Definice funkcí používající iterátory
 *  \{
 */

/** \brief Zavolání zvolené funkce na každý element vektoru od pozice určené iterátorem až do konce vektoru
 *  \details Zavolá zadanou funkci \p aOperation na každý element vektoru v rozsahu od pozice určené iterátorem až do konce vektoru.
 *  \param[in] aIter Ukazatel na existující iterátor
 *  \param[in] aOperation Ukazatel na funkci vracející \c void a mající jeden parametr typu ukazatel na iterátor
 */
static inline void vector_for_each(struct TVectorIterator aIter, void(*aOperation)(const struct TVectorIterator *aIter))
	{
	for(bool valid = vector_iterator_is_valid(&aIter); valid; valid = vector_iterator_to_next(&aIter))
		aOperation(&aIter);
	}

/** \brief Zavolání zvolené funkce na každý element vektoru v zadaném rozsahu pozic určených dvěma iterátory
 *  \details Zavolá zadanou funkci \p aOperation na každý element vektoru v rozsahu od pozice určené iterátorem až do elementu v zadaném rozsahu.
 *  \param[in] aFirstIter Ukazatel na existující iterátor definující počáteční element v rozsahu
 *  \param[in] aLastIter Ukazatel na existující iterátor definující poslední element v rozsahu
 *  \param[in] aOperation Ukazatel na funkci vracející \c void a mající jeden parametr typu ukazatel na iterátor
 */
static inline void vector_for_range(struct TVectorIterator aFirstIter, const struct TVectorIterator aLastIter, void(*aOperation)(const struct TVectorIterator *aIter))
	{
	for(bool valid = vector_iterator_is_valid(&aFirstIter); valid; valid = vector_iterator_to_next(&aFirstIter))
		{
		aOperation(&aFirstIter);
		if(vector_iterator_is_equal(&aFirstIter, &aLastIter))
			break;
		}
	}

/** \brief Zavolání zvolené funkce na prvních N elementů vektoru od pozice určené iterátorem
 *  \details Zavolá zadanou funkci \p aOperation na prvních \p aN elementů vektoru od počáteční pozice určené iterátorem. Pokud vektor má méně než \p aN elementů, funkce se ukončí dříve a vrátí neplatný iterátor.
 *  \param[in] aIter Ukazatel na existující iterátor
 *  \param[in] aN Hodnota udávající prvních N elementů vektoru, na které se má zavolat funkce \p aOperation
 *  \param[in] aOperation Ukazatel na funkci vracející \c void a mající jeden parametr typu ukazatel na iterátor
 *  \return Hodnota iterátoru ukazujícího za `aN`-tý element vektoru, nebo neplatný iterátor pokud vektor nemá další elementy.
 */
static inline struct TVectorIterator vector_for_n(struct TVectorIterator aIter, size_t aN, void(*aOperation)(const struct TVectorIterator *aIter))
	{
	for(bool valid = vector_iterator_is_valid(&aIter); aN && valid; --aN, valid = vector_iterator_to_next(&aIter))
		aOperation(&aIter);
	return aIter;
	}

/** \} IteratorAlgorithms */

#endif /* TVECTOR_H */
