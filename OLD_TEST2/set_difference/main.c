/**
 * @file set_difference_test.c
 * @brief Testovací program pro funkci set_difference
 * @author Claude
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include "TSet.h"
 
 // Testovací funkce pro set_difference
 void test_set_difference_example1() {
     struct TSet set1, set2, set3;
     set_init(&set1);
     set_init(&set2);
     set_init(&set3);
     
     // Naplnění set1
     TSetElement set1_values[] = {1, 2, 3, 4, 5};
     for (size_t i = 0; i < sizeof(set1_values) / sizeof(TSetElement); i++) {
         set_insert(&set1, set1_values[i]);
     }
     
     // Naplnění set2
     TSetElement set2_values[] = {-1, 1, 4, 5, 6, 7, 8};
     for (size_t i = 0; i < sizeof(set2_values) / sizeof(TSetElement); i++) {
         set_insert(&set2, set2_values[i]);
     }
     
     // Provedení operace rozdílu
     bool result = set_difference(&set3, &set1, &set2);
     assert(result);
     
     // Očekávaný výsledek: {2, 3}
     assert(set_size(&set3) == 2);
     assert(set_is_element_of(&set3, 2));
     assert(set_is_element_of(&set3, 3));
     assert(!set_is_element_of(&set3, 1));
     assert(!set_is_element_of(&set3, 4));
     assert(!set_is_element_of(&set3, 5));
     
     printf("Test 1: OK\n");
     
     // Uvolnění paměti
     set_destroy(&set1);
     set_destroy(&set2);
     set_destroy(&set3);
 }
 
 void test_set_difference_example2() {
     struct TSet set1, set2, set3;
     set_init(&set1);
     set_init(&set2);
     set_init(&set3);
     
     // Naplnění set1
     TSetElement set1_values[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
     for (size_t i = 0; i < sizeof(set1_values) / sizeof(TSetElement); i++) {
         set_insert(&set1, set1_values[i]);
     }
     
     // Naplnění set2
     TSetElement set2_values[] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18};
     for (size_t i = 0; i < sizeof(set2_values) / sizeof(TSetElement); i++) {
         set_insert(&set2, set2_values[i]);
     }
     
     // Provedení operace rozdílu
     bool result = set_difference(&set3, &set1, &set2);
     assert(result);
     
     // Očekávaný výsledek: {1, 3, 5, 7, 9}
     assert(set_size(&set3) == 5);
     assert(set_is_element_of(&set3, 1));
     assert(set_is_element_of(&set3, 3));
     assert(set_is_element_of(&set3, 5));
     assert(set_is_element_of(&set3, 7));
     assert(set_is_element_of(&set3, 9));
     assert(!set_is_element_of(&set3, 0));
     assert(!set_is_element_of(&set3, 2));
     assert(!set_is_element_of(&set3, 4));
     assert(!set_is_element_of(&set3, 6));
     assert(!set_is_element_of(&set3, 8));
     
     printf("Test 2: OK\n");
     
     // Uvolnění paměti
     set_destroy(&set1);
     set_destroy(&set2);
     set_destroy(&set3);
 }
 
 void test_edge_cases() {
     struct TSet set1, set2, set3;
     set_init(&set1);
     set_init(&set2);
     set_init(&set3);
     
     // Test: Prázdné množiny
     bool result = set_difference(&set3, &set1, &set2);
     assert(result);
     assert(set_size(&set3) == 0);
     
     // Test: NULL vstupy
     result = set_difference(&set3, NULL, &set2);
     assert(result);
     assert(set_size(&set3) == 0);
     
     result = set_difference(&set3, &set1, NULL);
     assert(result);
     assert(set_size(&set3) == 0);
     
     // Test: NULL výstup
     result = set_difference(NULL, &set1, &set2);
     assert(!result);
     
     // Naplnění set1
     for (long long i = 1; i <= 5; i++) {
         set_insert(&set1, i);
     }
     
     // Test: Rozdíl s prázdnou množinou (výsledek by měl být totožný s první množinou)
     result = set_difference(&set3, &set1, &set2);
     assert(result);
     assert(set_size(&set3) == 5);
     for (long long i = 1; i <= 5; i++) {
         assert(set_is_element_of(&set3, i));
     }
     
     // Naplnění set2 úplně stejnými prvky jako set1
     for (long long i = 1; i <= 5; i++) {
         set_insert(&set2, i);
     }
     
     // Test: Rozdíl dvou identických množin (výsledek by měl být prázdná množina)
     set_destroy(&set3);
     set_init(&set3);
     result = set_difference(&set3, &set1, &set2);
     assert(result);
     assert(set_size(&set3) == 0);
     
     printf("Test 3 (Edge cases): OK\n");
     
     // Uvolnění paměti
     set_destroy(&set1);
     set_destroy(&set2);
     set_destroy(&set3);
 }
 
 int main() {
     printf("Spouštím testy pro funkci set_difference...\n");
     
     // Spuštění testů
     test_set_difference_example1();
     test_set_difference_example2();
     test_edge_cases();
     
     printf("Všechny testy proběhly úspěšně!\n");
     return 0;
 }