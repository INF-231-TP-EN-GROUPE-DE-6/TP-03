#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int R;
    int G;
    int B;
} Pixel;
typedef struct
{
    int largeur;
    int hauteur;
    int max_val;
    Pixel **pixels;
} Image;
Image *lirePPM(const char *nomFichier)
{
    FILE *f = fopen(nomFichier, "r");
    if (!f)
    {
        printf("Erreur : impossible d’ouvrir %s\n", nomFichier);
        return NULL;
    }

    char type[3];
    Image *img = malloc(sizeof(Image));
    fscanf(f, "%s", type);
    if (type[0] != 'P' || type[1] != '3')
    {
        printf("Erreur : format PPM non supporté (%s)\n", type);
        fclose(f);
        free(img);
        return NULL;
    }

    fscanf(f, "%d %d %d", &img->largeur, &img->hauteur, &img->max_val);

    img->pixels = malloc(img->hauteur * sizeof(Pixel *));
    for (int i = 0; i < img->hauteur; i++)
    {
        img->pixels[i] = malloc(img->largeur * sizeof(Pixel));
    }

    for (int i = 0; i < img->hauteur; i++)
    {
        for (int j = 0; j < img->largeur; j++)
        {
            fscanf(f, "%d %d %d",
                   &img->pixels[i][j].R,
                   &img->pixels[i][j].G,
                   &img->pixels[i][j].B);
        }
    }

    fclose(f);
    return img;
}

void passerEnGris(Image *img)
{
    if (img == NULL || img->pixels == NULL)
    {
        printf("Erreur : image invalide.\n");
        return;
    }

    for (int i = 0; i < img->hauteur; i++)
    {
        for (int j = 0; j < img->largeur; j++)
        {

            int R = img->pixels[i][j].R;
            int G = img->pixels[i][j].G;
            int B = img->pixels[i][j].B;

            int gris = (R + G + B) / 3;

            img->pixels[i][j].R = gris;
            img->pixels[i][j].G = gris;
            img->pixels[i][j].B = gris;
        }
    }

    printf("Conversion en niveaux de gris effectuée avec succès.\n");
}

void ecrirePPM(const char *nomFichier, Image *img)
{
    FILE *f = fopen(nomFichier, "w");
    if (!f)
    {
        printf("Erreur : impossible de créer %s\n", nomFichier);
        return;
    }

    fprintf(f, "P3\n%d %d\n%d\n", img->largeur, img->hauteur, img->max_val);

    for (int i = 0; i < img->hauteur; i++)
    {
        for (int j = 0; j < img->largeur; j++)
        {
            fprintf(f, "%d %d %d ",
                    img->pixels[i][j].R,
                    img->pixels[i][j].G,
                    img->pixels[i][j].B);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf(" Fichier %s créé avec succès.\n", nomFichier);
}