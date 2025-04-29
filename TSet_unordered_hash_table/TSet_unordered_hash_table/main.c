/** \file main.c
 *  \brief Hlavní program pro testování ADT TSet - (realizace unordered množiny pomocí hašovací tabulky)
 *  \author Petyovský
 *  \version 2025
 *  $Id: main.c 3095 2025-04-25 15:11:26Z petyovsky $
 */

#include <stdio.h>
#include "testbench.h"
#include "TSet.h"
#include "main_support.h"

/** \defgroup MainProgram 5. Hlavní program
 *  \brief Definice funkcí hlavního programu
 *  \{
 */

const struct TTestPlan testplan[] =
	{
	#include "testplan_set1.h"
	//#include "testplan_set2.h"
	//#include "testplan_set3.h"
	};

bool testset_hardcoded(void)
	{
	struct TSet set = { 0 };
	set_init(&set);
	gSetElementComparisons = 0;

	printf("set is empty: %s\n", bool_to_cstring(set_is_empty(&set)) );
	UNLESS(set_insert(&set, 222), goto cleanup_testset_hardcoded);
	printf("set is empty: %s\n", bool_to_cstring(set_is_empty(&set)));

	for(struct TSetIterator it = set_iterator_begin(&set); set_iterator_is_valid(&it); set_iterator_to_next(&it))
		printf(TSET_ELEMENT_FRMSTR " ", set_iterator_value(&it));
	putchar('\n');

	UNLESS(set_insert(&set, 42), goto cleanup_testset_hardcoded);
	UNLESS(set_insert(&set, 43), goto cleanup_testset_hardcoded);
	UNLESS(set_insert(&set, 40), goto cleanup_testset_hardcoded);
	UNLESS(set_insert(&set, 41), goto cleanup_testset_hardcoded);
	UNLESS(set_insert(&set, 44), goto cleanup_testset_hardcoded);
	UNLESS(set_insert(&set, 45), goto cleanup_testset_hardcoded);

	//for(int i = 200;i > 100; --i)
	for(int i = 200;i > 197; --i)
		UNLESS(set_insert(&set, i), goto cleanup_testset_hardcoded);

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	UNLESS(set_erase(&set, 44), goto cleanup_testset_hardcoded);
	//for(int i = 200;i > 100; --i)
	for(int i = 200; i > 197; --i)
		UNLESS(set_erase(&set, i), goto cleanup_testset_hardcoded);

	UNLESS(set_erase(&set, 222), goto cleanup_testset_hardcoded);
	UNLESS(set_erase(&set, 40), goto cleanup_testset_hardcoded);
	UNLESS(set_erase(&set, 41), goto cleanup_testset_hardcoded);

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	bool erased = set_erase(&set, 42+256);
	printf("set erase(42+256): %s\n", bool_to_cstring(erased));

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	bool is_element_of = set_is_element_of(&set, 42);
	printf("set find(42): %s\n", bool_to_cstring(is_element_of));

	bool inserted = set_insert(&set, 45);
	printf("set insert(45): %s\n", bool_to_cstring(inserted));

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	erased = set_erase(&set, 64);
	printf("set erase(64): %s\n", bool_to_cstring(erased));

	set_for_each(set_iterator_begin(&set), print_value_by_iterator);
	putchar('\n');

	set_destroy(&set);

	printf("\nTSetElement comparisons: %zu\n", gSetElementComparisons);
	return true;

cleanup_testset_hardcoded:
	set_destroy(&set);
	return false;
	}

int main(int argc, char *argv[])
	{
	struct TSet set = { 0 };
	set_init(&set);

	if(!testbench_run(&set, ITEMS_OF(testplan), testplan))
		{
		puts("testplan failed!!!");
		set_destroy(&set);
		return 1;
		}
	set_destroy(&set);

	testset_hardcoded();
	return 0;
	}

/** \example cv12_reports_testplan_set1_linear_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set1.h` při `HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING`.
 */
/** \example cv12_reports_testplan_set1_quadratic_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set1.h` při `HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING`.
 */

/** \example cv12_reports_testplan_set2_linear_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set2.h` při `HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING`.
 */
/** \example cv12_reports_testplan_set2_quadratic_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set2.h` při `HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING`.
 */

/** \example cv12_reports_testplan_set3_linear_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set3.h` při `HASH_TABLE_SEARCH_VARIANT == LINEAR_PROBING`.
 */
/** \example cv12_reports_testplan_set3_quadratic_probing.lst
 * Příklad výstupu programu pro soubor `testplan_set3.h` při `HASH_TABLE_SEARCH_VARIANT == QUADRATIC_PROBING`.
 */

/** \} MainProgram */
