/**
 * @file main.c
 * @brief Implementace programu pro korekci textu pomocí konečného stavového automatu
 * @author Claude
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 #include "fsa.h"
 
 /**
  * @brief Hlavní funkce programu, která načítá vstupní soubor a vytváří výstupní soubor s korigovaným textem
  * @param argc Počet argumentů příkazové řádky
  * @param argv Pole argumentů příkazové řádky
  * @return 0 při úspěšném provedení, jinak kód chyby
  */
 int main(int argc, char *argv[]) {
     // Kontrola počtu argumentů - potřebujeme dva soubory (vstupní a výstupní)
     if (argc != 3) {
         fprintf(stderr, "Chyba: Nesprávný počet argumentů\n");
         fprintf(stderr, "Použití: %s vstupni_soubor vystupni_soubor\n", argv[0]);
         return 1;
     }
 
     // Otevření vstupního souboru pro čtení
     FILE *input_file = fopen(argv[1], "r");
     if (input_file == NULL) {
         fprintf(stderr, "Chyba: Nelze otevřít vstupní soubor '%s'\n", argv[1]);
         return 2;
     }
 
     // Otevření výstupního souboru pro zápis
     FILE *output_file = fopen(argv[2], "w");
     if (output_file == NULL) {
         fprintf(stderr, "Chyba: Nelze otevřít výstupní soubor '%s'\n", argv[2]);
         fclose(input_file);
         return 3;
     }
 
     // Volání funkce pro zpracování textu pomocí konečného stavového automatu
     int result = process_text(input_file, output_file);
 
     // Uzavření souborů
     fclose(input_file);
     fclose(output_file);
 
     // Vrátíme výsledek zpracování
     return result;
 }