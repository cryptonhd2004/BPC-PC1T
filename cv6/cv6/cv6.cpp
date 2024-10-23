#include "cv6.h"
#include <stdio.h>
#include <ctype.h> 


int pocetPismen(const char* text) {
    int count = 0;
    while (*text) {
        if (isalpha(*text)) {
            count++;
        }
        text++;
    }
    return count;
}

int pocetCislic(const char* text) {
    int count = 0;
    while (*text) {
        if (isdigit(*text)) {
            count++;
        }
        text++;
    }
    return count;
}
int maxDelkaSlova(const char* text) {
    int maxDelka = 0;
    int aktualniDelka = 0;
    while (*text) {
        if (isalpha(*text)) {
            aktualniDelka++;
        }
        else {
            if (aktualniDelka > maxDelka) {
                maxDelka = aktualniDelka;
            }
            aktualniDelka = 0; 
        }
        text++;
    }
    return maxDelka;
   }
    
int main() {
    char text[] = "Toto jsou 2 vzorove vety, ktere budou zpracovavany Vasemi funkcemi. Auto Hyundai ix35 ma pres 120 konskych sil.";
    int pismena = pocetPismen(text);
    int cislice = pocetCislic(text);
    int delka = maxDelkaSlova(text);
    printf("Statistiky textu:\n%s\n\n", text);
    printf("Pocet pismen v textu: %d\n", pismena);
    printf("Pocet cislic v textu: %d\n", cislice);
    printf("Nejvetsi delka slova: %d\n", delka);
    return 0;
}