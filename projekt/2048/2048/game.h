#pragma once

#define SIZE 4

extern int totalScore;
extern char playerName[100];

// Deklarace funkci
void showMenu();
void startNewGame(int isNewGame);
void printBoard(int board[SIZE][SIZE]);
void addNewTile(int board[SIZE][SIZE]);
int moveLeft(int board[SIZE][SIZE]);
int moveUp(int board[SIZE][SIZE]);
int moveDown(int board[SIZE][SIZE]);
int moveRight(int board[SIZE][SIZE]);
int isBoardFull(int board[SIZE][SIZE]);
int hasValidMove(int board[SIZE][SIZE]);
void saveGame(int board[SIZE][SIZE]);
int loadGame(int board[SIZE][SIZE]);
int isNameTaken(const char* name);