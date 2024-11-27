#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "game.h"
#include "statistics.h"

int main() {
    srand(time(NULL));

    while (1) {
        showMenu();
        char choice = getch();
        switch (choice) {
        case '1':  // Nová hra
            startNewGame(1);  // 1 = Nová hra (ptá se na jméno)
            break;
        case '2':  // Pokračování
            if (fopen("savegame.txt", "r") != NULL) {
                startNewGame(0);  // 0 = Pokračování (neptá se na jméno)
            }
            else {
                printf("Zadna ulozena hra nebyla nalezena.\n");
                system("pause");
            }
            break;
        case '3':  // Statistiky
            showStatistics();
            break;
        case '4':  // Konec
            printf("Konec hry.\n");
            saveStatistics(playerName, totalScore);
            return 0;
        }
    }
}