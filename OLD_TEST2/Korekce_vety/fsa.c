/**
 * @file fsa.c
 * @brief Implementace konečného stavového automatu pro korekci textu
 * @author Claude
 */

 #include "fsa.h"

 /**
  * @brief Zpracovává znak podle aktuálního stavu automatu a aktualizuje stav
  * @param state Ukazatel na aktuální stav automatu
  * @param c Zpracovávaný znak
  * @param output_file Výstupní soubor pro zápis
  */
 static void process_char(TState *state, int c, FILE *output_file) {
     switch (*state) {
         case SENTENCE:
             // Na začátku věty - první písmeno velké, ostatní malá
             if (isAlpha(c)) {
                 fputc(toUpper(c), output_file);
                 *state = SENTENCE;
             } else if (isDot(c)) {
                 fputc('.', output_file);
                 *state = DOT;
             } else if (isWhitespace(c)) {
                 fputc(' ', output_file);
                 *state = SENTENCE;
             } else {
                 fputc(c, output_file);
                 *state = SENTENCE;
             }
             break;
 
         case DOT:
             // Po tečce musí následovat mezera
             if (isWhitespace(c)) {
                 fputc(' ', output_file);
                 *state = SPACE_AFTER_DOT;
             } else if (isAlpha(c)) {
                 // Pokud po tečce následuje písmeno, přidáme mezeru a pak písmeno (velké)
                 fputc(' ', output_file);
                 fputc(toUpper(c), output_file);
                 *state = SENTENCE;
             } else if (isDot(c)) {
                 // Více teček za sebou - necháme tak jak je
                 fputc('.', output_file);
                 *state = DOT;
             } else {
                 fputc(c, output_file);
                 *state = DOT;
             }
             break;
 
         case SPACE_AFTER_DOT:
             // Po mezeře za tečkou - začíná nová věta
             if (isAlpha(c)) {
                 fputc(toUpper(c), output_file);
                 *state = SENTENCE;
             } else if (isDot(c)) {
                 fputc('.', output_file);
                 *state = DOT;
             } else if (isWhitespace(c)) {
                 // Další mezera - ignorujeme (mezery nemají následovat po mezere)
                 *state = SPACE_AFTER_DOT;
             } else {
                 fputc(c, output_file);
                 *state = SENTENCE;
             }
             break;
     }
 }
 
 int process_text(FILE *input_file, FILE *output_file) {
     int c;
     TState state = SENTENCE;
 
     while ((c = fgetc(input_file)) != EOF) {
         // Pokud není začátek věty, převedeme písmena na malá
         if (state == SENTENCE && !isWhitespace(c) && !isDot(c)) {
             if (isAlpha(c)) {
                 c = toLower(c);
             }
         }
 
         process_char(&state, c, output_file);
     }
 
     return 0;
 }
 
 bool isUpper(int c) {
     return c >= 'A' && c <= 'Z';
 }
 
 bool isLower(int c) {
     return c >= 'a' && c <= 'z';
 }
 
 bool isAlpha(int c) {
     return isUpper(c) || isLower(c);
 }
 
 bool isDot(int c) {
     return c == '.';
 }
 
 bool isWhitespace(int c) {
     return c == ' ' || c == '\t' || c == '\n' || c == '\r';
 }
 
 int toUpper(int c) {
     if (isLower(c)) {
         return c - ('a' - 'A');
     }
     return c;
 }
 
 int toLower(int c) {
     if (isUpper(c)) {
         return c + ('a' - 'A');
     }
     return c;
 }