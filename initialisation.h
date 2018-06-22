#ifndef INITIALISATION_H
#define INITIALISATION_H

#include "structures.h"

jeu_t * declarerJeu();
char *** initTrous();

void liberer(jeu_t * jeu);
void libererTrous(char *** trous);

void initialiserNiveau(jeu_t * jeu, int n);

#endif