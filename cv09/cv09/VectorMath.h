// VectorMath.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
enum typOperace {soucet = 1, skalarniSoucin, vektorovySoucin};

typedef struct vector3d {
    double x, y, z;
};

// Funkce pro provedení operace mezi dvěma vektory
struct vector3d operace(struct vector3d u, struct vector3d v, enum typOperace typ);

// Funkce pro tisk vektoru a jeho velikosti
void tisk(struct vector3d u);
int porovnejVelikosti(struct vector3d u, struct vector3d v);
