#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

void printBoard(int board[SIZE][SIZE]) {
    system("cls");
    printf("\n");
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

int moveUp(int board[SIZE][SIZE]) {
    rotateBoard(board);
    int success = moveLeft(board);
    rotateBoard(board);
    rotateBoard(board);
    rotateBoard(board);
    return success;
}

int moveRight(int board[SIZE][SIZE]) {
    rotateBoard(board);
    rotateBoard(board);
    int success = moveLeft(board);
    rotateBoard(board);
    rotateBoard(board);
    return success;
}

int moveDown(int board[SIZE][SIZE]) {
    rotateBoard(board);
    rotateBoard(board);
    rotateBoard(board);
    int success = moveLeft(board);
    rotateBoard(board);
    return success;
}

int canMove(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0)
                return 1;
            if (j < SIZE - 1 && board[i][j] == board[i][j + 1])
                return 1;
            if (i < SIZE - 1 && board[i][j] == board[i + 1][j])
                return 1;
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int board[SIZE][SIZE] = { 0 };
    addNewTile(board);
    addNewTile(board);

    char input;
    int success;

    while (1) {
        printBoard(board);

        if (!canMove(board)) {
            printf("Game Over!\n");
            break;
        }

        printf("Pohyb hrou (WASD): ");
        scanf(" %c", &input);

        success = 0; // Reset success for each move attempt

        switch (input) {
        case 'a':
        case 'A':
            success = moveLeft(board);
            addNewTile(board);
            break;
        case 'd':
        case 'D':
            success = moveRight(board);
            addNewTile(board);
            break;
        case 'w':
        case 'W':
            success = moveDown(board);
            addNewTile(board);
            break;
        case 's':
        case 'S':
            success = moveUp(board);
            addNewTile(board);
            break;
        default:
            printf("Invalid input!\n");
        }

        //if (success != 0) {
           // addNewTile(board); // Add new tile only if there was a successful move
        //}
    }

    return 0;
}