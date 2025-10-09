#include "operations.h"
void dominante(Image *img, char c, int val) {
    for (int i = 0; i < img->hauteur; i++) {
        for (int j = 0; j < img->largeur; j++) {
            Pixel *p = &img->pixels[i][j];
            int maxv = (p->r > p->g && p->r > p->b) ? 'R' : (p->g > p->b ? 'G' : 'B');
            if (maxv == c) {
                p->r += val; p->g += val; p->b += val;
                if (p->r < 0) p->r = 0; if (p->r > img->max) p->r = img->max;
                if (p->g < 0) p->g = 0; if (p->g > img->max) p->g = img->max;
                if (p->b < 0) p->b = 0; if (p->b > img->max) p->b = img->max;
            }
        }
    }
}