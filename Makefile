CFLAGS = -Wall -Wextra -ansi -pedantic -g 

SDL = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net

all: main

clean:
	-rm main.o moteur.o initialisation.o visuel.o main

main: main.o moteur.o initialisation.o visuel.o
	gcc $(CFLAGS) -o main main.o moteur.o visuel.o initialisation.o $(SDL)

main.o: main.c moteur.h initialisation.h visuel.h
	gcc $(CFLAGS) -c main.c $(SDL)
	
moteur.o: moteur.c moteur.h
	gcc $(CFLAGS) -c moteur.c 
	
initialisation.o: initialisation.c initialisation.h
	gcc $(CFLAGS) -c initialisation.c

visuel.o: visuel.c visuel.h
	gcc $(CFLAGS) -c visuel.c $(SDL)
