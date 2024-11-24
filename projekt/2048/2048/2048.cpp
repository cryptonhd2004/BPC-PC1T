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
    FILE* file = fopen("statistics.txt", "w");
    if (file != NULL) {
        fprintf(file, "Player Name: %s\n", playerName);
        fprintf(file, "Games Played: %d\n", gamesPlayed);
        fprintf(file, "Games Won: %d\n", gamesWon);
        fprintf(file, "Total Score: %d\n", totalScore);
        fclose(file);
    }
}

void loadStatistics() {
    FILE* file = fopen("statistics.txt", "r");
    if (file != NULL) {
        fscanf(file, "Player Name: %s\n", playerName);
        fscanf(file, "Games Played: %d\n", &gamesPlayed);
        fscanf(file, "Games Won: %d\n", &gamesWon);
        fscanf(file, "Total Score: %d\n", &totalScore);
        fclose(file);
    }
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
    printf("2. Statistiky\n");
    printf("3. Konec\n");
    printf("Vyberte volbu (1-3): ");
}

void startNewGame() {
    printf("Zadejte sve jmeno: ");
    fgets(playerName, 100, stdin);
    playerName[strcspn(playerName, "\n")] = '\0';  // Remove trailing newline character

    int board[SIZE][SIZE] = { 0 };
    addNewTile(board);
    addNewTile(board);

    while (1) {
        printBoard(board);

        if (isBoardFull(board) && !hasValidMove(board)) {
            printf("Game Over! No moves left and the board is full.\n");
            system("pause");
            gamesPlayed++;
            break;
        }

        printf("Use arrow keys (Up, Down, Left, Right): ");
        char input = getch();

        if (input == 0 || input == 224) {
            input = getch();
        }

        // Zkopírujeme aktuální stav desky před pohybem
        int oldBoard[SIZE][SIZE];
        memcpy(oldBoard, board, sizeof(board));

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
        }

        // Porovnáme desku před a po tahu
        if (memcmp(oldBoard, board, sizeof(board)) != 0) {
            addNewTile(board);  // Přidáme nový tile pouze při změně na desce
            totalScore++;       // Zvyšíme skóre za tah
        }
    }
}
void showStatistics() {
    system("cls");
    printf("Statistiky:\n");
    printf("Hrac: %s\n", playerName);
    printf("Hracich her: %d\n", gamesPlayed);
    printf("Vyhranych her: %d\n", gamesWon);
    printf("Celkovy score: %d\n", totalScore);
    printf("\nStisknete libovolnou klavesu pro navrat do menu.");
    getch();
}

int main() {
    srand(time(NULL));

    loadStatistics();

    while (1) {
        showMenu();
        char choice = getch();
        switch (choice) {
        case '1':  // New game
            startNewGame();
            break;
        case '2':  // Show statistics
            showStatistics();
            break;
        case '3':  // Exit
            printf("Konec hry.\n");
            saveStatistics();
            return 0;
        default:
            printf("Neplatna volba! Stisknete libovolnou klavesu pro opakovani.\n");
            getch();
        }
    }
}
