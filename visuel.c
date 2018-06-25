#include <stdio.h>
#include "visuel.h"


void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font)
{
	SDL_Rect *rect;
	SDL_Texture  *avatar;
	SDL_Surface *image = NULL;
	int iW, iH, i, j;
	SDL_Color     couleur  = {0, 0, 0, 255};
	SDL_Surface * surf;
	SDL_Texture * texttext;
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
	texttext = SDL_CreateTextureFromSurface(*prenderer, surf);
	SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(*prenderer, rect);
	rect->x = 0;
	rect->y = 0;
	rect->w = 0+iW;
	rect->h = 0+iH;
	SDL_RenderCopy(*prenderer, texttext, NULL, rect);
	free(rect);
		
	for(i =1; i<7; i++)
	{
		for(j=0; j<10; j++)
		{
			sprintf(num, "%d", i*10+j);
			surf     = TTF_RenderText_Blended(font, num, couleur);
			texttext = SDL_CreateTextureFromSurface(*prenderer, surf);
			SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
			rect = malloc(sizeof(SDL_Rect));
			SDL_RenderFillRect(*prenderer, rect);
			rect->x = 40*j;
			rect->y = 40*i;
			rect->w = 40*j+iW;
			rect->h = 40*i+iH;
			SDL_RenderCopy(*prenderer, texttext, NULL, rect);
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
	
	SDL_RenderPresent(*prenderer);
}

void fenetreNiveau(SDL_Window ** pwindow)
{
	*pwindow = SDL_CreateWindow("Niveau", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 600, 0);
	if (*pwindow == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}
}

void CreerFenetre(SDL_Window ** pwindow)
{
	int flags=IMG_INIT_JPG|IMG_INIT_PNG;
	int initted= 0;

	initted = IMG_Init(flags);

	if((initted&flags) != flags)
	{
		printf("IMG_Init: Impossible d'initialiser le support des formats JPG et PNG requis!\n");
		printf("IMG_Init: %s\n", IMG_GetError());
	}

	*pwindow = SDL_CreateWindow("SDL2 Programme 0.1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		        400, 500,
		        SDL_WINDOW_RESIZABLE);

	if (*pwindow == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		/* on peut aussi utiliser SLD_Log() */
	}
	
}


void plateau(SDL_Renderer ** prenderer, jeu_t * jeu)
{
/*initialisation*/
	
	int ligne, colonne;
	int cmpt0 = 0;
	int cmpt1= 0;
	SDL_Rect *rect;

	
	SDL_Texture  *avatar;

	
	SDL_Surface *plateau = NULL;
	SDL_Surface *figurine = NULL;
	
	
/*chargement des images avec vérifications*/	
	plateau=IMG_Load("plateau.png");
	if(!plateau) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	avatar = SDL_CreateTextureFromSurface(*prenderer, plateau);
	SDL_FreeSurface(plateau);
	
	rect = malloc(sizeof(SDL_Rect));
	rect->x = 0;
	rect->y = 100;
	rect->w = 500;
	rect->h = 500;
	SDL_RenderCopy(*prenderer, avatar, NULL, rect);
	free(rect);
	
	
	
	
	for(ligne=0;ligne<=4;ligne++)
	{
		for(colonne=0;colonne<=4;colonne++)
		{
			
			
			
			
			
			if( strcmp(jeu->plateau[ligne][colonne], "L0")==0 )
			{
				figurine=IMG_Load("lapin0.png");
				avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
				SDL_FreeSurface(figurine);
				
				rect = malloc(sizeof(SDL_Rect));
				rect->x= ligne*100;
				rect->y = 100 + colonne*100;
				rect->w=100;
				rect->h=100;
				SDL_RenderCopy(*prenderer, avatar, NULL, rect);
				free(rect);
			}
			else if( strcmp(jeu->plateau[ligne][colonne], "L1")==0 )
			{
				figurine=IMG_Load("lapin1.png");
				avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
				SDL_FreeSurface(figurine);
				
				rect = malloc(sizeof(SDL_Rect));
				rect->x= ligne*100;
				rect->y = 100 + colonne*100;
				rect->w=100;
				rect->h=100;
				SDL_RenderCopy(*prenderer, avatar, NULL, rect);
				free(rect);
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "L2")==0 )
			{
				figurine=IMG_Load("lapin2.png");
				avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
				SDL_FreeSurface(figurine);
				
				rect = malloc(sizeof(SDL_Rect));
				rect->x= ligne*100;
				rect->y = 100 + colonne*100;
				rect->w=100;
				rect->h=100;
				SDL_RenderCopy(*prenderer, avatar, NULL, rect);
				free(rect);
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "C ")==0 )
			{
				figurine=IMG_Load("champignon.png");
				avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
				SDL_FreeSurface(figurine);
				
				rect = malloc(sizeof(SDL_Rect));
				rect->x= ligne*100;
				rect->y = 100 + colonne*100;
				rect->w=100;
				rect->h=100;
				SDL_RenderCopy(*prenderer, avatar, NULL, rect);
				free(rect);
				
			}
			/* les renards*/
			else if (strcmp(jeu->plateau[ligne][colonne], "R0")==0 && cmpt0 == 0)
			{
				if(ligne<4 && strcmp(jeu->plateau[ligne+1][colonne], "R0")==0) /*renard 0 est horizontale*/
				{
					figurine=IMG_Load("renardhorizontale.png");
					avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
					SDL_FreeSurface(figurine);
					
					rect = malloc(sizeof(SDL_Rect));
					rect->x= ligne*100;
					rect->y = 100 + colonne*100;
					rect->w=200;
					rect->h=100;
					SDL_RenderCopy(*prenderer, avatar, NULL, rect);
					free(rect);
					
				}
				else /*renard 0 est verticale*/
				{
					figurine=IMG_Load("renardverticale.png");
					avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
					SDL_FreeSurface(figurine);
					
					rect = malloc(sizeof(SDL_Rect));
					rect->x= ligne*100;
					rect->y = 100 + colonne*100;
					rect->w=100;
					rect->h=200;
					SDL_RenderCopy(*prenderer, avatar, NULL, rect);
					free(rect);
					
				}
				cmpt0 = 1;
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "R1")==0 && cmpt1 == 0)
			{
				if(ligne<4 && strcmp(jeu->plateau[ligne+1][colonne], "R1")==0) /*renard 1 est horizontale*/
				{
					figurine=IMG_Load("renardhorizontale.png");
					avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
					SDL_FreeSurface(figurine);
					
					rect = malloc(sizeof(SDL_Rect));
					rect->x= ligne*100;
					rect->y = 100 + colonne*100;
					rect->w=200;
					rect->h=100;
					SDL_RenderCopy(*prenderer, avatar, NULL, rect);
					free(rect);
					
				}
				else /*renard 1 est verticale*/
				{
					figurine=IMG_Load("renardverticale.png");
					avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
					SDL_FreeSurface(figurine);
					
					rect = malloc(sizeof(SDL_Rect));
					rect->x= ligne*100;
					rect->y = 100 + colonne*100;
					rect->w=100;
					rect->h=200;
					SDL_RenderCopy(*prenderer, avatar, NULL, rect);
					free(rect);
					
				}
				cmpt1 = 1;
			}
			
			
			
		}
	}
	/* L'image a ete copiee dans le renderer qui sera plus tard affiche a l'ecran */
	
	SDL_RenderPresent(*prenderer);
}

void principal(jeu_t * jeu)
{
	int running, width, height;
	SDL_Event event;
	SDL_Window   * window;
	SDL_Renderer *renderer;
	TTF_Font * font;
	
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
 
	fenetreNiveau(&window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	/*remplirFenetreN(&renderer, font);*/
    plateau(&renderer, jeu);
	if (renderer == 0) {
		 fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
		 SDL_DestroyWindow(window);
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
					break;
				case SDL_QUIT :
					printf("on quitte\n");
					running = 0;
			}
		}
		SDL_Delay(1); /*delai minimal*/
	}
	
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}
