#include <stdio.h>
#include <stdlib.h>
int main() {

    FILE *fichier;
    fichier = fopen("C:\\Users\\NICK-TECH\\Documents\\GitHub\\TP-03\\ppmviewer\\Images\\test1.ppm", "r");
    if(fichier == NULL){
        printf("erreur lors de louverture du fichier");
        return 1;
    }
char ligne[150];
int compteur =0;
while (fgets(ligne, sizeof(ligne), fichier) !=NULL){
   compteur++;
    // Ignorer les lignes de commentaires ou vides
    if (ligne[0] == '#' || ligne[0] == '\n') {
        continue;
    }

    // Tenter d'extraire deux entiers (ex: "800 600")
    int val1 = 0, val2 = 0;
    if (sscanf(ligne, "%d %d", &val1, &val2) == 2) {
        // L'utilisateur veut afficher la première valeur comme hauteur
        // et la deuxième comme largeur
        printf("hauteur: %d largeur: %d\n", val1, val2);
        break;
    }

}
fclose(fichier);
return 0;
}