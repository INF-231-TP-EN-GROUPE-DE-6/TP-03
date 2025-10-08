#include <stdio.h>

void adjust_brightness(const char *filename, int adjustment) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return;
    }
    char format[3];
    int width, height, maxval;
    fscanf(f, "%2s", format);
    fscanf(f, "%d %d", &width, &height);
    fscanf(f, "%d", &maxval);

    int r, g, b;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            fscanf(f, "%d %d %d", &r, &g, &b);
            r = r + adjustment;
            g = g + adjustment;
            b = b + adjustment;
            // Clamp entre 0 et maxval
            if (r < 0) r = 0; if (r > maxval) r = maxval;
            if (g < 0) g = 0; if (g > maxval) g = maxval;
            if (b < 0) b = 0; if (b > maxval) b = maxval;
            printf("Pixel (%d,%d): R=%d G=%d B=%d\n", x, y, r, g, b);
        }
    }
    fclose(f);
}