#include "cv8.h"
#include "sindelar.h"
#include <cstdio>

using namespace std;

int main()
{
    double zacatek1, zacatek2, konec1, konec2, vysl_zacatek, vysl_konec;

    printf("CV08 program");
    printf("\nTest data:");

    // 1. test
    zacatek1 = 1.5;
    konec1 = 2.8;
    zacatek2 = 1.6;
    konec2 = 2.0;
    printf("\n1. (%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);

    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);

    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }

    // 2. test
    zacatek1 = 1.5;
    konec1 = 2.8;
    zacatek2 = 3.6;
    konec2 = 7.5;
    printf("\n2. (%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);

    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);

    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }

    // 3. test
    zacatek1 = 1.5;
    konec1 = 4.8;
    zacatek2 = 2.6;
    konec2 = 7.5;
    printf("\n3. (%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);

    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);

    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }

    // 4. test
    zacatek1 = 5.1;
    konec1 = -2.3;
    zacatek2 = 1.5;
    konec2 = 6.2;
    printf("\n4. (%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);

    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);

    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }
    // 5. test
    zacatek1 = 2.5;
    konec1 = 8.8;
    zacatek2 = -0.3;
    konec2 = 9.5;
    printf("\n5. (%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);

    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);

    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }
    // 6. test
    zacatek1 = 5.5;
    konec1 = -9.5;
    zacatek2 = 9.9;
    konec2 = -2.3;
    printf("\n6. (%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);

    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);

    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }
    //Vlastní test
    printf("\n\nZadejte vlastni rozsahy");
    printf("\nRozsah 1:");
    scanf_s("%lf", &zacatek1);
    scanf_s("%lf", &konec1);
    printf("Rozsah 2:");
    scanf_s("%lf", &zacatek2);
    scanf_s("%lf", &konec2);
    prunik(zacatek1, konec1, zacatek2, konec2, &vysl_zacatek, &vysl_konec);
    printf("(%.1lf, %.1lf) a (%.1lf, %.1lf)", zacatek1, konec1, zacatek2, konec2);
    if (vysl_zacatek == 0 && vysl_konec == 0) {
        printf(" -> Nema prunik");
    }
    else {
        if (vysl_zacatek > vysl_konec) {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_konec, vysl_zacatek);
        }
        else {
            printf(" -> Ma prunik; rozsah (%.1lf, %.1lf)", vysl_zacatek, vysl_konec);
        }
    }
    return 0;
}
