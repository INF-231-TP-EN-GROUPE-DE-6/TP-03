#include <stdio.h>
#include "ppm.h"

// ==================== MENU INTERACTIF ====================
void afficher_menu() {
    printf("\n========================================\n");
    printf(" APPLICATION PPM VIEWER\n");
    printf("========================================\n");
    printf("Commandes disponibles :\n\n");
    printf(" 1. dom <couleur> <valeur> <fichier.ppm>\n");
    printf(" Foncer/éclaircir les pixels dominants\n");
    printf(" Couleur : R, G ou B\n");
    printf(" Valeur : positive (foncer) ou négative (éclaircir)\n\n");
    printf(" 2. gris <fichier.ppm>\n");
    printf(" Convertir en niveaux de gris\n\n");
    printf(" 3. neg <fichier_entree.ppm> <fichier_sortie.ppm>\n");
    printf(" Créer le négatif de l'image\n\n");
    printf(" 4. size <fichier.ppm>\n");
    printf(" Afficher la taille de l'image\n\n");
    printf(" 5. cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>\n");
    printf(" Découper une partie de l'image\n\n");
    printf(" 6. fil <fichier_entree.ppm> <fichier_sortie.ppm>\n");
    printf(" Appliquer le filtre médian\n\n");
    printf(" help - Afficher ce menu\n");
    printf(" quit - Quitter l'application\n");
    printf("========================================\n\n");
}

// ==================== MAIN ====================
int main() {
    char commande[512];
    char cmd[20];
    printf("\n====================================================\n");
    printf("|| Application de traitement d'images PPM ║\n");
    printf("||======================================================\n");
    printf("\nTapez 'help' pour voir les commandes disponibles\n");
    while (1) {
        printf("\nppmviewer> ");
        if (fgets(commande, sizeof(commande), stdin) == NULL) {
            break;
        }
        // Supprimer le retour à la ligne
        commande[strcspn(commande, "\n")] = 0;
        // Ignorer les lignes vides
        if (strlen(commande) == 0) {
            continue;
        }
        // Analyser la commande
        sscanf(commande, "%s", cmd);
        // QUIT
        if (strcmp(cmd, "quit") == 0) {
            printf("\nMerci d'avoir utilisé PPM Viewer. Au revoir !\n\n");
            break;
        }
        // HELP
        else if (strcmp(cmd, "help") == 0) {
            afficher_menu();
        }
        // DOM - Dominante
        else if (strcmp(cmd, "dom") == 0) {
            char couleur, fichier[256];
            int valeur;
            if (sscanf(commande, "%s %c %d %s", cmd, &couleur, &valeur, fichier) == 4) {
                couleur = toupper(couleur);
                if (couleur == 'R' || couleur == 'G' || couleur == 'B') {
                    operation_dominante(fichier, couleur, valeur);
                } else {
                    printf("Erreur : la couleur doit être R, G ou B\n");
                }
            } else {
                printf("Usage : dom <couleur> <valeur> <fichier.ppm>\n");
            }
        }
        // GRIS - Niveaux de gris
        else if (strcmp(cmd, "gris") == 0) {
            char fichier[256];
            if (sscanf(commande, "%s %s", cmd, fichier) == 2) {
                operation_gris(fichier);
            } else {
                printf("Usage : gris <fichier.ppm>\n");
            }
        }
        // NEG - Négatif
        else if (strcmp(cmd, "neg") == 0) {
            char fichier_entree[256], fichier_sortie[256];
            if (sscanf(commande, "%s %s %s", cmd, fichier_entree, fichier_sortie) == 3) {
                operation_negatif(fichier_entree, fichier_sortie);
            } else {
                printf("Usage : neg <fichier_entree.ppm> <fichier_sortie.ppm>\n");
            }
        }
        // SIZE - Taille
        else if (strcmp(cmd, "size") == 0) {
            char fichier[256];
            if (sscanf(commande, "%s %s", cmd, fichier) == 2) {
                operation_taille(fichier);
            } else {
                printf("Usage : size <fichier.ppm>\n");
            }
        }
        // CUT - Découper
        else if (strcmp(cmd, "cut") == 0) {
            char fichier_entree[256], fichier_sortie[256];
            int l1, l2, c1, c2;
            if (sscanf(commande, "%s %s %d %d %d %d %s",
                       cmd, fichier_entree, &l1, &l2, &c1, &c2, fichier_sortie) == 7) {
                operation_decouper(fichier_entree, l1, l2, c1, c2, fichier_sortie);
            } else {
                printf("Usage : cut <fichier.ppm> <l1> <l2> <c1> <c2> <fichier_sortie.ppm>\n");
            }
        }
        // FIL - Filtre médian
        else if (strcmp(cmd, "fil") == 0) {
            char fichier_entree[256], fichier_sortie[256];
            if (sscanf(commande, "%s %s %s", cmd, fichier_entree, fichier_sortie) == 3) {
                operation_filtre_median(fichier_entree, fichier_sortie);
            } else {
                printf("Usage : fil <fichier_entree.ppm> <fichier_sortie.ppm>\n");
            }
        }
        // Commande inconnue
        else {
            printf("Commande inconnue : '%s'. Tapez 'help' pour voir les commandes.\n", cmd);
        }
    }
    return 0;
}