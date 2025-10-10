# Rapport Personnel - MASAD SHAID
## 1) Titre
Filtre médian 3x3 pour réduire le bruit.

## 2) Objectif
Améliorer la qualité d'image en supprimant les pixels impulsionnels.

## 3) Placement 
Fichier : src/fil.c  
Fonction principale : `void filtreMedian(Image *img)`

## 4) Principe (simple)
- Pour chaque pixel (sauf bords) : on prend un voisinage 3x3.  
- On trie les 9 valeurs pour chaque canal R, G, B.  
- On remplace la valeur par la médiane.

## 5) Détails d'implémentation
- Utilise `decouper(...)` pour copier l'image avant traitement.  
- Libère la copie avec `libererImage(...)`.  
- Bords non modifiés (boucles de 1 à hauteur-2 / largeur-2).

## 6) Utilisation rapide
1. Charger une Image `img`.  
2. Appeler `filtreMedian(img);`  
3. Sauvegarder l'image modifiée.

## 7) Limites
- Noyau fixe 3x3.  
- Tri simple (pas optimisé).  
- Bords non traités.  
- Conçu pour canaux 8 bits.

## 8) Utilisation en application
`ppmviewer> fil <nom_du_fichier_entrain> <nom_du_fichier_sortant>`

