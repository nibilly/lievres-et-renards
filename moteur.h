#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "structures.h"

void deplacer(jeu_t * jeu, objet_t objet, int numero, int ligne, int colonne);

void afficher(jeu_t * jeu);

int verifplateau (int ligne, int colonne);
int verifPasObstacle(jeu_t * jeu, int ligne, int colonne);
int verifLapin(jeu_t * jeu, int numero, int ligne, int colonne);

void moteurJeu(jeu_t * jeu, int niveau);
int estGagne(jeu_t * jeu);

#endif
