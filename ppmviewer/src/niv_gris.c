#include "operations.h"
void toGray(Image *img) {
    for (int i = 0; i < img->hauteur; i++)
        for (int j = 0; j < img->largeur; j++) {
            int m = (img->pixels[i][j].r + img->pixels[i][j].g + img->pixels[i][j].b) / 3;
            img->pixels[i][j].r = img->pixels[i][j].g = img->pixels[i][j].b = m;
        }
    }
