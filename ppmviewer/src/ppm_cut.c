#include "ppm.h"
void operation_decouper(const char *fichier_entree, int l1, int l2, int c1, int c2, const char *fichier_sortie) {
ImagePPM *original = lire_ppm(fichier_entree);
if (!original) {
printf("fichier non trouvé\n");
return;
}
// Validation des paramètres
if (l1 < 1 || l2 > original->hauteur || l1 >= l2 ||
c1 < 1 || c2 > original->largeur || c1 >= c2) {
printf("Erreur : paramètres de découpage invalides\n");
printf("Conditions requises : 1 <= l1 < l2 <= %d et 1 <= c1 < c2 <= %d\n",
original->hauteur, original->largeur);
liberer_image(original);
return;
}
// Créer sous-image
ImagePPM *nouvelle = malloc(sizeof(ImagePPM));
strcpy(nouvelle->version, original->version);
nouvelle->largeur = c2 - c1 + 1;
nouvelle->hauteur = l2 - l1 + 1;
nouvelle->max_val = original->max_val;
// Allouer pixels
nouvelle->pixels = malloc(nouvelle->hauteur * sizeof(Pixel *));
for (int i = 0; i < nouvelle->hauteur; i++) {
nouvelle->pixels[i] = malloc(nouvelle->largeur * sizeof(Pixel));
for (int j = 0; j < nouvelle->largeur; j++) {
nouvelle->pixels[i][j] = original->pixels[l1 - 1 + i][c1 - 1 + j];
}
}
// Sauvegarder
ecrire_ppm(fichier_sortie, nouvelle);
printf("opération effectuée\n");
// Libérer
liberer_image(nouvelle);
liberer_image(original);
}
