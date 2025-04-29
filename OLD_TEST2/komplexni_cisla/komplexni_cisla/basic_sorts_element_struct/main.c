#include <stdio.h>
#include "basic_sorts.h"
#include "main_support.h"
#include "check.h"

int main(int argc, char* argv[])
	{
	FILE* fsrc = fopen("complex.txt", "r");
	if (!fsrc)
		return 1;

	struct TVector vector1 = { 0 };

	bool initialized = vector_init_random(&vector1, 5);

	fclose(fsrc);
	if (!initialized)
		return 2;

	vector_for_each(vector_iterator_begin(&vector1), print_element);
	putchar('\n');

	vector_element_set_comparator(EByAbs);
	shaker_sort(&vector1);

	printf("Vzestupne podle abs:");
	putchar('\n');
	vector_for_each(vector_iterator_begin(&vector1), print_element);
	putchar('\n');
	
	vector_element_set_comparator(EByIm);
	shaker_sort(&vector1);

	printf("Vzestupne podle im:");
	putchar('\n');
	vector_for_each(vector_iterator_begin(&vector1), print_element);
	putchar('\n');

	vector_element_set_comparator(EByRe);
	shaker_sort(&vector1);

	printf("Vzestupne podle re:");
	putchar('\n');
	vector_for_each(vector_iterator_begin(&vector1), print_element);

	FILE* fout = fopen("sorted_data_complex.txt", "w");
	if (!fout)
		return 3;

	vector_store_file(&vector1, fout);

	fclose(fout);

	vector_destroy(&vector1);
	return 0;
	}

/** \} MainProgram */
