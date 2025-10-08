#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Structure pour représenter un pixel RGB
typedef struct {
    int r, g, b;
} Pixel;

// Structure pour représenter une image PPM
typedef struct {
    char version[3];
    int largeur;
    int hauteur;
    int max_val;
    Pixel **pixels;
} ImagePPM;

// Fonctions utilitaires
int comparer(const void *a, const void *b);
int mediane(int *tableau, int taille);
int limiter(int valeur, int max_val);

// Fonctions I/O
int lire_entier(FILE *fichier);
ImagePPM* lire_ppm(const char *nom_fichier);
void ecrire_ppm(const char *nom_fichier, ImagePPM *image);
void liberer_image(ImagePPM *image);

// Opérations
void operation_dominante(const char *fichier, char couleur, int valeur);
void operation_gris(const char *fichier);
void operation_negatif(const char *fichier_entree, const char *fichier_sortie);
void operation_taille(const char *fichier);
void operation_decouper(const char *fichier_entree, int l1, int l2, int c1, int c2, const char *fichier_sortie);
void operation_filtre_median(const char *fichier_entree, const char *fichier_sortie);

// Menu (utilisé dans main)
void afficher_menu();

#endif