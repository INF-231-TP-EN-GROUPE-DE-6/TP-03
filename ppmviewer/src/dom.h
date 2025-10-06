#ifndef DOM_H
#define DOM_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// Représentation minimale d'une image PPM maintenue en mémoire.
// - maxval doit être <= 255 (stockage sur 8 bits)
// - data contient les pixels au format RGBRGB... (3 octets par pixel)
typedef struct {
    int width;      // largeur en pixels
    int height;     // hauteur en pixels
    int maxval;     // valeur maximale d'intensité (habituellement 255)
    uint8_t *data;  // tampon de taille width * height * 3
} PPMImage;

/*
 * Augmente la dominante d'une couleur sur une image PPM en mémoire (in-situ).
 *
 * Paramètres:
 *  - img: pointeur vers l'image PPM (doit être non NULL et correctement initialisée)
 *  - canal: 'r'/'R' (rouge), 'g'/'G' ou 'v'/'V' (vert), 'b'/'B' (bleu)
 *  - pourcentage: valeur entre 0.0 et 1.0 représentant la proportion de la marge
 *                 restante jusqu'à maxval ajoutée au canal choisi.
 *                 Exemple: 0.2 -> nouveau = ancien + 0.2 * (maxval - ancien)
 *
 * Retour:
 *  - 0 en cas de succès
 *  - -1 si les arguments sont invalides ou non supportés (ex: maxval > 255)
 */
int dom_augmenter_dominante(PPMImage *img, char canal, float pourcentage);

#ifdef __cplusplus
}
#endif

#endif // DOM_H
