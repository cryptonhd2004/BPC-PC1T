#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "HudbaDB.h"

void add(const char* interpret, const char* nazev_alba, int rok_vydani, struct t_HudbaDB** uk_prvni) {
    struct t_HudbaDB* noveAlbum = (struct t_HudbaDB*)malloc(sizeof(struct t_HudbaDB));
    struct t_HudbaDB* aktAlbum;

    strcpy_s(noveAlbum->interpret, INTERPRET_SIZE, interpret);
    strcpy_s(noveAlbum->nazev_alba, NAZEV_ALBA_SIZE, nazev_alba);
    noveAlbum->rok_vydani = rok_vydani;
    noveAlbum->dalsi = NULL;

    if (*uk_prvni == NULL) {
        *uk_prvni = noveAlbum;
        return;
    }

    if (strcmp(noveAlbum->interpret, (*uk_prvni)->interpret) < 0) {
        noveAlbum->dalsi = *uk_prvni;
        *uk_prvni = noveAlbum;
        return;
    }

    aktAlbum = *uk_prvni;
    while (aktAlbum->dalsi) {
        if (strcmp(noveAlbum->interpret, aktAlbum->dalsi->interpret) < 0) {
            noveAlbum->dalsi = aktAlbum->dalsi;
            aktAlbum->dalsi = noveAlbum;
            return;
        }
        aktAlbum = aktAlbum->dalsi;
    }

    aktAlbum->dalsi = noveAlbum; 
}

void del(int rok_vydani, struct t_HudbaDB** uk_prvni) {
    struct t_HudbaDB* aktAlbum;

    while (*uk_prvni && (*uk_prvni)->rok_vydani == rok_vydani) {
        struct t_HudbaDB* newPrvni = (*uk_prvni)->dalsi;
        free(*uk_prvni);
        *uk_prvni = newPrvni;
    }

    aktAlbum = *uk_prvni;
    while (aktAlbum && aktAlbum->dalsi) {
        if (aktAlbum->dalsi->rok_vydani == rok_vydani) {
            struct t_HudbaDB* newDalsi = aktAlbum->dalsi->dalsi;
            free(aktAlbum->dalsi);
            aktAlbum->dalsi = newDalsi;
        }
        aktAlbum = aktAlbum->dalsi;
    }
}

void vypisSeznam(struct t_HudbaDB* uk_prvni) {
    struct t_HudbaDB* aktAlbum = uk_prvni;

    printf("\nSeznam vsech alb:\n");

    if (aktAlbum == NULL) {
        printf("Seznam je prazdny.\n");
        return;
    }

    while (aktAlbum) {
        printf("%d: %s - %s\n", aktAlbum->rok_vydani, aktAlbum->interpret, aktAlbum->nazev_alba);
        aktAlbum = aktAlbum->dalsi;
    }
}

void vypisSeznamPodlePismena(struct t_HudbaDB* uk_prvni) {
    char pismeno;
    struct t_HudbaDB* aktAlbum = uk_prvni;

    printf("Zadejte pocatecni pismeno interpreta: ");
    scanf_s(" %c", &pismeno, 1);  

    pismeno = toupper(pismeno);

    printf("\nSeznam alb, jejichz interpret zacina pismenem '%c':\n", pismeno);

    int found = 0; 
    while (aktAlbum) {
        if (toupper(aktAlbum->interpret[0]) == pismeno) {
            printf("%d: %s - %s\n", aktAlbum->rok_vydani, aktAlbum->interpret, aktAlbum->nazev_alba);
            found = 1;
        }
        aktAlbum = aktAlbum->dalsi;
    }

    if (!found) {
        printf("Nebylo nalezeno zadne album zacinajici pismenem '%c'.\n", pismeno);
    }
}