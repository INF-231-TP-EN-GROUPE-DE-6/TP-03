# Rapport Personnel - KENGNE GUEPOUOKSI PIERRE JOSUÉ

Dans ce 3 ème TP, j'ai principalement implémenté la fonction de dominance colorée (`dom.c`), permettant d'éclaircir ou foncer les pixels dominants dans une couleur donnée (R, V, B). Le procédé utilisé consiste à parcourir chaque pixel de l'image, déterminer la composante dominante (celle ayant la valeur la plus élevée parmi R, G, B), et si elle correspond à la couleur spécifiée, ajuster uniformément les trois composantes RGB par la valeur donnée, tout en les bornant entre 0 et la valeur maximale de l'image pour éviter les débordements.

J'ai aussi participé à la création du programme principal (`main.c`), en contribuant à l'interface utilisateur, au menu d'aide. Enfin, je me suis occupé de la documentation (`README.md`).

Le défi principal était de définir la "dominance" d'un pixel ; j'ai opté pour une approche simple basée sur la comparaison des composantes.