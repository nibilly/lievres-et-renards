#ifndef VISUEL_T
#define VISUEL_T

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "structures.h"

typedef enum {JEU, NIVEAUX, VICTOIRE}etat_fenetre_t;

void remplirFenetreN(TTF_Font *font);
void fenetre(SDL_Window ** pwindow, int x, int y);
void principal(jeu_t * jeu);
void plateau(jeu_t * jeu);
void affichefig (SDL_Surface *figurine, int x, int y, int w, int h);
int cliqueSourisN(int x, int y, jeu_t * jeu);
void cliquePlateau(int x, int y, jeu_t * jeu, TTF_Font * font, int niveau);
void boutons();

#endif
