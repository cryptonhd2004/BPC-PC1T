// cv7.cpp : Defines the entry point for the application.
//

#include "cv7.h"

using namespace std;


double vzdalenost(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    }

int indexNejblizsi(int velikost, int poleBodu[][2], int referencniX, int referencniY) {
    int index = 0;
    double nejmensi = vzdalenost(poleBodu[0][0], poleBodu[0][1], referencniX, referencniY);
    for (int i = 1; i < velikost; i++) {
        double aktualni = vzdalenost(poleBodu[i][0], poleBodu[i][1], referencniX, referencniY);
        if (aktualni < nejmensi) {
            nejmensi = aktualni;
            index = i;
        }
    }
    return index;
}
double prumernaVzdalenost(int velikost, int poleBodu[][2], int referencniX, int referencniY) {
    double suma = 0;
    for (int i = 0; i < velikost; i++) {
        suma += vzdalenost(poleBodu[i][0], poleBodu[i][1], referencniX, referencniY);
        }
    return suma / velikost;
    }
	
void vypisBlizkeBody(int velikost, int poleBodu[][2], int referencniX, int referencniY, double maxVzdalenost) {
    printf("- Body v danem perimetru:\n");
    int pocetokoli = 0;
    for (int i = 0; i < velikost; i++) {
        if (vzdalenost(poleBodu[i][0], poleBodu[i][1], referencniX, referencniY) <= maxVzdalenost) {
            printf("    %d. (%d, %d)\n",i, poleBodu[i][0], poleBodu[i][1]);
            pocetokoli++;

        }
    }
    printf(" Nalezeno %d body / bodu v okoli",pocetokoli);

}
