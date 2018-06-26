#include <stdio.h>
#include <time.h>
#include "visuel.h"
#include "initialisation.h"

void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font)
{
	SDL_Rect *rect;
	int iW, iH, i, j;
	SDL_Color     couleur  = {0, 0, 0, 255};
	SDL_Surface * surf;
	SDL_Texture * texture;
	char num[5];
	
	SDL_SetRenderDrawColor(*prenderer, 255, 255, 255, 0);
	rect = malloc(sizeof(SDL_Rect));
	rect->x = 0;
	rect->y = 0;
	rect->w = 800;
	rect->h = 400;
	SDL_RenderFillRect(*prenderer, rect );
	free(rect);
	
	surf     = TTF_RenderText_Blended(font, "Selectionnez un niveau : ", couleur);
	texture = SDL_CreateTextureFromSurface(*prenderer, surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(*prenderer, rect);
	rect->x = 0;
	rect->y = 0;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(*prenderer, texture, NULL, rect);
	free(rect);
	
	for(i =0; i<6; i++)
	{
		for(j=1; j<11; j++)
		{
			sprintf(num, "%d", i*10+j);
			surf     = TTF_RenderText_Blended(font, num, couleur);
			texture = SDL_CreateTextureFromSurface(*prenderer, surf);
			SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
			rect = malloc(sizeof(SDL_Rect));
			SDL_SetRenderDrawColor(*prenderer, 0, 150, 150, 255);
			rect->x = 30*j+30;
			rect->y = 30*(i+1)+30;
			rect->w = iW;
			rect->h = iH;
			SDL_RenderFillRect(*prenderer, rect);
			SDL_RenderCopy(*prenderer, texture, NULL, rect);
			free(rect);
		}
	}
	/*
	image=IMG_Load("fd.jpg");
	if(!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}

	avatar = SDL_CreateTextureFromSurface(*prenderer, image);
	SDL_FreeSurface(image);

	rect.x = 150;
	rect.y = 150;
	rect.w = rect.h = 200;
	SDL_RenderCopy(*prenderer, avatar, NULL, &rect);*/
	
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
	SDL_RenderPresent(*prenderer);
}

void fenetre(SDL_Window ** pwindow, int x, int y)
{
	*pwindow = SDL_CreateWindow("Niveau", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);
	if (*pwindow == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}
}

void cliqueSourisN(int x, int y, jeu_t * jeu, SDL_Window ** pwindow, SDL_Renderer ** prenderer, SDL_Window ** pwindow2, SDL_Renderer ** prenderer2)
{
	int niveau, dizaine=0, unite=0;
	SDL_DestroyRenderer(*prenderer);
	SDL_DestroyWindow(*pwindow);
	if(x>30 && x<360 && y>60 && y<240)
	{
		x-=30;
		while(x>29)
		{
			unite++;
			x-=30;
		}
		y-=60;
		while(y>29)
		{
			dizaine++;
			y-=30;
		}
		niveau = dizaine*10+unite;
		initialiserNiveau(jeu, niveau-1);
		
		fenetre(pwindow2, 500, 600);
	    *prenderer2 = SDL_CreateRenderer(*pwindow2, -1, SDL_RENDERER_ACCELERATED);
		plateau(prenderer2, jeu);
	}
}

void plateau(SDL_Renderer ** prenderer, jeu_t * jeu)
{
/*initialisation*/
	
	int ligne, colonne;

	int cmpt0 = 0;
	int cmpt1= 0;

	 
	SDL_Surface *plateau = NULL;
	SDL_Surface *figurine = NULL;
		
	plateau=IMG_Load("plateau.png");
	if(!plateau) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	affichefig (prenderer, plateau, 0, 100, 500, 500);
	
	for(ligne=0;ligne<=4;ligne++)
	{
		for(colonne=0;colonne<=4;colonne++)
		{			
			if( strcmp(jeu->plateau[ligne][colonne], "L0")==0 )
			{
				figurine=IMG_Load("lapin0.png");
				affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 100, 100);
				
			}
			else if( strcmp(jeu->plateau[ligne][colonne], "L1")==0 )
			{
				figurine=IMG_Load("lapin1.png");
				affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 100, 100);
				
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "L2")==0 )
			{
				figurine=IMG_Load("lapin2.png");
				affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 100, 100);
				
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "C ")==0 )
			{
				figurine=IMG_Load("champignon.png");
				affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 100, 100);
				
			}
			/* les renards*/
			else if (strcmp(jeu->plateau[ligne][colonne], "R0")==0 && cmpt0 == 0)
			{
				if(ligne<4 && strcmp(jeu->plateau[ligne+1][colonne], "R0")==0) 
				{
					figurine=IMG_Load("renardverticale.png");
					affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 100, 200);
					 
					
				}
				else 
				{
					figurine=IMG_Load("renardhorizontale.png");
					affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 200, 100);
					
					
				}
				cmpt0 = 1;
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "R1")==0 && cmpt1 == 0)
			{
				if(ligne<4 && strcmp(jeu->plateau[ligne+1][colonne], "R1")==0) 
				{
					figurine=IMG_Load("renardverticale.png");
					affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 100, 200);
					
				}
				else 
				{
					figurine=IMG_Load("renardhorizontale.png");
					affichefig (prenderer, figurine, colonne*100, 100 + ligne*100, 200, 100);
					
				}
				cmpt1 = 1;
			}
			
			
			
		}
	}
	/* L'image a ete copiee dans le renderer qui sera plus tard affiche a l'ecran */
	
	SDL_RenderPresent(*prenderer);
}

void affichefig (SDL_Renderer ** prenderer, SDL_Surface *figurine, int x, int y, int w, int h)
{
	SDL_Rect *rect;
	SDL_Texture  *avatar;
	
	avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
	SDL_FreeSurface(figurine);
	
	rect = malloc(sizeof(SDL_Rect));
	rect->x= x;
	rect->y = y;
	rect->w= w;
	rect->h= h;
	SDL_RenderCopy(*prenderer, avatar, NULL, rect);
	free(rect);
	
}

void principal(jeu_t * jeu)
{
	int running, width, height;
	SDL_Event event;
	SDL_Window   * window;
	SDL_Window   * window2;
	SDL_Renderer * renderer;
	SDL_Renderer * renderer2;
	TTF_Font * font;
	etat_fenetre_t etatFenetre;
	
	running = 1;
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		return;
	}
	if(TTF_Init() == -1)
	{
		fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
	}
	font = TTF_OpenFont("fake.receipt.ttf", 15);
	etatFenetre = NIVEAUX;
	fenetre(&window, 390, 270);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	remplirFenetreN(&renderer, font);
	if (renderer == 0) {
		 fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		 SDL_DestroyWindow(window);
		 TTF_CloseFont(font);
		 TTF_Quit();
		 SDL_Quit();
	}

	while (running) {

		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_WINDOWEVENT:
					printf("window event\n");
					switch (event.window.event)
					{
						case SDL_WINDOWEVENT_CLOSE:
							printf("appui sur la croix\n");
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							width = event.window.data1;
							height = event.window.data2;
							printf("Size : %d%d\n", width, height);
						default:
							printf("Default/n");
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					printf("Appui :%d %d\n", event.button.x, event.button.y);
					switch(etatFenetre)
					{
						case JEU:
							break;
						case NIVEAUX:
							cliqueSourisN(event.button.x, event.button.y, jeu, &window, &renderer, &window2, &renderer2);
							break;
					}
					break;
				case SDL_QUIT :
					printf("on quitte\n");
					running = 0;
			}
		}
		SDL_Delay(1); /*delai minimal*/
	}
	
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer2);
	SDL_DestroyWindow(window2);
	TTF_Quit();
	SDL_Quit();
}
