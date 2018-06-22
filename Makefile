all: main

clean:
	-rm main.o moteur.o initialisation.o main

main: main.o moteur.o initialisation.o
	gcc -Wall -Wextra -ansi -pedantic -g -o main main.o moteur.o initialisation.o

main.o: main.c moteur.h initialisation.h
	gcc -Wall -Wextra -ansi -pedantic -g -c main.c
	
moteur.o: moteur.c moteur.h
	gcc -Wall -Wextra -ansi -pedantic -g -c moteur.c
	
initialisation.o: initialisation.c initialisation.h
	gcc -Wall -Wextra -ansi -pedantic -g -c initialisation.c