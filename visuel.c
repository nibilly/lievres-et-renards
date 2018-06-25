#include <stdio.h>
#include "visuel.h"

void remplirFenetreN(SDL_Renderer **prenderer, TTF_Font *font)
{
	SDL_Rect rect;
	SDL_Texture  *avatar;
	SDL_Surface *image = NULL;
	int iW, iH;
	SDL_Color     couleur  = {255, 255, 255, 255};
	SDL_Surface * surf     = TTF_RenderText_Blended(font, "niveau de 0 à 2 : ", couleur);
	SDL_Texture * texttext = SDL_CreateTextureFromSurface(*prenderer, surf);
	SDL_QueryTexture(texttext, NULL, NULL, &iW, &iH);
	SDL_RenderFillRect(*prenderer, &rect);
	rect.x = 0;
	rect.y = 0;
	rect.w = 200;
	rect.h = 30;
	SDL_RenderCopy(*prenderer, texttext, NULL, &rect);
	
	SDL_SetRenderDrawColor(*prenderer, 255, 255, 0, 0);
	rect.x = 100;
	rect.y = 100;
	rect.w = rect.h = 250;
	SDL_RenderFillRect(*prenderer, &rect );
	
	image=IMG_Load("fd.jpg");
	/* image=SDL_LoadBMP("loic.bmp"); fonction standard de la SDL2 */
	if(!image) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}

	avatar = SDL_CreateTextureFromSurface(*prenderer, image);
	SDL_FreeSurface(image);

	rect.x = 150;
	rect.y = 150;
	rect.w = rect.h = 200;
	SDL_RenderCopy(*prenderer, avatar, NULL, &rect);
	/* L'image a ete copiee dans le renderer qui sera plus tard affiche a l'ecran */
	
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


void plateau(SDL_Renderer ** prenderer)
{
/*initialisation*/
	
	SDL_Rect *rect;

	
	SDL_Texture  *avatar;

	
	SDL_Surface *plateau = NULL;
	SDL_Surface *lapin0 = NULL;
	
	
/*chargement des images avec vérifications*/	
	plateau=IMG_Load("plateau.png");
	/* image=SDL_LoadBMP("loic.bmp"); fonction standard de la SDL2 */
	lapin0=IMG_Load("lapin0.png");
	if(!plateau||!lapin0) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	

	avatar = SDL_CreateTextureFromSurface(*prenderer, plateau);
	SDL_FreeSurface(plateau);
	/*avatarPlateau = SDL_CreateTextureFromSurface(*prenderer, lapin0);
	SDL_FreeSurface(lapin0);*/
	
	rectPlateau.x = 0;
	rectPlateau.y = 100;
	rectPlateau.w = 500;
	rectPlateau.h = 500;
	SDL_RenderCopy(*prenderer, avatar, NULL, &rectPlateau);
	
	
	
	
	
	
	
	avatar = SDL_CreateTextureFromSurface(*prenderer, lapin0);
	SDL_FreeSurface(lapin0);
	rectLapin0.x= 0;
	rectLapin0.y = 100;
	rectLapin0.w=100;
	rectLapin0.h=100;
	SDL_RenderCopy(*prenderer, avatar, NULL, &rectLapin0);
	/* L'image a ete copiee dans le renderer qui sera plus tard affiche a l'ecran */
	
	SDL_RenderPresent(*prenderer);
}






void principal()
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
	font = TTF_OpenFont("fake.receipt.ttf", 30);
 
	fenetreNiveau(&window);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
	/*remplirFenetreN(&renderer, font);*/
    plateau(&renderer);
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
