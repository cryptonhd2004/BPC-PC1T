#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "statistics.h"

void saveStatistics(const char* playerName, int totalScore) {
    FILE* file = fopen("statistics.txt", "a+");  // otevre soubor pro pripsani (ne prepsani)
    if (file != NULL) {
        char line[150];

        char tempNames[1000][100];
        int tempScores[1000];
        int count = 0;
        int found = 0;

        // precte vsechny zaznamy
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

        // kdyz existuje hrac, tak se jen prepise jeho skore
        for (int i = 0; i < count; i++) {
            if (strcmp(playerName, tempNames[i]) == 0) {
                tempScores[i] = totalScore;
                found = 1;
                break;
            }
        }

        // kdyz je jiny hrac nez existuje prida se zaznam
        if (!found) {
            strcpy(tempNames[count], playerName);
            tempScores[count] = totalScore;
            count++;
        }

        // Sort the records by score in descending order (bubble sort or any other sorting algorithm)
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (tempScores[j] < tempScores[j + 1]) {
                    // prohozeni skore
                    int tempScore = tempScores[j];
                    tempScores[j] = tempScores[j + 1];
                    tempScores[j + 1] = tempScore;

                    // prohozeni jmen
                    char tempName[100];
                    strcpy(tempName, tempNames[j]);
                    strcpy(tempNames[j], tempNames[j + 1]);
                    strcpy(tempNames[j + 1], tempName);
                }
            }
        }

        // Prepise statistiky
        freopen("statistics.txt", "w", file);  // Znovu otevre pro zapsani
        for (int i = 0; i < count; i++) {
            fprintf(file, "%s,%d\n", tempNames[i], tempScores[i]);
        }

        fclose(file);
    }
}

//Funkce na vypis statistik (max 10)
void showStatistics() {
    FILE* file = fopen("statistics.txt", "r");
    if (file == NULL) {
        printf("No statistics available.\n");
        return;
    }
    system("cls");
    printf("*** 2048 ***\n");
    printf("\nTop 10 hracu a jejich skore:\n\n");

    char line[150];
    int count = 0;

    // Naèítání a výpis maximálnì 10 hracu
    while (fgets(line, sizeof(line), file) && count < 10) {
        char* token = strtok(line, ",");  // Jméno hráèe
        if (token != NULL) {
            char playerName[100];
            strncpy(playerName, token, sizeof(playerName) - 1);
            playerName[sizeof(playerName) - 1] = '\0';

            token = strtok(NULL, ",");
            if (token != NULL) {
                int score = atoi(token);
                printf("%s : %d\n", playerName, score);  // Výpis ve formátu "Hráè : Skóre"
                count++;
            }
        }
    }
    fclose(file);
    system("pause");
}