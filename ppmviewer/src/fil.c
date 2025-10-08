#include "ppm.h"
void operation_filtre_median(const char *fichier_entree, const char *fichier_sortie) {
    ImagePPM *image = lire_ppm(fichier_entree);
    if (!image) {
        printf("fichier non trouvé\n");
        return;
    }
    // Créer une nouvelle image pour le résultat
    ImagePPM *resultat = (ImagePPM*)malloc(sizeof(ImagePPM));
    strcpy(resultat->version, image->version);
    resultat->largeur = image->largeur;
    resultat->hauteur = image->hauteur;
    resultat->max_val = image->max_val;
    // Allouer la mémoire
    resultat->pixels = (Pixel**)malloc(resultat->hauteur * sizeof(Pixel*));
    for (int i = 0; i < resultat->hauteur; i++) {
        resultat->pixels[i] = (Pixel*)malloc(resultat->largeur * sizeof(Pixel));
    }
    // Tableaux pour stocker les valeurs des voisins
    int voisins_r[9], voisins_g[9], voisins_b[9];
    // Appliquer le filtre médian
    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            int count = 0;
            // Collecter les valeurs des 8 voisins + pixel central
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    int ni = i + di;
                    int nj = j + dj;
                    if (ni >= 0 && ni < image->hauteur && nj >= 0 && nj < image->largeur) {
                        voisins_r[count] = image->pixels[ni][nj].r;
                        voisins_g[count] = image->pixels[ni][nj].g;
                        voisins_b[count] = image->pixels[ni][nj].b;
                        count++;
                    }
                }
            }
            // Calculer la médiane pour chaque composante
            resultat->pixels[i][j].r = mediane(voisins_r, count);
            resultat->pixels[i][j].g = mediane(voisins_g, count);
            resultat->pixels[i][j].b = mediane(voisins_b, count);
        }
    }
    ecrire_ppm(fichier_sortie, resultat);
    liberer_image(image);
    liberer_image(resultat);
    printf("opération effectuée\n");
}