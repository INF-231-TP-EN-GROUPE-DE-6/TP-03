#include "ppm.h"

// Fonction pour lire un entier en ignorant les commentaires
int lire_entier(FILE *fichier) {
    int val, c;
    while (1) {
        if (fscanf(fichier, "%d", &val) == 1) return val;
        // Ignorer jusqu'à la fin de ligne (commentaire ou erreur)
        while ((c = fgetc(fichier)) != EOF && c != '\n');
        if (c == EOF) return -1; // Erreur de lecture
    }
    return -1; // Ne devrait pas arriver
}

// Fonction pour lire une image PPM
ImagePPM* lire_ppm(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        return NULL;
    }
    ImagePPM *image = (ImagePPM*)malloc(sizeof(ImagePPM));
    char ligne[256];
    int valeurs_lues = 0;
    // Lire la version
    fscanf(fichier, "%s", image->version);
    if (strcmp(image->version, "P3") != 0) {
        printf("Erreur : Seul le format P3 est supporté\n");
        free(image);
        fclose(fichier);
        return NULL;
    }
    // Consommer le retour à la ligne après P3
    fgetc(fichier);
    // Lire largeur, hauteur et max_val en ignorant les commentaires
    while (valeurs_lues < 3) {
        if (fgets(ligne, sizeof(ligne), fichier) == NULL) break;
        // Ignorer les lignes de commentaires
        if (ligne[0] == '#') continue;
        // Essayer de lire les valeurs
        if (valeurs_lues == 0) {
            if (sscanf(ligne, "%d %d", &image->largeur, &image->hauteur) == 2) {
                valeurs_lues = 2;
            } else if (sscanf(ligne, "%d", &image->largeur) == 1) {
                valeurs_lues = 1;
            }
        } else if (valeurs_lues == 1) {
            if (sscanf(ligne, "%d %d", &image->hauteur, &image->max_val) == 2) {
                valeurs_lues = 3;
            } else if (sscanf(ligne, "%d", &image->hauteur) == 1) {
                valeurs_lues = 2;
            }
        } else if (valeurs_lues == 2) {
            if (sscanf(ligne, "%d", &image->max_val) == 1) {
                valeurs_lues = 3;
            }
        }
    }
    // Allouer la mémoire pour les pixels
    image->pixels = (Pixel**)malloc(image->hauteur * sizeof(Pixel*));
    for (int i = 0; i < image->hauteur; i++) {
        image->pixels[i] = (Pixel*)malloc(image->largeur * sizeof(Pixel));
    }
    // Lire les pixels avec gestion des commentaires
    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            image->pixels[i][j].r = lire_entier(fichier);
            image->pixels[i][j].g = lire_entier(fichier);
            image->pixels[i][j].b = lire_entier(fichier);
            // Vérifier erreurs de lecture (optionnel, mais recommandé)
            if (image->pixels[i][j].r < 0 || image->pixels[i][j].g < 0 || image->pixels[i][j].b < 0) {
                printf("Erreur de lecture des pixels\n");
                liberer_image(image);
                fclose(fichier);
                return NULL;
            }
        }
    }
    fclose(fichier);
    return image;
}

// Fonction pour écrire une image PPM
void ecrire_ppm(const char *nom_fichier, ImagePPM *image) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (!fichier) {
        printf("Erreur : impossible de créer le fichier %s\n", nom_fichier);
        return;
    }
    // Écrire l'en-tête
    fprintf(fichier, "%s\n", image->version);
    fprintf(fichier, "# Image traitée\n");
    fprintf(fichier, "%d %d\n", image->largeur, image->hauteur);
    fprintf(fichier, "%d\n", image->max_val);
    // Écrire les pixels
    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            fprintf(fichier, "%d %d %d ",
                    image->pixels[i][j].r,
                    image->pixels[i][j].g,
                    image->pixels[i][j].b);
        }
        fprintf(fichier, "\n");
    }
    fclose(fichier);
}

// Fonction pour libérer la mémoire d'une image
void liberer_image(ImagePPM *image) {
    if (image) {
        for (int i = 0; i < image->hauteur; i++) {
            free(image->pixels[i]);
        }
        free(image->pixels);
        free(image);
    }
}