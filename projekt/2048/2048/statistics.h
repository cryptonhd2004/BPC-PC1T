#pragma once

// Deklarace funkci
#define MAX_PLAYERS 100

typedef struct {
    char name[100];
    int score;
} Player;

void saveStatistics(const char* playerName, int score);
void showStatistics();