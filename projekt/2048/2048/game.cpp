#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "game.h"
#include "statistics.h"

int totalScore = 0;
char playerName[100];

//funkce pro zobrazeni menu
void showMenu() {
    system("cls");
    printf("***2048***\n");
    printf("Hlavni menu:\n");
    printf("1. Nova hra\n");
    if (fopen("savegame.txt", "r") != NULL) {
        printf("2. Pokracovat v ulozene hre\n");
    }
    printf("3. Statistiky\n");
    printf("4. Konec\n");
    printf("Vyberte volbu (1-4): ");
}
//funkce pro spusteni nove hry
void startNewGame(int isNewGame) {
    if (isNewGame) {
        while (1) {
            printf("\n\nZadejte sve jmeno: ");
            fgets(playerName, 100, stdin);
            playerName[strcspn(playerName, "\n")] = '\0';

            if (isNameTaken(playerName)) {
                printf("Jmeno '%s' je uz pouzito. Zadejte jine jmeno.\n", playerName);
                _sleep(1000);
            }
            else {
                break;  //unikatni jmeno, preruseni cyklu
            }
        }

        totalScore = 0; 
    }

    // inicializace hraci plochy
    int board[SIZE][SIZE] = { 0 };
    if (!isNewGame && loadGame(board)) {
        printf("Ulozena hra byla nactena. Pokracujeme...\n");
    }
    else {  // nova hra
        memset(board, 0, sizeof(board));
        addNewTile(board);
        addNewTile(board);
    }

    while (1) {
        printBoard(board);
        if (isBoardFull(board) && !hasValidMove(board)) {
            printf("Konec hry! Zadne mozne tahy.\n");
            saveStatistics(playerName, totalScore);
            system("pause");
            break;
        }

        printf("\nPouzivejte sipky k ovladani, ulozit pomoci 'S'");
        char input = getch();

        if (input == 0 || input == 224) {
            input = getch();
        }

        int success = 0;
        switch (input) {
        case 75:  // do leva
            success = moveLeft(board);
            totalScore++;
            break;
        case 77:  // do prava
            success = moveRight(board);
            totalScore++;
            break;
        case 72:  // nahoru
            success = moveUp(board);
            totalScore++;
            break;
        case 80:  // dolu
            success = moveDown(board);
            totalScore++;
            break;
        case 's':
        case 'S':
            saveGame(board);
            saveStatistics(playerName, totalScore);
            return;
        }

        addNewTile(board);

        saveGame(board);
        saveStatistics(playerName, totalScore);
    }
}
//funkce pro zobrazeni hraciho pole
void printBoard(int board[SIZE][SIZE]) {
    system("cls");
    printf("***2048***\n\n");
    printf("Hrac: %s\n", playerName);
    printf("\nSkore: %d\n", totalScore);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                printf(".\t");
            else
                printf("%d\t", board[i][j]);
        }
        printf("\n");
    }
}
//funkce pro pridavani novych cisel na policka
void addNewTile(int board[SIZE][SIZE]) {
    int emptyTiles[SIZE * SIZE][2];
    int emptyCount = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[emptyCount][0] = i;
                emptyTiles[emptyCount][1] = j;
                emptyCount++;
            }
        }
    }

    if (emptyCount > 0) {
        int randomTile = rand() % emptyCount;
        int x = emptyTiles[randomTile][0];
        int y = emptyTiles[randomTile][1];
        board[x][y] = (rand() % 10 == 0) ? 4 : 2; // 90% sance pro spawnuti 2, 10% sance pro 4
    }
}
//funkce pro posunuti do leva
int moveLeft(int board[SIZE][SIZE]) {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 1; j < SIZE; j++) {
            if (board[i][j] != 0) {
                int k = j;
                while (k > 0 && board[i][k - 1] == 0) {
                    board[i][k - 1] = board[i][k];
                    board[i][k] = 0;
                    k--;
                    moved = 1;
                }
                if (k > 0 && board[i][k - 1] == board[i][k]) {
                    board[i][k - 1] *= 2;
                    board[i][k] = 0;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}
//funkce pro posunuti do prava
int moveRight(int board[SIZE][SIZE]) {
    int moved = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = SIZE - 2; j >= 0; j--) {
            if (board[i][j] != 0) {
                int k = j;
                while (k < SIZE - 1 && board[i][k + 1] == 0) {
                    board[i][k + 1] = board[i][k];
                    board[i][k] = 0;
                    k++;
                    moved = 1;
                }
                if (k < SIZE - 1 && board[i][k + 1] == board[i][k]) {
                    board[i][k + 1] *= 2;
                    board[i][k] = 0;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}
//funkce pro posunuti nahoru
int moveUp(int board[SIZE][SIZE]) {
    int moved = 0;
    for (int j = 0; j < SIZE; j++) {
        for (int i = 1; i < SIZE; i++) {
            if (board[i][j] != 0) {
                int k = i;
                while (k > 0 && board[k - 1][j] == 0) {
                    board[k - 1][j] = board[k][j];
                    board[k][j] = 0;
                    k--;
                    moved = 1;
                }
                if (k > 0 && board[k - 1][j] == board[k][j]) {
                    board[k - 1][j] *= 2;
                    board[k][j] = 0;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}
//funkce pro posunuti dolu
int moveDown(int board[SIZE][SIZE]) {
    int moved = 0;
    for (int j = 0; j < SIZE; j++) {
        for (int i = SIZE - 2; i >= 0; i--) {
            if (board[i][j] != 0) {
                int k = i;
                while (k < SIZE - 1 && board[k + 1][j] == 0) {
                    board[k + 1][j] = board[k][j];
                    board[k][j] = 0;
                    k++;
                    moved = 1;
                }
                if (k < SIZE - 1 && board[k + 1][j] == board[k][j]) {
                    board[k + 1][j] *= 2;
                    board[k][j] = 0;
                    moved = 1;
                }
            }
        }
    }
    return moved;
}
//funkce pro zjisteni zda je plna hraci plocha
int isBoardFull(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}
//funkce na kontrolu zda jsou mozne dalsi tahy
int hasValidMove(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) return 1;
            if (i > 0 && board[i][j] == board[i - 1][j]) return 1;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j]) return 1;
            if (j > 0 && board[i][j] == board[i][j - 1]) return 1;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1]) return 1;
        }
    }
    return 0;
}
//funkce pro ulozeni jmena a skore hrace
void saveGame(int board[SIZE][SIZE]) {
    FILE* file = fopen("savegame.txt", "w");
    if (file != NULL) {
        fprintf(file, "%s\n", playerName);   // Uložíme jméno hráèe
        fprintf(file, "%d\n", totalScore);   // Uložíme skóre

        // Uložení herní desky
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fprintf(file, "%d ", board[i][j]);
            }
            fprintf(file, "\n");
        }
        fclose(file);
    }
}
//funkce pro nacteni posledni hry ze souboru
int loadGame(int board[SIZE][SIZE]) {
    FILE* file = fopen("savegame.txt", "r");
    if (file != NULL) {

        // Naètení jména hráèe a skóre
        fgets(playerName, 100, file);
        playerName[strcspn(playerName, "\n")] = '\0';  // odstraní se nový øádek, který je po jménu

        fscanf(file, "%d\n", &totalScore);

        // Naètení herní desky
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, "%d", &board[i][j]);
            }
        }
        fclose(file);
        return 1; 
    }
    return 0;
}

//funkce na zjisteni zda existuje zadane jmeno
int isNameTaken(const char* name) {
    FILE* file = fopen("statistics.txt", "r");
    if (file != NULL) {
        char line[150];
        while (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ",");
            if (token != NULL) {
                if (strcmp(name, token) == 0) {
                    fclose(file);
                    return 1;
                }
            }
        }
        fclose(file);
    }
    return 0;
}