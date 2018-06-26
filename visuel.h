#ifndef VISUEL_T
#define VISUEL_T

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "structures.h"

typedef enum {JEU, NIVEAUX}etat_fenetre_t;

void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font);
void fenetre(SDL_Window ** pwindow, int x, int y);
void principal(jeu_t * jeu);
void plateau(SDL_Renderer ** prenderer, jeu_t * jeu);
void affichefig (SDL_Renderer ** prenderer, SDL_Surface *figurine, int x, int y, int w, int h);
int cliqueSourisN(int x, int y, jeu_t * jeu, SDL_Window ** pwindow, SDL_Renderer ** prenderer, SDL_Window ** pwindow2, SDL_Renderer ** prenderer2);
void cliquePlateau(int x, int y, jeu_t * jeu, SDL_Window ** pwindow, SDL_Renderer ** prenderer, SDL_Window ** pwindow2, SDL_Renderer ** prenderer2, TTF_Font * font, int niveau);
void boutons(SDL_Renderer ** prenderer);

#endif
