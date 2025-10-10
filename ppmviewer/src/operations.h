#ifndef OPERATIONS_H
#define OPERATIONS_H
#include "ppm.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

void afficherTaille(Image *img);
void toGray(Image *img);
void negatif(Image *img);
void dominante(Image *img, char c, int val);
Image *decouper(Image *img, int l1, int l2, int c1, int c2);
void filtreMedian(Image *img);

#endif
