#include <stdio.h>

#include "structures.h"
#include "moteur.h"
#include "initialisation.h"
#include "visuel.h"

int main()
{
	
    jeu_t * jeu;
    jeu = declarerJeu();
    
    principal(jeu);
    
    /*moteurjeu(jeu, niveau);*/
    /*jeu->lapins[0].position->x = 0;
    jeu->lapins[0].position->y = 0;
    jeu->renards[1].tete->x = 1;
    jeu->renards[1].tete->y = 2;
    jeu->renards[1].queue->x = 1;
    jeu->renards[1].queue->y = 3;
    jeu->champignons[2].position->x = 4;
    jeu->champignons[2].position->y = 4;*/
    /*
    printf("%d\n", jeu->lapins[0].position->x);
    printf("%d\n", jeu->lapins[0].position->y);
    printf("%d\n", jeu->renards[1].tete->x);
    printf("%d\n", jeu->renards[1].tete->y);
    printf("%d\n", jeu->renards[1].queue->x);
    printf("%d\n", jeu->renards[1].queue->y);
    printf("%d\n", jeu->champignons[2].position->x);
    printf("%d\n", jeu->champignons[2].position->y);
    afficher(jeu);
    */
    liberer(jeu);
    
    return 0;
}
