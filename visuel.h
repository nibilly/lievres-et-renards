#ifndef VISUEL_T
#define VISUEL_T

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

typedef enum {JEU, NIVEAUX}etat_fenetre_t;

void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font);
void fenetreNiveau(SDL_Window ** pwindow);
void principal();

#endif
