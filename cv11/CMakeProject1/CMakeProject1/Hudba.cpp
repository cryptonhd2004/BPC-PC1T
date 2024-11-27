#include <stdio.h>
#include <ctype.h>         
#include <stdlib.h>				
#include "HudbaDB.h"

struct t_HudbaDB* prvni = NULL; 

void OnAdd() {
    char my_interpret[INTERPRET_SIZE];
    char my_nazev_alba[NAZEV_ALBA_SIZE];
    int my_year;

    printf("\nInterpret: ");
    scanf_s("%[^\n]", my_interpret, INTERPRET_SIZE);
    while (getchar() != '\n');

    printf("\nNazev alba: ");
    scanf_s("%[^\n]", my_nazev_alba, NAZEV_ALBA_SIZE);
    while (getchar() != '\n');

    printf("\nRok vydani: ");
    scanf_s("%d", &my_year);
    while (getchar() != '\n');

    add(my_interpret, my_nazev_alba, my_year, &prvni); 
}

void OnDel() {
    int my_year;

    printf("\nRok vydani k odstraneni: ");
    scanf_s("%d", &my_year);
    while (getchar() != '\n');

    del(my_year, &prvni); 
}

int main() {
    add("The Prodigy", "Invaders Must Die", 2009, &prvni);
    add("Linkin Park", "Meteora", 2003, &prvni);
    add("Linkin Park", "Hybrid Theory", 2000, &prvni);
    add("AC/DC", "Highway to Hell", 1979, &prvni);
    add("Pendulum", "Immersion", 2010, &prvni);

    char cmd;

    do {
        system("cls");
        printf("A: Pridat      ");
        printf("D: Smazat      ");
        printf("P: Tisk     ");
        printf("X: Hledej   ");
        printf("Q: Konec\n\n");

        cmd = tolower(getchar());
        while (getchar() != '\n');

        switch (cmd) {
        case 'a':
            OnAdd();
            break;
        case 'd':
            OnDel();
            break;
        case 'p':
            vypisSeznam(prvni);
            system("pause>nul");
            break;
        case 'x':
            vypisSeznamPodlePismena(prvni); 
            system("pause>nul");
            break;
        }
    } while (cmd != 'q'); 

    return 0;
}