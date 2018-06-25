#ifndef VISUEL_T
#define VISUEL_T

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "structures.h"

void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font);
void fenetreNiveau(SDL_Window ** pwindow);
void principal(jeu_t * jeu);
void plateau(SDL_Renderer ** prenderer, jeu_t * jeu);

#endif
