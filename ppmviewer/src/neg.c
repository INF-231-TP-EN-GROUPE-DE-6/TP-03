#include "operations.h"
void negatif(Image *img) {
    for (int i = 0; i < img->hauteur; i++)
        for (int j = 0; j < img->largeur; j++) {
            img->pixels[i][j].r = img->max - img->pixels[i][j].r;
            img->pixels[i][j].g = img->max - img->pixels[i][j].g;
            img->pixels[i][j].b = img->max - img->pixels[i][j].b;
        }
}