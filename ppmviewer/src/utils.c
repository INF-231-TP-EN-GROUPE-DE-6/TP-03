#include "ppm.h"

// Fonction pour comparer deux entiers (pour qsort)
int comparer(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// Fonction pour calculer la médiane d'un tableau
int mediane(int *tableau, int taille) {
    qsort(tableau, taille, sizeof(int), comparer);
    return tableau[taille / 2];
}

// Fonction pour limiter une valeur entre 0 et max_val
int limiter(int valeur, int max_val) {
    if (valeur < 0) return 0;
    if (valeur > max_val) return max_val;
    return valeur;
}