// VectorMath.cpp : Defines the entry point for the application.
//

#include "VectorMath.h"
#include <iostream>
#include <cmath>

// Funkce pro provedení operace mezi dvěma vektory
struct vector3d operace(struct vector3d u, struct vector3d v, enum typOperace typ) {
    vector3d result;
    switch (typ) {
    case soucet:
        result.x = u.x + v.x;
        result.y = u.y + v.y;
        result.z = u.z + v.z;
        break;
    case skalarniSoucin:
        result.x = u.x * v.x + u.y * v.y + u.z * v.z;
        result.y = 0;
        result.z = 0;
        break;
    case vektorovySoucin:
        result.x = u.y * v.z - u.z * v.y;
        result.y = u.z * v.x - u.x * v.z;
        result.z = u.x * v.y - u.y * v.x;
        break;
    default:
        printf("Zadal jste operaci mimo rozsah!\n");
        break;
    }
    return result;
}
void tisk(struct vector3d u) {
    double velikost = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    printf("w = (%.2f, %.2f, %.2f)\n", u.x, u.y, u.z);
    printf("|w| = %.2f\n", velikost);
}
int porovnejVelikosti(struct vector3d u, struct vector3d v) {
    double velikostU = sqrt(u.x * u.x + u.y * u.y + u.z * u.z);
    double velikostV = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);

    if (velikostU > velikostV) {
        return 1;  // |u| > |v|
    }
    else if (velikostU < velikostV) {
        return -1; // |u| < |v|
    }
    else {
        return 0;  // |u| == |v|
    }
}