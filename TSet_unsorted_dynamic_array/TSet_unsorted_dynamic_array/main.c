/** \file main.c
 *  \brief Hlavní program pro testování ADT TSet
 *  \author Petyovský
 *  \version 2025
 *  $Id: main.c 3085 2025-04-17 18:24:24Z petyovsky $
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
	//#include "testplan_set1.h"
	#include "testplan_set2.h"
	};

bool testset2_hardcoded(void)
	{
	struct TSet set2 = { 0 };
	set_init(&set2);
	gSetElementComparisons = 0;

	printf("set2 is empty: %s\n", bool_to_cstring(set_is_empty(&set2)) );
	UNLESS(set_insert(&set2, 222), goto cleanup_testset2_hardcoded);
	printf("set2 is empty: %s\n", bool_to_cstring(set_is_empty(&set2)) );

	for(struct TSetIterator it = set_iterator_begin(&set2); set_iterator_is_valid(&it); set_iterator_to_next(&it))
		printf("%d ", set_iterator_value(&it));
	putchar('\n');

	UNLESS(set_insert(&set2, 42), goto cleanup_testset2_hardcoded);
	UNLESS(set_insert(&set2, 43), goto cleanup_testset2_hardcoded);
	UNLESS(set_insert(&set2, 40), goto cleanup_testset2_hardcoded);
	UNLESS(set_insert(&set2, 41), goto cleanup_testset2_hardcoded);
	UNLESS(set_insert(&set2, 333), goto cleanup_testset2_hardcoded);

	set_for_each(set_iterator_begin(&set2), print_value_by_iterator);
	putchar('\n');

	UNLESS(set_erase(&set2, 222), goto cleanup_testset2_hardcoded);
	UNLESS(set_erase(&set2, 40), goto cleanup_testset2_hardcoded);

	set_for_each(set_iterator_begin(&set2), print_value_by_iterator);
	putchar('\n');

	bool is_element_of = set_is_element_of(&set2, 42);
	printf("set2 find 42: %s\n", bool_to_cstring(is_element_of));

	set_destroy(&set2);

	printf("\nTSetElement comparisons: %zu\n", gSetElementComparisons);
	return true;

cleanup_testset2_hardcoded:
	set_destroy(&set2);
	return false;
	}

int main(int argc, char *argv[])
	{
	struct TSet set1 = { 0 };
	set_init(&set1);

	if(!testbench_run(&set1, ITEMS_OF(testplan), testplan))
		{
		puts("testplan failed!!!");
		set_destroy(&set1);
		return 1;
		}
	set_destroy(&set1);

	testset2_hardcoded();
	return 0;
	}

/** \example cv11_reports_TSet_unsorted_dynamic_array_set1.lst
 * Příklad výstupu programu pro soubor `testplan_set1.h`.
 */

/** \example cv11_reports_TSet_unsorted_dynamic_array_set2.lst
 * Příklad výstupu programu pro soubor `testplan_set2.h`.
 */

/** \} MainProgram */
