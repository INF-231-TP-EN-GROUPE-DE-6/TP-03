# RAPPORT PERSONNEL de FANTCHOM SIMO JULIE SUZANNE

Dans le cadre du projet de traitement d’images en C, ma tâche a consisté à réaliser un programme permettant de convertir une image couleur en noir et blanc.
Le fichier que j’ai développé s’intitule niv_gris.c et représente ma partie personnelle du projet.
L’objectif est de transformer chaque pixel de l’image, défini par trois composantes (R, G, B), en un ton de gris unique.
Pour cela, j’ai appliqué le principe des niveaux de gris en calculant la moyenne des trois valeurs :

gris = \frac{R + G + B}{3}

Le programme suit trois étapes principales : lecture du fichier PPM, conversion des pixels et écriture du nouveau fichier.
Avant d’implémenter le code, j’ai d’abord travaillé sur papier pour concevoir la logique générale et l’algorithme de parcours des pixels.
L’implémentation en langage C m’a permis de manipuler les structures, les pointeurs et la mémoire dynamique.
Des tests ont ensuite été réalisés avec plusieurs fichiers .ppm pour vérifier la fidélité du rendu obtenu.
Cette partie m’a aidée à mieux comprendre le fonctionnement interne d’une image numérique et la notion de composantes R, G, B.
Le programme se compile avec la commande gcc niv_gris.c -o niv_gris et s’exécute via ./niv_gris image_couleur.ppm image_gris.ppm.
Il constitue une étape essentielle du projet global de visualisation et de manipulation d’images PPM.
Ce travail allie rigueur algorithmique et précision numérique, tout en illustrant une application concrète du traitement d’images en C.
