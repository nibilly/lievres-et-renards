#include <stdio.h>

#include "structures.h"
#include "moteur.h"
#include "initialisation.h"

int main()
{
    jeu_t * jeu;
    int niveau = 2;/*de 0 à n-1*/
    jeu = declarerJeu();
    initialiserNiveau(jeu, niveau);
    /*jeu->renards[1].orientation = HORIZONTALE;
    jeu->renards[0].orientation = HORIZONTALE;
    
    deplacer(jeu, RENARD, 1, 3, 1);*//*dabord la tete vers le haut ou la droite*/
    /*deplacer(jeu, RENARD, 1, 3, 0);
    deplacer(jeu, RENARD, 0, 1, 4);
    deplacer(jeu, RENARD, 0, 1, 3);*/
    /*deplacer(jeu, CHAMPIGNON, 0, 1, 1);
    */
    /*jeu->lapins[0].position->x = 0;
    jeu->lapins[0].position->y = 0;
    strcpy(jeu->plateau[0][0], "L0");
    jeu->lapins[1].position->x = 1;
    jeu->lapins[1].position->y = 1;
    strcpy(jeu->plateau[1][1], "L1");*/
    /*deplacer(jeu, LAPIN, 1, 3, 3);
    deplacer(jeu, LAPIN, 2, 0, 1);*/
    /*if ( jeu->lapins[2].estSauve == 0)*//*par defaut == 0*/ 
    /*{
        printf("ok");
    }
    else
    {
        printf("nop");
    }
    */
    moteurjeu(jeu, niveau);
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
