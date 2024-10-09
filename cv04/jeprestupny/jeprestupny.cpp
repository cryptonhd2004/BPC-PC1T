// jeprestupny.cpp : Defines the entry point for the application.
//

#include "jeprestupny.h"

using namespace std;


int jePrestupny(int rok) {
	if ((rok % 4 == 0 and rok % 100 != 0) || (rok % 400 == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

int jeLichy(int rok) {
	if (rok % 2 != 0) {
		return 1;
	}
	else {
		return 0;
	}
}

int main()
{
	int rok;
	printf("|Rok    | Je prestupny  |  Je lichy	|\n");
	int roky[7] = { 1000, 1999, 2000, 2002, 2022, 2024, 2200 };
	for (int i = 0; i < 7; i++) {
		rok = roky[i];
		
			printf("|%d	|	%d	|	%d	|\n", rok, jePrestupny(rok), jeLichy(rok));
			
	}


	return 0;
}
