/**
 * @file fsa.h
 * @brief Hlavičkový soubor pro implementaci konečného stavového automatu pro korekci textu
 * @author Claude
 */

 #ifndef FSA_H
 #define FSA_H
 
 #include <stdio.h>
 #include <stdbool.h>
 
 /**
  * @brief Stavy konečného automatu
  */
 typedef enum {
     SENTENCE,        // Stav pro normální text ve větě
     DOT,             // Stav po detekci tečky
     SPACE_AFTER_DOT  // Stav po detekci mezery za tečkou
 } TState;
 
 /**
  * @brief Zpracuje text ze vstupního souboru a uloží korigovaný text do výstupního souboru
  * @param input_file Ukazatel na vstupní soubor
  * @param output_file Ukazatel na výstupní soubor
  * @return 0 při úspěšném zpracování, jinak kód chyby
  */
 int process_text(FILE *input_file, FILE *output_file);
 
 /**
  * @brief Zjistí, zda je znak velké písmeno ASCII tabulky
  * @param c Znak ke kontrole
  * @return true pokud je znak velké písmeno, jinak false
  */
 bool isUpper(int c);
 
 /**
  * @brief Zjistí, zda je znak malé písmeno ASCII tabulky
  * @param c Znak ke kontrole
  * @return true pokud je znak malé písmeno, jinak false
  */
 bool isLower(int c);
 
 /**
  * @brief Zjistí, zda je znak písmeno ASCII tabulky
  * @param c Znak ke kontrole
  * @return true pokud je znak písmeno, jinak false
  */
 bool isAlpha(int c);
 
 /**
  * @brief Zjistí, zda je znak tečka
  * @param c Znak ke kontrole
  * @return true pokud je znak tečka, jinak false
  */
 bool isDot(int c);
 
 /**
  * @brief Zjistí, zda je znak mezera nebo jiný bílý znak
  * @param c Znak ke kontrole
  * @return true pokud je znak mezera nebo jiný bílý znak, jinak false
  */
 bool isWhitespace(int c);
 
 /**
  * @brief Převede znak na velké písmeno, pokud je to písmeno
  * @param c Znak k převodu
  * @return Velké písmeno nebo původní znak, pokud to není písmeno
  */
 int toUpper(int c);
 
 /**
  * @brief Převede znak na malé písmeno, pokud je to písmeno
  * @param c Znak k převodu
  * @return Malé písmeno nebo původní znak, pokud to není písmeno
  */
 int toLower(int c);
 
 #endif /* FSA_H */