#include "cv10.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

// Funkce pro počítání písmen v textu
int pocetPismen(const char* text) {
    int count = 0;
    while (*text) {
        // Před použitím funkce isalpha se ujistíme, že je znak platný (char)
        if (isalpha((unsigned char)*text)) {
            count++;
        }
        text++;
    }
    return count;
}

// Funkce pro počítání číslic v textu
int pocetCislic(const char* text) {
    int count = 0;
    while (*text) {
        // Před použitím funkce isdigit se ujistíme, že je znak platný (char)
        if (isdigit((unsigned char)*text)) {
            count++;
        }
        text++;
    }
    return count;
}

// Funkce pro počítání slov v textu
int pocetSlov(const char* text) {
    int count = 0;
    bool vnitrniSlovo = false;  // Flag pro detekci začátku nového slova

    while (*text) {
        // Před použitím isalnum zkontrolujeme platnost znaku
        if (isalnum((unsigned char)*text)) {  // Pokud je znak alfanumerický
            if (!vnitrniSlovo) {
                count++;  // Začátek nového slova
                vnitrniSlovo = true;
            }
        }
        else {
            vnitrniSlovo = false;  // Konec slova (oddělení mezery nebo interpunkce)
        }
        text++;
    }

    return count;
}

// Funkce pro počítání vět v textu
int pocetVet(const char* text) {
    int count = 0;
    while (*text) {
        // Před použitím funkce na interpunkci kontrolujeme, že je platný znak
        if (*text == '.' || *text == '?' || *text == '!') {  // Konec věty
            count++;
        }
        text++;
    }
    return count;
}

int main() {
    const char* inputFile = "D:/vstup.txt";
    const char* outputFile = "D:/vysledky.txt";

    // Otevření souboru pro čtení
    FILE* input = fopen(inputFile, "r");
    if (input == NULL) {
        perror("Chyba při otevírání souboru");
        return 1;  // Ukončení programu, pokud došlo k chybě
    }

    // Zjištění délky souboru (abychom věděli, kolik paměti alokovat)
    fseek(input, 0, SEEK_END);
    long fileSize = ftell(input);
    fseek(input, 0, SEEK_SET);  // Vrátíme se na začátek souboru

    // Pokud je soubor prázdný, ukončíme program
    if (fileSize == 0) {
        printf("Soubor je prazdny.\n");
        fclose(input);
        return 0;
    }

    // Alokace paměti pro načtení celého souboru
    char* text = (char*)malloc(fileSize + 1);  // +1 pro nulový znak
    if (text == NULL) {
        perror("Chyba při alokaci paměti");
        fclose(input);
        return 1;
    }

    // Načtení souboru do textu
    fread(text, 1, fileSize, input);
    text[fileSize] = '\0';  // Přidání nulového znaku na konec řetězce

    // Zobrazíme obsah textu pro diagnostiku
    printf("Načtený text:\n%s\n", text);

    // Počítání písmen, číslic, slov a vět
    int pismena = pocetPismen(text);
    int cislice = pocetCislic(text);
    int slova = pocetSlov(text);
    int vety = pocetVet(text);

    // Výpis výsledků
    printf("Počet písmen v textu: %d\n", pismena);
    printf("Počet číslic v textu: %d\n", cislice);
    printf("Počet slov v textu: %d\n", slova);
    printf("Počet vět v textu: %d\n", vety);

    // Uložení výsledků do souboru
    FILE* output = fopen(outputFile, "w");
    if (output == NULL) {
        perror("Chyba při otevírání souboru pro zápis");
        free(text);  // Uvolníme alokovanou paměť
        fclose(input);
        return 1;
    }

    fprintf(output, "Počet písmen v textu: %d\n", pismena);
    fprintf(output, "Počet číslic v textu: %d\n", cislice);
    fprintf(output, "Počet slov v textu: %d\n", slova);
    fprintf(output, "Počet vět v textu: %d\n", vety);

    // Zavření souborů a uvolnění paměti
    fclose(output);
    fclose(input);
    free(text);

    return 0;
}