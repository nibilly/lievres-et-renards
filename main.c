#include <stdio.h>
#include <string.h>

#include "structures.h"
#include "moteur.h"
#include "initialisation.h"
#include "visuel.h"

int main()
{
	
    jeu_t * jeu;
    jeu = declarerJeu();
    
    principal(jeu);
    return 0;
}
