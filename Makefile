# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes
LD=gcc
LDFLAGS=

# Files
PRODUIT_EXEC=produit
PUISSANCE_EXEC=puissance
PRODUIT_OBJECTS=source/matrice.o source/produit.o source/tri.o source/vecteur.o
PUISSANCE_OBJECTS=source/matrice.o source/valeur_propre.o source/vecteur.o

## Rules

all: $(PRODUIT_EXEC) $(PUISSANCE_EXEC)

$(PRODUIT_EXEC): $(PRODUIT_OBJECTS)
	$(CC) -o $(PRODUIT_EXEC) $(PRODUIT_OBJECTS) $(CFLAGS)

$(PUISSANCE_EXEC): $(PUISSANCE_OBJECTS)
	$(CC) -o $(PUISSANCE_EXEC) $(PUISSANCE_OBJECTS) $(CFLAGS)

source/%.o: source/%.c source/%.h
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f $(PRODUIT_OBJECTS) $(PUISSANCE_OBJECTS) $(PRODUIT_EXEC) $(PUISSANCE_EXEC) *~

.PHONY: all clean