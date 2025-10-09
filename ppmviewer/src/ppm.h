#ifndef PPM_H
#define PPM_H

typedef struct {
    int r, g, b;
} Pixel;

typedef struct {
    int largeur;
    int hauteur;
    int max;
    Pixel **pixels;
} Image;

Image *lirePPM(const char *nom);
void ecrirePPM(const char *nom, Image *img);
void libererImage(Image *img);

#endif
