// Fonction pour découper une image PPM
void decouper_image(const char *entree, int l1, int l2, int c1, int c2, const char *sortie) {
    // Lire l'image originale
    ImagePPM *original = lire_ppm(entree);
    if (!original) {
        printf("Erreur: Impossible de lire %s\n", entree);
        return;
    }

    // Validation des paramètres
    if (l1 < 1 || l2 > original->hauteur || l1 >= l2 || 
        c1 < 1 || c2 > original->largeur || c1 >= c2) {
        printf("Paramètres invalides! Image: %dx%d pixels\n", 
               original->largeur, original->hauteur);
        printf("Doit respecter: 1 <= l1 < l2 <= %d et 1 <= c1 < c2 <= %d\n",
               original->hauteur, original->largeur);
        liberer_image(original);
        return;
    }

    // Calcul des nouvelles dimensions
    int nouvelle_largeur = c2 - c1 + 1;
    int nouvelle_hauteur = l2 - l1 + 1;

    // Création de la sous-image
    ImagePPM sous_image;
    strcpy(sous_image.version, original->version);
    sous_image.largeur = nouvelle_largeur;
    sous_image.hauteur = nouvelle_hauteur;
    sous_image.max_val = original->max_val;
    
    // Allocation mémoire pour les pixels
    sous_image.pixels = (Pixel **)malloc(nouvelle_hauteur * sizeof(Pixel *));
    for (int i = 0; i < nouvelle_hauteur; i++) {
        sous_image.pixels[i] = (Pixel *)malloc(nouvelle_largeur * sizeof(Pixel));
    }

    // Copie de la zone sélectionnée
    for (int i = 0; i < nouvelle_hauteur; i++) {
        for (int j = 0; j < nouvelle_largeur; j++) {
            int ligne_orig = (l1 - 1) + i;
            int col_orig = (c1 - 1) + j;
            sous_image.pixels[i][j] = original->pixels[ligne_orig][col_orig];
        }
    }

    // Sauvegarde du résultat
    sauvegarder_ppm(&sous_image, sortie);
    printf("Découpage réussi: %s créé (%dx%d pixels)\n", 
           sortie, nouvelle_largeur, nouvelle_hauteur);
    
    // Libération mémoire
    for (int i = 0; i < nouvelle_hauteur; i++) {
        free(sous_image.pixels[i]);
    }
    free(sous_image.pixels);
    liberer_image(original);
}
