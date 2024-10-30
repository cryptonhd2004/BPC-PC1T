// cv7.cpp : Defines the entry point for the application.
//

#include "cv7.h"
#include "Body2d.h"
#define POCET_BODU 10
using namespace std;

int main() {
	int body[POCET_BODU][2] = { 5, 10,
	-14, 2,
	45, 4,
	-9, 8,
	58, -3,
	47, 5,
	-18, -86,
	75, 7,
	-25, 51,
	17, 98 };
	int referencniX, referencniY;
	printf("Pole bodu: \n");
	int i = 0;
	while (i < 9) {
		printf("%d. (%d , %d)\n", i, body[i][0], body[1][i]);
			i++;
	}
	printf("\nZadejte souradnice bodu: ");
	scanf("%d %d", &referencniX, &referencniY);
	double maxVzdalenost;
	printf("Zadejte perimetr: ");
	scanf("%lf", &maxVzdalenost);
	int index = indexNejblizsi(POCET_BODU, body, referencniX, referencniY);
	double prumerna = prumernaVzdalenost(POCET_BODU, body, referencniX, referencniY);

	printf("- Nejblizsi je index bodu: %d. (%d, %d)\n",index, body[index][0], body[index][1]);
	printf("- Prumerna vzdalenost k ostatnim bodum je: %.2f\n", prumerna);
	

	vypisBlizkeBody(POCET_BODU, body, referencniX, referencniY, maxVzdalenost);

	return 0;
}
