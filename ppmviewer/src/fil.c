#include "operations.h"
static int mediane(int *vals, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (vals[j] < vals[i]) {
                int tmp = vals[i];
                vals[i] = vals[j];
                vals[j] = tmp;
            }
    return vals[n / 2];
}

void filtreMedian(Image *img) {
    Image *copie = decouper(img, 0, img->hauteur, 0, img->largeur);
    int dx[] = {-1,-1,-1,0,0,0,1,1,1};
    int dy[] = {-1,0,1,-1,0,1,-1,0,1};
    for (int i = 1; i < img->hauteur - 1; i++) {
        for (int j = 1; j < img->largeur - 1; j++) {
            int R[9], G[9], B[9];
            for (int k = 0; k < 9; k++) {
                int x = i + dx[k], y = j + dy[k];
                R[k] = copie->pixels[x][y].r;
                G[k] = copie->pixels[x][y].g;
                B[k] = copie->pixels[x][y].b;
            }
            img->pixels[i][j].r = mediane(R, 9);
            img->pixels[i][j].g = mediane(G, 9);
            img->pixels[i][j].b = mediane(B, 9);
        }
    }
    libererImage(copie);
}