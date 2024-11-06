


#include "sindelar.h"

using namespace std;

void prunik(double zacatek1, double konec1, double zacatek2, double konec2, double* vysl_zacatek, double* vysl_konec)
{
    if (!(zacatek1 <= konec1)) {
        double xzacatek1 = zacatek1;
        double xkonec1 = konec1;

        if (xzacatek1 >= xkonec1) {
            zacatek1 = xkonec1;
            konec1 = xzacatek1;
        }
    }

    // Oprava poøadí intervalù 2
    if (!(zacatek2 <= konec2)) {
        double xzacatek2 = zacatek2;
        double xkonec2 = konec2;

        if (xzacatek2 >= xkonec2) {
            zacatek2 = xkonec2;
            konec2 = xzacatek2;
        }
    }

    // Urèení prùniku intervalu
    *vysl_zacatek = (zacatek1 > zacatek2) ? zacatek1 : zacatek2;
    *vysl_konec = (konec1 < konec2) ? konec1 : konec2;

    // Pokud je zaèátek vìtší než konec, není prùnik
    if (*vysl_zacatek > *vysl_konec) {
        *vysl_zacatek = 0;  // Mùže být libovolná hodnota signalizující "žádný prùnik"
        *vysl_konec = 0;
    }
}
