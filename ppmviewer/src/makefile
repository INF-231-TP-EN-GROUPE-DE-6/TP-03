# Nom de l'exécutable
EXEC = ppmviewer

# Tous les fichiers sources (.c)
SRC = main.c ppm.c gris.c neg.c dom.c cut.c fil.c tal.c

# Tous les fichiers objets (.o)
OBJ = $(SRC:.c=.o)

# Options du compilateur
CC = gcc
CFLAGS = -Wall -std=c11

# Règle principale
all: $(EXEC)

# Création de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Compilation des .c en .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f *.o $(EXEC)

# Nettoyer les fichiers générés (.ppm ou autres si besoin)
mrproper: clean
	rm -f *.ppm

