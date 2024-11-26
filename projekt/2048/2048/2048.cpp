#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>  // For _kbhit() and getch()
#include <string.h>

#define SIZE 4

// Globální proměnné pro uchování statistik
int gamesPlayed = 0;
int gamesWon = 0;
int totalScore = 0;
char playerName[100];  // Pro uchování jména hráče

void saveStatistics() {
    FILE* file = fopen("statistics.txt", "a"); // Otevře soubor v režimu přidání
    if (file != NULL) {
        fprintf(file, "%s,%d\n", playerName, totalScore);
        fclose(file);
    }
}

void loadStatisticsAndSort(char topPlayers[10][100], int topScores[10], int* playerCount) {
    FILE* file = fopen("statistics.txt", "r");
    if (file != NULL) {
        char line[150];
        char tempNames[1000][100];
        int tempScores[1000];
        int count = 0;

        // Načti všechny záznamy
        while (fgets(line, sizeof(line), file)) {
            char* token = strtok(line, ",");
            if (token != NULL) {
                strncpy(tempNames[count], token, sizeof(tempNames[count]) - 1);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    tempScores[count] = atoi(token);
                    count++;
                }
            }
        }
        fclose(file);

        // Seřaď záznamy sestupně podle skóre (jednoduché řazení Bubble Sort)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (tempScores[j] < tempScores[j + 1]) {
                    int tempScore = tempScores[j];
                    tempScores[j] = tempScores[j + 1];
                    tempScores[j + 1] = tempScore;

                    char tempName[100];
                    strcpy(tempName, tempNames[j]);
                    strcpy(tempNames[j], tempNames[j + 1]);
                    strcpy(tempNames[j + 1], tempName);
                }
            }
        }

        // Zkopíruj 10 nejlepších hráčů
        *playerCount = (count < 10) ? count : 10;
        for (int i = 0; i < *playerCount; i++) {
            strcpy(topPlayers[i], tempNames[i]);
            topScores[i] = tempScores[i];
        }
    }
}

void showStatistics() {
    system("cls");

    char topPlayers[10][100];
    int topScores[10];
    int playerCount = 0;

    loadStatisticsAndSort(topPlayers, topScores, &playerCount);

    printf("Statistiky - Top 10 hracu:\n");
    for (int i = 0; i < playerCount; i++) {
        printf("%d. %s - %d\n", i + 1, topPlayers[i], topScores[i]);
    }

    printf("\nStisknete libovolnou klavesu pro navrat do menu.");
    getch();
}




void printBoard(int board[SIZE][SIZE]) {
    system("cls");
    printf("\n");
    printf("Player: %s\n", playerName);
    printf("Current Score: %d\n", totalScore);
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
        board[x][y] = (rand() % 10 == 0) ? 4 : 2; // 90% chance for 2, 10% chance for 4
    }
}

void slideArray(int row[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (row[i] == 0) {
            for (int j = i + 1; j < SIZE; j++) {
                if (row[j] != 0) {
                    row[i] = row[j];
                    row[j] = 0;
                    break;
                }
            }
        }
    }
}

int combineArray(int row[SIZE]) {
    int success = 0;
    for (int i = 0; i < SIZE - 1; i++) {
        if (row[i] != 0 && row[i] == row[i + 1]) {
            row[i] *= 2;
            row[i + 1] = 0;
            success = 1;
            slideArray(row); // Slide after combine
        }
    }
    return success;
}

int moveLeft(int board[SIZE][SIZE]) {
    int success = 0;
    for (int i = 0; i < SIZE; i++) {
        int temp[SIZE] = { 0 };
        for (int j = 0; j < SIZE; j++) {
            temp[j] = board[i][j];
        }

        slideArray(temp);
        success |= combineArray(temp);
        slideArray(temp);

        for (int j = 0; j < SIZE; j++) {
            board[i][j] = temp[j];
        }
    }
    return success;
}

int moveUp(int board[SIZE][SIZE]) {
    int success = 0;
    for (int j = 0; j < SIZE; j++) {
        int temp[SIZE] = { 0 };

        // Copy column into temp array
        for (int i = 0; i < SIZE; i++) {
            temp[i] = board[i][j];
        }

        slideArray(temp);
        success |= combineArray(temp);
        slideArray(temp);

        // Copy back to the board
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = temp[i];
        }
    }
    return success;
}

int moveDown(int board[SIZE][SIZE]) {
    int success = 0;
    for (int j = 0; j < SIZE; j++) {
        int temp[SIZE] = { 0 };

        // Copy column into temp array
        for (int i = 0; i < SIZE; i++) {
            temp[i] = board[i][j];
        }

        // Reverse the array for moving down
        for (int i = 0; i < SIZE / 2; i++) {
            int t = temp[i];
            temp[i] = temp[SIZE - i - 1];
            temp[SIZE - i - 1] = t;
        }

        slideArray(temp);
        success |= combineArray(temp);
        slideArray(temp);

        // Reverse back the array after combining
        for (int i = 0; i < SIZE / 2; i++) {
            int t = temp[i];
            temp[i] = temp[SIZE - i - 1];
            temp[SIZE - i - 1] = t;
        }

        // Copy back to the board
        for (int i = 0; i < SIZE; i++) {
            board[i][j] = temp[i];
        }
    }
    return success;
}

void rotateBoard(int board[SIZE][SIZE]) {
    int temp[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            temp[i][j] = board[i][j];
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = temp[SIZE - j - 1][i];
        }
    }
}

int moveRight(int board[SIZE][SIZE]) {
    rotateBoard(board);
    rotateBoard(board);
    int success = moveLeft(board);
    rotateBoard(board);
    rotateBoard(board);
    return success;
}

int isBoardFull(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                return 0;  // Found an empty tile
        }
    }
    return 1;  // Board is full
}

int hasValidMove(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                return 1;  // There is an empty tile, so a move is possible
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j])
                return 1;  // Vertical merge is possible
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1])
                return 1;  // Horizontal merge is possible
        }
    }
    return 0;  // No valid move left
}

int checkWin(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 2048) {
                return 1;  // Player wins
            }
        }
    }
    return 0;  // No win yet
}

void showMenu() {
    system("cls");
    printf("Hlavni menu:\n");
    printf("1. Nova hra\n");
    if (fopen("savegame.txt", "r") != NULL) {
        printf("2. Pokracovat v ulozene hre\n");
    }
    printf("3. Statistiky\n");
    printf("4. Konec\n");
    printf("Vyberte volbu (1-4): ");
}


void saveGame(int board[SIZE][SIZE]) {
    FILE* file = fopen("savegame.txt", "w");
    if (file != NULL) {
        // Uložíme hrací desku
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fprintf(file, "%d ", board[i][j]);
            }
            fprintf(file, "\n");
        }

        // Uložíme statistiky
        fprintf(file, "%s\n", playerName);
        fprintf(file, "%d %d %d\n", gamesPlayed, gamesWon, totalScore);
        fclose(file);
        printf("Hra byla ulozena.\n");
    }
    else {
        printf("Chyba pri ukladani hry!\n");
    }
}

int loadGame(int board[SIZE][SIZE]) {
    FILE* file = fopen("savegame.txt", "r");
    if (file != NULL) {
        // Načteme hrací desku
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (fscanf(file, "%d", &board[i][j]) != 1) {
                    fclose(file);
                    return 0; // Chyba při načítání
                }
            }
        }

        // Načteme statistiky
        fscanf(file, "%s", playerName);
        fscanf(file, "%d %d %d", &gamesPlayed, &gamesWon, &totalScore);
        fclose(file);
        return 1; // Úspěšně načteno
    }
    return 0; // Soubor neexistuje
}


void startNewGame(int isNewGame) {
    if (isNewGame) {  // Pokud je to nová hra
        printf("Zadejte sve jmeno: ");
        fgets(playerName, 100, stdin);
        playerName[strcspn(playerName, "\n")] = '\0';  // Odstraníme konec řádku
        totalScore = 0;  // Nastavíme skóre na 0
    }

    int board[SIZE][SIZE] = { 0 };
    if (!isNewGame && loadGame(board)) {  // Pokračování v uložené hře
        printf("Ulozena hra byla nactena. Pokracujeme...\n");
    }
    else {  // Nová hra
        memset(board, 0, sizeof(board));
        addNewTile(board);
        addNewTile(board);
    }

    while (1) {
        printBoard(board);

        if (isBoardFull(board) && !hasValidMove(board)) {
            printf("Game Over! No moves left and the board is full.\n");
            system("pause");
            gamesPlayed++;
            break;
        }

        printf("Use arrow keys (Up, Down, Left, Right) or press 'S' to save and quit: ");
        char input = getch();

        if (input == 0 || input == 224) {
            input = getch();
        }

        // Speciální vstup pro uložení hry
        if (input == 'S' || input == 's') {
            saveGame(board);
            saveStatistics();
            return; // Návrat do menu
        }

        int success = 0;
        switch (input) {
        case 75:  // Left arrow
            success = moveLeft(board);
            break;
        case 77:  // Right arrow
            success = moveRight(board);
            break;
        case 72:  // Up arrow
            success = moveUp(board);
            break;
        case 80:  // Down arrow
            success = moveDown(board);
            break;
        default:
            printf("Invalid input!\n");
            continue;
        }

        // Přidáme nový tile po každém tahu
        addNewTile(board);
        totalScore++;
    }
}


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
            saveStatistics();
            return 0;
        default:
            printf("Neplatna volba! Stisknete libovolnou klavesu pro opakovani.\n");
            getch();
        }
    }
}
