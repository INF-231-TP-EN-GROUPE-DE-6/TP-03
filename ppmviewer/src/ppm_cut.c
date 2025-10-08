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

// Fonction pour lire un fichier PPM
ImagePPM *lire_fichier_ppm(const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        printf("Erreur: Impossible d'ouvrir le fichier %s\n", nom_fichier);
        return NULL;
    }

    ImagePPM *image = (ImagePPM *)malloc(sizeof(ImagePPM));
    if (image == NULL) {
        fclose(fichier);
        return NULL;
    }

    // Lire la version
    if (fscanf(fichier, "%2s", image->version) != 1) {
        printf("Erreur: Format de fichier invalide (version)\n");
        fclose(fichier);
        free(image);
        return NULL;
    }

    // Lire les dimensions en sautant les commentaires
    int caractere;
    while ((caractere = fgetc(fichier)) != EOF) {
        if (caractere == '#') {
            // Ignorer le commentaire
            while ((caractere = fgetc(fichier)) != '\n' && caractere != EOF);
        } else if (!isspace(caractere)) {
            ungetc(caractere, fichier);
            break;
        }
    }

    if (fscanf(fichier, "%d %d", &image->largeur, &image->hauteur) != 2) {
        printf("Erreur: Format de fichier invalide (dimensions)\n");
        fclose(fichier);
        free(image);
        return NULL;
    }

    // Lire la valeur maximale
    if (fscanf(fichier, "%d", &image->max_val) != 1) {
        printf("Erreur: Format de fichier invalide (valeur max)\n");
        fclose(fichier);
        free(image);
        return NULL;
    }

    // Allouer la mémoire pour les pixels
    image->pixels = (Pixel **)malloc(image->hauteur * sizeof(Pixel *));
    if (image->pixels == NULL) {
        printf("Erreur: Allocation mémoire échouée\n");
        fclose(fichier);
        free(image);
        return NULL;
    }

    for (int i = 0; i < image->hauteur; i++) {
        image->pixels[i] = (Pixel *)malloc(image->largeur * sizeof(Pixel));
        if (image->pixels[i] == NULL) {
            printf("Erreur: Allocation mémoire échouée pour la ligne %d\n", i);
            // Libérer la mémoire allouée précédemment
            for (int j = 0; j < i; j++) {
                free(image->pixels[j]);
            }
            free(image->pixels);
            fclose(fichier);
            free(image);
            return NULL;
        }
    }

    // Lire les données des pixels
    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            if (fscanf(fichier, "%d %d %d", &image->pixels[i][j].r, 
                                           &image->pixels[i][j].g, 
                                           &image->pixels[i][j].b) != 3) {
                printf("Erreur: Données pixel incomplètes à la position (%d, %d)\n", i, j);
                // Libérer la mémoire
                for (int k = 0; k < image->hauteur; k++) {
                    free(image->pixels[k]);
                }
                free(image->pixels);
                fclose(fichier);
                free(image);
                return NULL;
            }
        }
    }

    fclose(fichier);
    printf("Image %s chargée: %d x %d pixels\n", nom_fichier, image->largeur, image->hauteur);
    return image;
}

// Fonction pour sauvegarder un fichier PPM
int sauvegarder_fichier_ppm(ImagePPM *image, const char *nom_fichier) {
    FILE *fichier = fopen(nom_fichier, "w");
    if (fichier == NULL) {
        printf("Erreur: Impossible de créer le fichier %s\n", nom_fichier);
        return 0;
    }

    // Écrire l'en-tête
    fprintf(fichier, "%s\n", image->version);
    fprintf(fichier, "# Fichier créé par ppmviewer\n");
    fprintf(fichier, "%d %d\n", image->largeur, image->hauteur);
    fprintf(fichier, "%d\n", image->max_val);

    // Écrire les pixels
    for (int i = 0; i < image->hauteur; i++) {
        for (int j = 0; j < image->largeur; j++) {
            fprintf(fichier, "%d %d %d", image->pixels[i][j].r, 
                                        image->pixels[i][j].g, 
                                        image->pixels[i][j].b);
            if (j < image->largeur - 1) {
                fprintf(fichier, " ");
            }
        }
        fprintf(fichier, "\n");
    }

    fclose(fichier);
    return 1;
}

// Fonction pour libérer la mémoire d'une image
void liberer_image(ImagePPM *image) {
    if (image == NULL) return;
    
    if (image->pixels != NULL) {
        for (int i = 0; i < image->hauteur; i++) {
            if (image->pixels[i] != NULL) {
                free(image->pixels[i]);
            }
        }
        free(image->pixels);
    }
    free(image);
}

// Fonction pour afficher la taille d'une image
void afficher_taille(const char *nom_fichier) {
    ImagePPM *image = lire_fichier_ppm(nom_fichier);
    if (image == NULL) {
        printf("Erreur: Impossible de lire le fichier %s\n", nom_fichier);
        return;
    }

    printf("%d x %d\n", image->largeur, image->hauteur);
    liberer_image(image);
}

// Fonction pour découper une image
int decouper_image(const char *fichier_entree, int l1, int l2, int c1, int c2, const char *fichier_sortie) {
    ImagePPM *image_originale = lire_fichier_ppm(fichier_entree);
    if (image_originale == NULL) {
        return 0;
    }

    // Validation des paramètres
    if (l1 < 1 || l2 > image_originale->hauteur || l1 >= l2 || 
        c1 < 1 || c2 > image_originale->largeur || c1 >= c2) {
        printf("Erreur: Paramètres de découpage invalides.\n");
        printf("L'image a une taille de %d x %d pixels\n", 
               image_originale->largeur, image_originale->hauteur);
        printf("Doit respecter: 1 <= l1 < l2 <= %d et 1 <= c1 < c2 <= %d\n",
               image_originale->hauteur, image_originale->largeur);
        liberer_image(image_originale);
        return 0;
    }

    // Calcul des nouvelles dimensions
    int nouvelle_hauteur = l2 - l1 + 1;
    int nouvelle_largeur = c2 - c1 + 1;

    // Création de la nouvelle image
    ImagePPM *sous_image = (ImagePPM *)malloc(sizeof(ImagePPM));
    if (sous_image == NULL) {
        printf("Erreur: Impossible d'allouer la mémoire\n");
        liberer_image(image_originale);
        return 0;
    }

    strcpy(sous_image->version, image_originale->version);
    sous_image->largeur = nouvelle_largeur;
    sous_image->hauteur = nouvelle_hauteur;
    sous_image->max_val = image_originale->max_val;

    // Allocation mémoire pour les pixels
    sous_image->pixels = (Pixel **)malloc(nouvelle_hauteur * sizeof(Pixel *));
    if (sous_image->pixels == NULL) {
        printf("Erreur: Allocation mémoire échouée\n");
        liberer_image(image_originale);
        free(sous_image);
        return 0;
    }

    for (int i = 0; i < nouvelle_hauteur; i++) {
        sous_image->pixels[i] = (Pixel *)malloc(nouvelle_largeur * sizeof(Pixel));
        if (sous_image->pixels[i] == NULL) {
            printf("Erreur: Allocation mémoire échouée pour la ligne %d\n", i);
            for (int j = 0; j < i; j++) {
                free(sous_image->pixels[j]);
            }
            free(sous_image->pixels);
            liberer_image(image_originale);
            free(sous_image);
            return 0;
        }
    }

    // Copie des pixels de la zone choisie
    for (int i = 0; i < nouvelle_hauteur; i++) {
        for (int j = 0; j < nouvelle_largeur; j++) {
            int ligne_originale = (l1 - 1) + i;
            int colonne_originale = (c1 - 1) + j;
            sous_image->pixels[i][j] = image_originale->pixels[ligne_originale][colonne_originale];
        }
    }

    // Sauvegarde
    int succes = sauvegarder_fichier_ppm(sous_image, fichier_sortie);
    
    if (succes) {
        printf("Découpage réussi: %s créé (%d x %d pixels)\n", 
               fichier_sortie, nouvelle_largeur, nouvelle_hauteur);
    } else {
        printf("Erreur: Impossible de sauvegarder %s\n", fichier_sortie);
    }

    liberer_image(image_originale);
    liberer_image(sous_image);
    return succes;
}

// Fonction pour traiter la commande cut
void traiter_commande_cut(char *arguments[]) {
    if (arguments[1] == NULL || arguments[2] == NULL || arguments[3] == NULL || 
        arguments[4] == NULL || arguments[5] == NULL || arguments[6] == NULL) {
        printf("Usage: cut fichier.ppm l1 l2 c1 c2 fichier_resultat.ppm\n");
        printf("Exemple: cut image.ppm 1 50 1 100 resultat.ppm\n");
        return;
    }

    char *fichier_entree = arguments[1];
    int l1 = atoi(arguments[2]);
    int l2 = atoi(arguments[3]);
    int c1 = atoi(arguments[4]);
    int c2 = atoi(arguments[5]);
    char *fichier_sortie = arguments[6];

    decouper_image(fichier_entree, l1, l2, c1, c2, fichier_sortie);
}

// Fonction principale de traitement des commandes
void traiter_commande(char *ligne_commande) {
    char *arguments[10];
    int i = 0;
    
    char *token = strtok(ligne_commande, " \n");
    while (token != NULL && i < 10) {
        arguments[i++] = token;
        token = strtok(NULL, " \n");
    }
    arguments[i] = NULL;

    if (i == 0) return;

    if (strcmp(arguments[0], "cut") == 0) {
        traiter_commande_cut(arguments);
    }
    else if (strcmp(arguments[0], "size") == 0) {
        if (arguments[1] == NULL) {
            printf("Usage: size fichier.ppm\n");
        } else {
            afficher_taille(arguments[1]);
        }
    }
    else if (strcmp(arguments[0], "quit") == 0) {
        printf("Au revoir!\n");
        exit(0);
    }
    else {
        printf("Commande non reconnue: %s\n", arguments[0]);
        printf("Commandes disponibles: cut, size, quit\n");
    }
}

int main() {
    printf("Application de traitement d'images PPM\n");
    printf("Réalisée par [Votre Nom]\n");
    printf("Commandes disponibles: cut, size, quit\n\n");
    
    char ligne_commande[256];
    
    while (1) {
        printf("ppmviewer > ");
        
        if (fgets(ligne_commande, sizeof(ligne_commande), stdin) == NULL) {
            break;
        }
        
        traiter_commande(ligne_commande);
    }
    
    return 0;
}