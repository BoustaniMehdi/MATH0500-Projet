# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes -O3 -g 
LD=gcc
LDFLAGS=

# Files
PRODUIT_EXEC=multiplication
PUISSANCE_EXEC=vecteur
PRODUIT_OBJECTS=source/matrice.o source/produit.o source/tri.o source/vecteur.o source/valeur_propre.o
PUISSANCE_OBJECTS=source/matrice.o source/valeur_propre.o source/produit.o source/tri.o source/vecteur.o
MAIN_FILE=source/main.c

## Rules

all: $(PRODUIT_EXEC) $(PUISSANCE_EXEC)

$(PRODUIT_EXEC): $(PRODUIT_OBJECTS)
	$(CC) -o $(PRODUIT_EXEC) $(PRODUIT_OBJECTS) $(MAIN_FILE) $(CFLAGS)

$(PUISSANCE_EXEC): $(PUISSANCE_OBJECTS)
	$(CC) -o $(PUISSANCE_EXEC) $(PUISSANCE_OBJECTS) $(MAIN_FILE) $(CFLAGS)

source/%.o: source/%.c source/%.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(PRODUIT_OBJECTS) $(PUISSANCE_OBJECTS) $(PRODUIT_EXEC) $(PUISSANCE_EXEC) *~

.PHONY: all clean
