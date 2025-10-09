#include "ppm.h"
void operation_taille(const char *fichier) {
    ImagePPM *image = lire_ppm(fichier);
    if (!image) {
        printf("fichier non trouvé\n");
        return;
    }
    printf("%d x %d\n", image->largeur, image->hauteur);
    liberer_image(image);
}
