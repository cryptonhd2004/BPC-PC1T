// Cv05.cpp : Defines the entry point for the application.
//

#include "Cv05.h"
#include <iostream>
#include <math.h>
using namespace std;



void soucet(double a[3], double b[3], double c[3]) {
    for (int i = 0; i < 3; i++) {
        c[i] = a[i] + b[i];
    }
}

double velikost(double a[3]) {
    return sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
}

double skalarniSoucin(double a[3], double b[3]) {
    double soucin = 0.0;
    for (int i = 0; i < 3; i++) {
        soucin += a[i] * b[i];
    }
    return soucin;
}

void vektorovySoucin(double a[3], double b[3], double c[3]) {
    c[0] = a[1] * b[2] - a[2] * b[1];
    c[1] = a[2] * b[0] - a[0] * b[2];
    c[2] = a[0] * b[1] - a[1] * b[0];
}

int main() {
    float a1, a2, a3, b1, b2, b3;
    a1 = a2 = a3 = b1 = b2 = b3 = 0;

    cout << "Kalkulator vektoru ve 3D prostoru\n\n";
    cout << "Zadejte souradnice vektoru A oddelene carkou: ";
    scanf_s("%f,%f,%f", &a1, &a2, &a3);
    cout << "Zadejte souradnice vektoru B oddelene carkou: ";
    scanf_s("%f,%f,%f", &b1, &b2, &b3);

    double vektorA[3] = { a1,a2,a3 };
    double vektorB[3] = { b1,b2,b3 };
    double vektorC[3];
    double vektorsouc[3];

    soucet(vektorA, vektorB, vektorC);
    cout << "Soucet A+B: (" << vektorC[0] << ", " << vektorC[1] << ", " << vektorC[2] << ")\n";

    double velikostA = velikost(vektorA);
    cout << "Velikost A: " << velikostA << "\n";

    double velikostB = velikost(vektorB);
    cout << "Velikost B: " << velikostB << "\n";

    double skalarni = skalarniSoucin(vektorA, vektorB);
    cout << "Skalarni soucin AB: " << skalarni << "\n";

    vektorovySoucin(vektorA, vektorB, vektorsouc);
    //cout << "Vektorovy soucin AB: " << vektorsouc[0];
    cout << "Vektorovy soucin AB: (" << vektorsouc[0] << ", " << vektorsouc[1] << ", " << vektorsouc[2] << ")\n";
    return 0;
}