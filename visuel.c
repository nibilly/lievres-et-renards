#include <stdio.h>
#include <time.h>
#include "visuel.h"
#include "initialisation.h"
#include "moteur.h"


etat_fenetre_t etatFenetre;
int sourceExiste;
objet_t objetSource;
int numeroSource;

void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font)
{
	SDL_Rect *rect;
	int iW, iH, i, j;
	int r, v, b;
	SDL_Color     couleur  = {0, 0, 0, 255};
	SDL_Surface * surf;
	SDL_Texture * texture;
	char num[5];
	int numero;
	
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
			numero = i*10+j;
			sprintf(num, "%d", numero);
			surf     = TTF_RenderText_Blended(font, num, couleur);
			texture = SDL_CreateTextureFromSurface(*prenderer, surf);
			SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
			rect = malloc(sizeof(SDL_Rect));
			if(numero<13)
			{
				r = 115;
				v = 184;
				b = 46;
			}
			else
			{
				if(numero<25)
				{
					r = 255;
					v = 165;
					b = 0;
				}
				else
				{
					if(numero<37)
					{
						r = 160;
						v = 24;
						b = 24;
					}
					else
					{
						if(numero<49)
						{
							r = 100;
							v = 0;
							b = 132;
						}
						else
						{
							r = 12;
							v = 89;
							b = 166;
						}
					}
				}
			}
			SDL_SetRenderDrawColor(*prenderer, r, v, b, 255);
			rect->x = 30*j+30;
			rect->y = 30*(i+1)+30;
			rect->w = iW;
			rect->h = iH;
			SDL_RenderFillRect(*prenderer, rect);
			SDL_RenderCopy(*prenderer, texture, NULL, rect);
			free(rect);
		}
	}	
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
	SDL_SetWindowInputFocus(*pwindow);
}

/*retourne le niveau*/
int cliqueSourisN(int x, int y, jeu_t * jeu, SDL_Window ** pwindow, SDL_Renderer ** prenderer, SDL_Window ** pwindow2, SDL_Renderer ** prenderer2)
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
		
		etatFenetre = JEU;
		fenetre(pwindow2, 500, 600);
	    *prenderer2 = SDL_CreateRenderer(*pwindow2, -1, SDL_RENDERER_ACCELERATED);
		plateau(prenderer2, jeu);
	}
	return niveau;
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
	boutons(prenderer);
	
	SDL_RenderPresent(*prenderer);
}

void boutons(SDL_Renderer ** prenderer)
{
	SDL_Rect *rect;
	int iW, iH;
	SDL_Color     couleur  = {255, 255, 255, 255};
	SDL_Surface * surf;
	SDL_Texture * texture;
	TTF_Font * font2 = TTF_OpenFont("fake.receipt.ttf", 35);
	
	
	surf     = TTF_RenderText_Blended(font2, "Quitter", couleur);
	texture = SDL_CreateTextureFromSurface(*prenderer, surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(*prenderer, rect);
	rect->x = 25;
	rect->y = 25;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(*prenderer, texture, NULL, rect);
	free(rect);	
	
	surf     = TTF_RenderText_Blended(font2, "Initialiser", couleur);
	texture = SDL_CreateTextureFromSurface(*prenderer, surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(*prenderer, rect);
	rect->x = 225;
	rect->y = 25;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(*prenderer, texture, NULL, rect);
	free(rect);	
	
	TTF_CloseFont(font2);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

void affichefig (SDL_Renderer ** prenderer, SDL_Surface *figurine, int x, int y, int w, int h)
{
	SDL_Rect *rect;
	SDL_Texture  *avatar;
	
	avatar = SDL_CreateTextureFromSurface(*prenderer, figurine);
	SDL_FreeSurface(figurine);
	
	rect = malloc(sizeof(SDL_Rect));
	rect->x= x;
	rect->y= y;
	rect->w= w;
	rect->h= h;
	SDL_RenderCopy(*prenderer, avatar, NULL, rect);
	free(rect);
}

void cliquePlateau(int x, int y, jeu_t * jeu, SDL_Window ** pwindow, SDL_Renderer ** prenderer, SDL_Window ** pwindow2, SDL_Renderer ** prenderer2, TTF_Font * font, int niveau)
{
	int ligne = 0, colonne = 0;
	char elementPlateau[5];
	if(y<100)
	{
		liberer(jeu);
		jeu = declarerJeu();
		if(x<225)
		{
			SDL_DestroyRenderer(*prenderer2);
			SDL_DestroyWindow(*pwindow2);
			etatFenetre = NIVEAUX;
			fenetre(pwindow, 390, 270);
			*prenderer = SDL_CreateRenderer(*pwindow, -1, SDL_RENDERER_ACCELERATED );
			remplirFenetreN(prenderer, font);
		}
		else
		{
			initialiserNiveau(jeu, niveau-1);
			plateau(prenderer2, jeu);
		}
	}
	else
	{
		y-=100;
		while(y>100)
		{
			ligne++;
			y-=100;
		}
		while(x>100)
		{
			colonne++;
			x-=100;
		}
		
		if(sourceExiste)
		{
			
			deplacer(jeu, objetSource, numeroSource, ligne, colonne);
			plateau(prenderer2, jeu);
			sourceExiste = 0;
		}
		else
		{
			strcpy(elementPlateau, jeu->plateau[ligne][colonne]);
			if(elementPlateau[0] == 'L')
			{
				objetSource = LAPIN;
			}
			else
			{ 
				if(elementPlateau[0] == 'R')
				{
					objetSource = RENARD;
				}
				else
				{
					objetSource = CHAMPIGNON;
				}
			}
			if(objetSource != CHAMPIGNON)
			{
				sourceExiste = 1;
				if(elementPlateau[1] == '0')
				{
					numeroSource = 0;
				}
				else
				{
					if(elementPlateau[1] == '1')
					{
						numeroSource = 1;
					}
					else
					{
						numeroSource = 2;
					}
				}
			}
		}
	}
	printf("%d\n", estGagne(jeu));/**/
}

void principal(jeu_t * jeu)
{
	int niveau;
	TTF_Font * font;
	int running, width, height;
	SDL_Event event;
	SDL_Window   * window;
	SDL_Window   * window2;
	SDL_Renderer * renderer;
	SDL_Renderer * renderer2;
	sourceExiste = 0;
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
							cliquePlateau(event.button.x, event.button.y, jeu, &window, &renderer, &window2, &renderer2, font, niveau);
							break;
						case NIVEAUX:
							niveau = cliqueSourisN(event.button.x, event.button.y, jeu, &window, &renderer, &window2, &renderer2);
							break;
					}
					break;
				case SDL_QUIT :
					printf("on quitte\n");
					running = 0;
			}
		}
		SDL_Delay(100); /*delai minimal*/
	}
	TTF_CloseFont(font);
	switch(etatFenetre)
	{
		case JEU:
			SDL_DestroyRenderer(renderer2);
			SDL_DestroyWindow(window2);
			break;
		case NIVEAUX:
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			break;
	}
	TTF_Quit();
	SDL_Quit();
	if(jeu != NULL)/*depend de si on a déjà joué ou non*/
	{
		liberer(jeu);
	}
}
