# Tools & flags
CC=gcc
CFLAGS=--std=c99 --pedantic -Wall -W -Wmissing-prototypes

# Files
EXEC=main
OBJECTS=main.o lecture.o produit.o valeur_propre.o

## Rules

all: $(EXEC)

main: $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS) $(CFLAGS)

main.o: source/main.c source/lecture.h source/produit.h source/valeur_propre.h
	$(CC) -c $< $(CFLAGS)

lecture.o: source/lecture.c source/lecture.h
	$(CC) -c $< $(CFLAGS) 

produit.o: source/produit.c source/produit.h
	$(CC) -c $< $(CFLAGS) 

valeur_propre.o: source/valeur_propre.c source/valeur_propre.h
	$(CC) -c $< $(CFLAGS) 

clean:
	rm -f *.o main