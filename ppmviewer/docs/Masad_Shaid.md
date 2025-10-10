## Rapport Personnel - MASAD SHAID 

Dans ce TP, la fonction de filtre médian (filtreMedian) a été implémentée dans `src/fil.c`. Elle applique un noyau 3x3 pour réduire le bruit "sel et poivre". La méthode utilisée consiste à : effectuer une copie de l'image avec decouper(...), parcourir chaque pixel (en excluant les bords), rassembler les 9 valeurs du voisinage pour chaque canal R, G, B, trier ces valeurs de façon simple et remplacer la valeur du pixel par la médiane. La copie est ensuite libérée avec `libererImage(...)`.

Contributions complémentaires :
- Intégration de la commande correspondante dans `main.c`.
- Rédaction de la documentation et des explications d'utilisation.

Limites identifiées :
- Les bords ne sont pas modifiés.
- Tri simple peu optimisé (complexité élevée pour de grandes images).
- Pas de vérification explicite que decouper retourne non-NULL avant usage dans certaines versions.
- Conçu pour canaux 8 bits ; pas d'optimisation mémoire/temps.

Utilisation :
`ppmviewer> fil <nom_du_fichier_entrant> <nom_du_fichier_sortant>`
