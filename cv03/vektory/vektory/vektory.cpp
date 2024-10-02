// vektory.cpp : Defines the entry point for the application.
//

#include "vektory.h"

using namespace std;

int main()
{
	float ux;
	float uy;
	float vx;
	float vy;
	float x;
	float y;
	cout << "Zadejte souradnice vektoru u (oddelte je mezerou): ";
	cin >> ux;
	cin >> uy;
	cout << "\nZadejte souradnice vektoru v (oddelte je mezerou): ";
	cin >> vx;
	cin >> vy;
	x = ux + vx;
	y = uy + vy;
	cout << "\nSoucet vektoru uv je: (" << x << "," << y << ").";
	return 0;
}
