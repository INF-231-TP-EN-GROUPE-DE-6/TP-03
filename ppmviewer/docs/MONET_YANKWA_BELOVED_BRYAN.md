Rapport Personnel - MONET YANKWA BELOVED BRYAN

Dans ce TP, la fonction de découpage d'image (decouper) a été implémentée dans src/cut.c. Le rôle de la fonction est d'extraire une sous-image rectangulaire [l1..l2-1] x [c1..c2-1] depuis une image PPM source et de retourner une nouvelle Image allouée contenant uniquement cette zone.

La méthode utilisée :
- Validation des bornes d'entrée pour s'assurer qu'elles sont dans l'intervalle et correctement ordonnées. En cas d'erreur, la fonction signale "coordonnées invalides" et retourne NULL.
- Allocation d'une nouvelle structure Image et d'un tableau de lignes (pixels) de la taille demandée.
- Copie pixel par pixel de la région demandée depuis l'image source vers la nouvelle image.
- Retour de la sous-image allouée pour usage ultérieur (à libérer avec libererImage()).

Contributions complémentaires :
- Participation au programme principal (main.c) en veillant à l'intégration de la commande cut et à la gestion des retours NULL.
- Rédaction de la documentation (README.md) décrivant l'usage et les limites.

Limites identifiées :
- Vérification d'échec d'allocation mémoire non exhaustive (possibilité de plantage si malloc retourne NULL).
- Indices basés sur 0 ; l2 et c2 sont exclusifs dans la copie.
- Nécessité pour l'appelant de libérer la sous-image pour éviter des fuites mémoires.

Proposition d'amélioration :
- Ajouter des vérifications des retours de malloc et gérer proprement les erreurs d'allocation.
- Documenter clairement la convention d'indices (inclusif/exclusif) pour éviter les confusions.
