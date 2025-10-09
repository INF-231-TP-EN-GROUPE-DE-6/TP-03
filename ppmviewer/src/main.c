#include <stdio.h>
#include <string.h>
#include "ppm.h"
#include "operations.h"

// Affiche le menu d’aide
void afficherMenu() {
    printf("\n===================MENU DES COMMANDES ========================================\n");
    printf("size <fichier.ppm>                : Affiche la taille de l'image (largeur x hauteur)\n");
    printf("gris <fichier.ppm> <sortie.ppm>   : Convertit l'image en niveaux de gris et crée <fichier.ppm_gris.ppm>\n");
    printf("neg <entrée.ppm> <sortie.ppm>     : Crée le négatif de l'image\n");
    printf("dom <R|G|B> <val> <fichier.ppm>   : Fonce ou éclaircit les pixels dominants dans une couleur\n");
    printf("cut <entrée.ppm> <l1> <l2> <c1> <c2> <sortie.ppm> : Découpe une partie de l'image\n");
    printf("fil <entrée.ppm> <sortie.ppm>     : Applique un filtre médian (lisse l'image)\n");
    printf("menu                              : Affiche ce menu d'aide\n");
    printf("quit                              : Quitte le programme\n");
    printf("============================================================================\n\n");
}

int main() {
   printf("\n====================================================\n");
    printf("|| Application de traitement d'images PPM ║\n");
    printf("||======================================================\n");
    printf("\nTapez 'menu' pour voir les commandes disponibles\n");

    char cmd[50];
    while (1) {
        printf("ppmviewer > ");
        scanf("%s", cmd);

        if (strcmp(cmd, "quit") == 0)
            break;

        else if (strcmp(cmd, "menu") == 0)
            afficherMenu();

        else if (strcmp(cmd, "size") == 0) {
            char fichier[100];
            scanf("%s", fichier);
            Image *img = lirePPM(fichier);
            if (img) {
                afficherTaille(img);
                libererImage(img);
            }
        }

        else if (strcmp(cmd, "gris") == 0) {
            char in[100], out[100];
            scanf("%s %s", in, out);
            Image *img = lirePPM(in);
            if (img) {
                toGray(img);
                ecrirePPM(out, img);
                printf("opération effectuée ; %s créé\n", out);
                libererImage(img);
            }
        }

        else if (strcmp(cmd, "neg") == 0) {
            char in[100], out[100];
            scanf("%s %s", in, out);
            Image *img = lirePPM(in);
            if (img) {
                negatif(img);
                ecrirePPM(out, img);
                printf("opération effectuée\n");
                libererImage(img);
            }
        }

        else if (strcmp(cmd, "dom") == 0) {
            char c; int val; char fichier[100];
            scanf(" %c %d %s", &c, &val, fichier);
            Image *img = lirePPM(fichier);
            if (img) {
                dominante(img, c, val);
                char out[120];
                sprintf(out, "%s_dom.ppm", fichier);
                ecrirePPM(out, img);
                printf("opération effectuée ; %s créé\n", out);
                libererImage(img);
            }
        }

        else if (strcmp(cmd, "cut") == 0) {
            char in[100], out[100];
            int l1, l2, c1, c2;
            scanf("%s %d %d %d %d %s", in, &l1, &l2, &c1, &c2, out);
            Image *img = lirePPM(in);
            if (img) {
                Image *part = decouper(img, l1, l2, c1, c2);
                if (part) {
                    ecrirePPM(out, part);
                    printf("opération effectuée\n");
                    libererImage(part);
                }
                libererImage(img);
            }
        }

        else if (strcmp(cmd, "fil") == 0) {
            char in[100], out[100];
            scanf("%s %s", in, out);
            Image *img = lirePPM(in);
            if (img) {
                filtreMedian(img);
                ecrirePPM(out, img);
                printf("opération effectuée\n");
                libererImage(img);
            }
        }

        else
            printf("Commande inconnue. Tapez 'menu' pour voir les commandes disponibles.\n");
    }

    printf("Programme terminé.\n");
    return 0;
}