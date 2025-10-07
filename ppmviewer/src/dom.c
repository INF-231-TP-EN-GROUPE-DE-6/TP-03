#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("/home/boyz/School_projects/TP-03/ppmviewer/Images/test1.ppm", "r");
    char format[3];
    int width, height, maxval;

    fscanf(f, "%2s", format);
    fscanf(f, "%d %d", &width, &height);
    fscanf(f, "%d", &maxval);

    int r, g, b;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fscanf(f, "%d %d %d", &r, &g, &b);
            printf("Pixel (%d,%d): R=%d G=%d B=%d\n", x, y, r, g, b);
        }
    }
    fclose(f);
    return 0;
}