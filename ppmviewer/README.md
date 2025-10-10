# TP-03 : Manipulateur d'Images PPM

Créer un programme en C capable de manipuler des images au format PPM (Portable Pixmap).

## Description

Ce projet implémente un outil en ligne de commande pour effectuer diverses opérations de traitement d'images sur des fichiers PPM. Le programme offre une interface interactive permettant d'appliquer des filtres, transformations et analyses sur les images.

## Fonctionnalités

- **Affichage de la taille** : Obtenir les dimensions (largeur x hauteur) d'une image
- **Conversion en niveaux de gris** : Transformer une image couleur en niveaux de gris
- **Négatif** : Inverser les couleurs de l'image
- **Contrôle de dominance colorée** : Éclaircir ou foncer les pixels dominants dans une couleur spécifique (Rouge, Vert, Bleu)
- **Découpage d'image** : Extraire une portion rectangulaire de l'image
- **Filtre médian** : Appliquer un filtre médian pour lisser l'image et réduire le bruit

## Contributions de l'Équipe

Le projet a été réalisé en collaboration par l'équipe suivante :

- **MASAD SHAID** : Implémentation du filtre médian (`fil.c`)
- **MERCIELLE MAEVA MINKENG YANA** : Implémentation de l'effet négatif (`neg.c`)
- **DANCHI KENFACK ABI GAËLLE LYDIA** : Implémentation de l'affichage de la taille (`tal.c`)
- **KENGNE GUEPOUOKSI PIERRE JOSUÉ** : Implémentation de l'éclaircissement/foncissement des pixels (`dom.c`)
- **FANTCHOM SIMO JULIE SUZANNE** : Implémentation de la conversion en niveaux de gris (`gris.c`)
- **MONET YANKWA BELOVED BRYAN** : Implémentation du découpage d'image (`cut.c`)

Tous les membres de l'équipe ont participé à l'élaboration du programme principal (`main.c`), incluant l'interface utilisateur, la gestion des commandes et l'intégration des différentes opérations.

## Organisation de l'Implémentation

Le projet est organisé selon une architecture modulaire :

- **`ppm.h` et `ppm.c`** : Gestion de base des images PPM (lecture, écriture, allocation mémoire)
- **`operations.h`** : Déclarations des fonctions d'opération
- **Fichiers spécialisés** : Chaque opération est implémentée dans son propre fichier source pour une meilleure séparation des responsabilités
- **`main.c`** : Interface en ligne de commande et orchestration des opérations
- **`makefile`** : Automatisation de la compilation

Cette organisation permet une maintenance facile et une réutilisabilité des composants.

## Prérequis

- Compilateur C (GCC recommandé)
- Système d'exploitation compatible (Linux, macOS, Windows avec MinGW)
- Fichiers d'images au format PPM (P6, binaire)

## Installation et Compilation

1. Naviguer vers le répertoire `src/` :
   ```
   cd ppmviewer/src
   ```

2. Compiler le programme :
   ```
   make all
   ```

   Cette commande génère l'exécutable `ppmviewer` (ou `ppmviewer.exe` sous Windows).

3. Pour nettoyer les fichiers objets :
   ```
   make clean
   ```

4. Pour nettoyer complètement (y compris les images générées) :
   ```
   make mrproper
   ```

## Utilisation

Après compilation, lancer le programme :

```
./ppmviewer
```

Le programme affiche un prompt `ppmviewer > ` où vous pouvez entrer les commandes.

### Commandes Disponibles

- `size <fichier.ppm>` : Affiche la taille de l'image (largeur x hauteur)
- `gris <entrée.ppm> <sortie.ppm>` : Convertit l'image en niveaux de gris
- `neg <entrée.ppm> <sortie.ppm>` : Crée le négatif de l'image
- `dom <R|G|B> <valeur> <fichier.ppm>` : Modifie la dominance colorée (valeur positive pour éclaircir, négative pour foncer)
- `cut <entrée.ppm> <ligne1> <ligne2> <colonne1> <colonne2> <sortie.ppm>` : Découpe une partie de l'image
- `fil <entrée.ppm> <sortie.ppm>` : Applique un filtre médian
- `menu` : Affiche l'aide des commandes
- `quit` : Quitte le programme

### Exemples d'Utilisation

Afficher la taille d'une image :
```
ppmviewer > size images/image1.ppm
```

Convertir en niveaux de gris :
```
ppmviewer > gris images/image1.ppm output/gris_image1.ppm
```

Appliquer un négatif :
```
ppmviewer > neg images/image1.ppm output/neg_image1.ppm
```

Éclaircir les pixels rouges dominants :
```
ppmviewer > dom R 50 images/image1.ppm
```

Découper une portion (lignes 100-200, colonnes 50-150) :
```
ppmviewer > cut images/image1.ppm 100 200 50 150 output/cut_image1.ppm
```

Appliquer un filtre médian :
```
ppmviewer > fil images/image1.ppm output/filtered_image1.ppm
```

## Structure du Projet

```
ppmviewer/
├── images/
│   ├── image1.ppm    # Image d'exemple 1
│   └── image2.ppm    # Image d'exemple 2
├── src/
│   ├── main.c        # Programme principal et interface utilisateur
│   ├── ppm.h         # En-têtes pour la gestion PPM
│   ├── ppm.c         # Implémentation de la gestion PPM
│   ├── operations.h  # En-têtes des opérations
│   ├── makefile      # Script de compilation
│   ├── tal.c         # Affichage de la taille
│   ├── dom.c         # Contrôle de dominance colorée
│   ├── gris.c        # Conversion en niveaux de gris
│   ├── neg.c         # Effet négatif
│   ├── cut.c         # Découpage d'image
│   ├── fil.c         # Filtre médian
│   └── ppmviewer.exe # Exécutable généré (Windows)
├── README.md         # Ce fichier
└── LICENSE           # Licence du projet
```

## Notes Techniques

- Le programme supporte uniquement le format PPM P6 (binaire)
- Les coordonnées pour le découpage commencent à 0
- Le filtre médian utilise une matrice 3x3 centrée sur chaque pixel
- Pour la dominance colorée, les valeurs vont typiquement de -255 à +255

## Membres

- MASAD SHAID - 24G2951
- MERCIELLE MAEVA MINKENG YANA - 24G2945
- DANCHI KENFACK ABI GAËLLE LYDIA - 24G2614
- KENGNE GUEPOUOKSI PIERRE JOSUÉ - 24H2486
- FANTCHOM SIMO JULIE SUZANNE - 24G2546
- MONET YANKWA BELOVED BRYAN - 24H2039

## Informations

```
*Cours*: INF 231_EC2
*Année*: 2025
*Responsable*: PR MELATAGIA Paulin
```