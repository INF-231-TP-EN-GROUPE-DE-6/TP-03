#include <stdio.h>
#include <stdlib.h>
#include "ppm.h"

Image *lirePPM(const char *nom) {
    FILE *f = fopen(nom, "r");
    if (!f) {
        printf("fichier non trouvé\n");
        return NULL;
    }

    Image *img = malloc(sizeof(Image));
    char format[3];
    fscanf(f, "%2s", format);
    if (format[0] != 'P' || format[1] != '3') {
        printf("Format non supporté (P3 attendu)\n");
        fclose(f);
        free(img);
        return NULL;
    }

    fscanf(f, "%d %d %d", &img->largeur, &img->hauteur, &img->max);

    img->pixels = malloc(img->hauteur * sizeof(Pixel *));
    for (int i = 0; i < img->hauteur; i++) {
        img->pixels[i] = malloc(img->largeur * sizeof(Pixel));
        for (int j = 0; j < img->largeur; j++)
            fscanf(f, "%d %d %d", &img->pixels[i][j].r, &img->pixels[i][j].g, &img->pixels[i][j].b);
    }

    fclose(f);
    return img;
}

void ecrirePPM(const char *nom, Image *img) {
    FILE *f = fopen(nom, "w");
    if (!f) return;

    fprintf(f, "P3\n%d %d\n%d\n", img->largeur, img->hauteur, img->max);
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++)
            fprintf(f, "%d %d %d ", img->pixels[i][j].r, img->pixels[i][j].g, img->pixels[i][j].b);
        fprintf(f, "\n");
    }
    fclose(f);
}

void libererImage(Image *img) {
    for (int i = 0; i < img->hauteur; i++)
        free(img->pixels[i]);
    free(img->pixels);
    free(img);
}
