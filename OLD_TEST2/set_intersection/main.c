/** \file main.c
 *  \brief Hlavní program pro testování implementace průniku množin
 *  \author Student
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "TSet.h"
 #include "check.h"
 
 // Pomocná funkce pro tisk obsahu množiny
 void print_set(const struct TSet *aSet)
 {
     printf("Set content: ");
     struct TSetIterator iter = set_iterator_begin(aSet);
     while (set_iterator_is_valid(&iter))
     {
         printf("%d ", set_iterator_value(&iter));
         set_iterator_to_next(&iter);
     }
     printf("\n");
 }
 
 int main()
 {
     // Test 1: Průnik dvou množin
     struct TSet set1, set2, result;
     set_init(&set1);
     set_init(&set2);
     set_init(&result);
     
     // Naplnění první množiny
     printf("Filling set1 with elements: 1, 2, 3, 4, 5\n");
     set_insert(&set1, 1);
     set_insert(&set1, 2);
     set_insert(&set1, 3);
     set_insert(&set1, 4);
     set_insert(&set1, 5);
     print_set(&set1);
     
     // Naplnění druhé množiny
     printf("Filling set2 with elements: 3, 4, 5, 6, 7\n");
     set_insert(&set2, 3);
     set_insert(&set2, 4);
     set_insert(&set2, 5);
     set_insert(&set2, 6);
     set_insert(&set2, 7);
     print_set(&set2);
     
     // Otestování průniku množin
     printf("Testing set_intersection function...\n");
     if (set_intersection(&result, &set1, &set2))
     {
         printf("Intersection successful!\n");
         print_set(&result);
         printf("Expected result: 3, 4, 5\n");
     }
     else
     {
         printf("Intersection failed!\n");
     }
     
     // Test 2: Průnik s prázdnou množinou
     struct TSet empty, result2;
     set_init(&empty);
     set_init(&result2);
     
     printf("\nTesting intersection with empty set...\n");
     if (set_intersection(&result2, &set1, &empty))
     {
         printf("Intersection successful!\n");
         print_set(&result2);
         printf("Expected result: <empty set>\n");
     }
     else
     {
         printf("Intersection failed!\n");
     }
     
     // Test 3: Průnik dvou stejných množin
     struct TSet result3;
     set_init(&result3);
     
     printf("\nTesting intersection of a set with itself...\n");
     if (set_intersection(&result3, &set1, &set1))
     {
         printf("Intersection successful!\n");
         print_set(&result3);
         printf("Expected result: 1, 2, 3, 4, 5\n");
     }
     else
     {
         printf("Intersection failed!\n");
     }
     
     // Uvolnění paměti
     set_destroy(&set1);
     set_destroy(&set2);
     set_destroy(&empty);
     set_destroy(&result);
     set_destroy(&result2);
     set_destroy(&result3);
     
     printf("\nMemory statistics:\n");
     memory_stat();
     
     return 0;
 }