#include <stdio.h>
void adjust_brightness_ppm(const char *input_filename, const char *output_filename, int adjustment);
#ifndef DOM_H
#define DOM_H

#include <stdint.h>
#include <stddef.h>
typedef struct {
    int width;      // largeur en pixels
    int height;     // hauteur en pixels
    int maxval;     // valeur maximale d'intensité (habituellement 255)
    uint8_t *data;  // tampon de taille width * height * 3
} PPMImage;
#endif // DOM_H
