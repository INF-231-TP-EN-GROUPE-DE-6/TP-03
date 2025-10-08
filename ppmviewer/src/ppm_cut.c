#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int r, g, b;
} Pixel;

typedef struct {
    char version[3];
    int largeur, hauteur, max_val;
    Pixel **pixels;
} ImagePPM;

// Lire fichier PPM
ImagePPM *lire_ppm(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (!fichier) {
        printf("Erreur: Fichier %s introuvable\n", nom_fichier);
        return NULL;
    }

    ImagePPM *image = malloc(sizeof(ImagePPM));
    char ligne[256];
    
    // Lire version
    fscanf(fichier, "%2s", image->version);
    
    // Lire dimensions en sautant les commentaires
    while (fgets(ligne, sizeof(ligne), fichier)) {
        if (ligne[0] == '#') continue;
        if (sscanf(ligne, "%d %d", &image->largeur, &image->hauteur) == 2) break;
    }
    
    // Lire valeur max
    fscanf(fichier, "%d", &image->max_val);
    
    // Allouer pixels
    image->pixels = malloc(image->hauteur * sizeof(Pixel *));
    for (int i = 0; i < image->hauteur; i++) {
        image->pixels[i] = malloc(image->largeur * sizeof(Pixel));
        for (int j = 0; j < image->largeur; j++) {
            fscanf(fichier, "%d %d %d", &image->pixels[i][j].r, 
                                       &image->pixels[i][j].g, 
                                       &image->pixels[i][j].b);
        }
    }
    
    fclose(fichier);
    return image;
}

// Sauvegarder fichier PPM
void sauvegarder_ppm(ImagePPM *image, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    fprintf(fichier, "%s\n", image->version);
    fprintf(fichier, "%d %d\n", image->largeur, image->hauteur);
    fprintf(fichier, "%d\n", image->max_val);
    
    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            fprintf(fichier, "%d %d %d\n", image->pixels[i][j].r, 
                                         image->pixels[i][j].g, 
                                         image->pixels[i][j].b);
        }
    }
    
    fclose(fichier);
}

// Libérer mémoire
void liberer_image(ImagePPM *image) {
    for (int i = 0; i < image->hauteur; i++) {
        free(image->pixels[i]);
    }
    free(image->pixels);
    free(image);
}

// FONCTION PRINCIPALE - Découper l'image
void decouper_image(const char *entree, int l1, int l2, int c1, int c2, const char *sortie) {
    ImagePPM *original = lire_ppm(entree);
    if (!original) return;

    // Validation
    if (l1 < 1 || l2 > original->hauteur || l1 >= l2 || 
        c1 < 1 || c2 > original->largeur || c1 >= c2) {
        printf("Paramètres invalides! Image: %dx%d\n", original->largeur, original->hauteur);
        liberer_image(original);
        return;
    }

    // Créer sous-image
    ImagePPM sous_image;
    strcpy(sous_image.version, original->version);
    sous_image.largeur = c2 - c1 + 1;
    sous_image.hauteur = l2 - l1 + 1;
    sous_image.max_val = original->max_val;
    
    // Allouer pixels
    sous_image.pixels = malloc(sous_image.hauteur * sizeof(Pixel *));
    for (int i = 0; i < sous_image.hauteur; i++) {
        sous_image.pixels[i] = malloc(sous_image.largeur * sizeof(Pixel));
        for (int j = 0; j < sous_image.largeur; j++) {
            sous_image.pixels[i][j] = original->pixels[(l1-1) + i][(c1-1) + j];
        }
    }

    // Sauvegarder
    sauvegarder_ppm(&sous_image, sortie);
    printf("Découpage réussi: %s (%dx%d)\n", sortie, sous_image.largeur, sous_image.hauteur);
    
    // Libérer
    for (int i = 0; i < sous_image.hauteur; i++) {
        free(sous_image.pixels[i]);
    }
    free(sous_image.pixels);
    liberer_image(original);
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        printf("Usage: %s fichier.ppm l1 l2 c1 c2 resultat.ppm\n", argv[0]);
        printf("Exemple: %s image.ppm 1 50 1 100 coupure.ppm\n", argv[0]);
        return 1;
    }
    
    decouper_image(argv[1], atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), argv[6]);
    return 0;
}
