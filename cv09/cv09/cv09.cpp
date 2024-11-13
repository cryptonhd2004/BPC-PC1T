#include "VectorMath.cpp"

int main() {
    struct vector3d u, v;
    int operaceTyp;


    printf("Zadejte prvni 3D vektor (x y z): ");
    scanf("%lf %lf %lf", &u.x,  &u.y, &u.z);
    printf("Zadejte druhy 3D vektor (x, y, z): ");
    scanf("%lf %lf %lf", &v.x, &v.y, &v.z);

    printf("Zadejte operaci (1 = soucet, 2 = skalarniSoucin, 3 = vektorovySoucin): ");
    scanf("%d", &operaceTyp);

   
    struct vector3d vysledek = operace(u, v, (enum typOperace)operaceTyp);

    
    tisk(vysledek);
    int porovnani = porovnejVelikosti(u, v);
    if (porovnani == 1) {
        printf("Vektor u je vetsi nez vektor v.\n");
    }
    else if (porovnani == -1) {
        printf("Vektor u je mensi nez vektor v.\n");
    }
    else {
        printf("Vektory u a v maji stejnou velikost.\n");
    }

    
    return 0;
}