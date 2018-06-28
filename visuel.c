#include <stdio.h>
#include <time.h>
#include "visuel.h"
#include "initialisation.h"
#include "moteur.h"

/*permet de savoir sur quelle fenetre nous nous trouvons*/
etat_fenetre_t etatFenetre;
/*identifie un element qu on va peut etre deplacer au prochain clique*/
int sourceExiste;
objet_t objetSource;
int numeroSource;
/*les fenetres*/
SDL_Window   * window;
SDL_Window   * window2;
SDL_Window   * window3;
/*les renderers*/
SDL_Renderer * renderer;
SDL_Renderer * renderer2;
SDL_Renderer * renderer3;

/*
Remplit la premiere fenetre : celle des niveaux
Avec les niveaux de 1 a 60 et des couleurs qui changent en fonction de la difficulté
Entree : font : la police utilisee pour ecrire
*/
void remplirFenetreN(TTF_Font *font)
{
	SDL_Rect *rect;
	int iW, iH, i, j;
	int r, v, b;
	SDL_Color     couleur  = {0, 0, 0, 255}; /*couleur d ecriture*/
	SDL_Surface * surf;
	SDL_Texture * texture;
	char num[5]; /*pour le texte*/
	int numero; /*pour la difficulté*/
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);/*le font blanc*/
	rect = malloc(sizeof(SDL_Rect));
	rect->x = 0;
	rect->y = 0;
	rect->w = 800;
	rect->h = 400;
	SDL_RenderFillRect(renderer, rect );
	free(rect);
	
	surf     = TTF_RenderText_Blended(font, "Selectionnez un niveau : ", couleur);
	texture = SDL_CreateTextureFromSurface(renderer, surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(renderer, rect);
	rect->x = 0;
	rect->y = 0;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(renderer, texture, NULL, rect);
	free(rect);
	
	for(i =0; i<6; i/*6 lignes de dizaines*/
	{
		for(j=1; j<11; j++)/*10 colonnes de unites : de 1 a 10*/
		{
			SDL_DestroyTexture(texture);
			SDL_FreeSurface(surf);
			numero = i*10+j;
			sprintf(num, "%d", numero);
			surf     = TTF_RenderText_Blended(font, num, couleur);
			texture = SDL_CreateTextureFromSurface(renderer, surf);
			SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
			rect = malloc(sizeof(SDL_Rect));
			if(numero<13)
			{	r = 115;
				v = 184;
				b = 46;
			}
			else
			{
				if(numero<25)
				{	r = 255;
					v = 165;
					b = 0;
				}
				else
				{
					if(numero<37)
					{	r = 160;
						v = 24;
						b = 24;
					}
					else
					{
						if(numero<49)
						{	r = 100;
							v = 0;
							b = 132;
						}
						else
						{	r = 12;
							v = 89;
							b = 166;
						}
					}
				}
			}
			SDL_SetRenderDrawColor(renderer, r, v, b, 255);

			rect->x = 30*j+30;/*absisses decalees de 30 + 30 pour faire une marge*/
			rect->y = 30*(i+1)+30;/*ordonnees : pareil mais on evite le 0*/
			rect->w = iW;
			rect->h = iH;
			SDL_RenderFillRect(renderer, rect);
			SDL_RenderCopy(renderer, texture, NULL, rect);
			free(rect);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_FreeSurface(surf);
	SDL_DestroyTexture(texture);
}

/*
Creer une fenetre et essaie de mettre le focus de la souris dessus
Entrees : pwindow : pointeur de pointeur sur une fenetre
	x : largeur
	y : hauteur
*/
void fenetre(SDL_Window ** pwindow, int x, int y)
{
	*pwindow = SDL_CreateWindow("Lièvres et Renards", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, x, y, 0);
	if (*pwindow == 0)
	{
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
	}
	SDL_SetWindowInputFocus(*pwindow);
}

/*
Si on clique dans la zone des niveaux on enleve autant de fois qu on peut la taille d'une zone de clique reservee a un niveau
on ferme la fenetre des niveaux et ouvre la fenetre du jeu avec le bon niveau
Entree : x : absisse du clique en pixel
	y : ordonnee du clique en pixel
	jeu : la structure du jeu deja declaree
Sortie : niveau : le niveau choisi
*/
int cliqueSourisN(int x, int y, jeu_t * jeu)
{
	int niveau = -1, dizaine=0, unite=0;
	if(x>30 && x<360 && y>60 && y<240)
	{
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		x-=30;/*marge*/
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
		fenetre(&window2, 500, 600);
	    	renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED);
		plateau(jeu);/*remplissage*/
	}
	return niveau;
}

/*
Si estGagne a la fin d'un deplacement
Ferme la fenetre du plateau, affiche une nouvelle fenetre avec une image Gagne! 
et le nombre de deplacement par rapport au nombre minimum possible
Entree : font : la meme police d ecriture que la fenetre des niveaux
	jeu : structure du jeu pour les nbDeplacements et nbCoutsMin
*/
void victoire(TTF_Font * font, jeu_t * jeu)
{
	int iW, iH;
	SDL_Rect *rect;
	SDL_Texture  *avatar;
	SDL_Surface *victoire = NULL;
	SDL_Color     couleur  = {0, 0, 0, 255};
	SDL_Surface * surf;
	SDL_Texture * texture;
	char resultat[255];
	char resultat2[255];
	
	victoire=IMG_Load("victoire.png");
		
	SDL_DestroyRenderer(renderer2);
	SDL_DestroyWindow(window2);
	
	etatFenetre = VICTOIRE;
	fenetre(&window3, 400, 500);
	renderer3 = SDL_CreateRenderer(window3, -1, SDL_RENDERER_ACCELERATED);
	
	avatar = SDL_CreateTextureFromSurface(renderer3, victoire);
	SDL_FreeSurface(victoire);
	
	rect = malloc(sizeof(SDL_Rect));
	rect->x= 0;
	rect->y= 0;
	rect->w= 400;
	rect->h= 400;
	SDL_RenderCopy(renderer3, avatar, NULL, rect);
	free(rect);
	
	SDL_SetRenderDrawColor(renderer3, 255, 255, 255, 0);/*Petite zone blanche pour faire jolie*/
	rect = malloc(sizeof(SDL_Rect));
	rect->x = 0;
	rect->y = 400;
	rect->w = 400;
	rect->h = 100;
	SDL_RenderFillRect(renderer3, rect );
	free(rect);
	
	sprintf(resultat, "%d deplacements effectues / ", jeu->nbDeplacements);
	sprintf(resultat2, "%d minimums", jeu->nbCoutsMin);
	strcat(resultat, resultat2);
	surf     = TTF_RenderText_Blended(font, resultat, couleur);
	texture = SDL_CreateTextureFromSurface(renderer3, surf);
	SDL_FreeSurface(surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(renderer3, rect);
	rect->x = 0;
	rect->y = 400;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(renderer3, texture, NULL, rect);
	free(rect);
	
	SDL_RenderPresent(renderer3);
	SDL_DestroyTexture(avatar);
	SDL_DestroyTexture(texture);
}

/*
Affichage du plateau de jeu
d abord le plateau en font puis on parcours jeu->plateua qui est une matrice correspondant a l affichage de la partie
pour chaque case de jeu->plateau si on identifit un element de taille 100*100 alors on l'ajoute sur la fenetre
Entree : 
*/
void plateau(jeu_t * jeu)
{
	int ligne, colonne;
	int cmpt0 = 0;
	int cmpt1= 0;
	 
	SDL_Surface *plateau = NULL;
	SDL_Surface *figurine = NULL;
	SDL_RenderClear(renderer);
		
	plateau=IMG_Load("plateau.png");
	if(!plateau) {
		printf("IMG_Load: %s\n", IMG_GetError());
	}
	affichefig(&plateau, 0, 100, 500, 500);
	
	for(ligne=0;ligne<=4;ligne++)
	{
		for(colonne=0;colonne<=4;colonne++)
		{			
			if( strcmp(jeu->plateau[ligne][colonne], "L0")==0 )
			{
				figurine=IMG_Load("lapin0.png");
				affichefig (&figurine, colonne*100, 100 + ligne*100, 100, 100);
			}
			else if( strcmp(jeu->plateau[ligne][colonne], "L1")==0 )
			{
				figurine=IMG_Load("lapin1.png");
				affichefig (&figurine, colonne*100, 100 + ligne*100, 100, 100);
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "L2")==0 )
			{
				figurine=IMG_Load("lapin2.png");
				affichefig (&figurine, colonne*100, 100 + ligne*100, 100, 100);
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "C ")==0 )
			{
				figurine=IMG_Load("champignon.png");
				affichefig (&figurine, colonne*100, 100 + ligne*100, 100, 100);
			}
			/* les renards*/
			else if (strcmp(jeu->plateau[ligne][colonne], "R0")==0 && cmpt0 == 0)
			{
				if(ligne<4 && strcmp(jeu->plateau[ligne+1][colonne], "R0")==0) 
				{
					figurine=IMG_Load("renardverticale.png");
					affichefig (&figurine, colonne*100, 100 + ligne*100, 100, 200);
					
				}
				else 
				{
					figurine=IMG_Load("renardhorizontale.png");
					affichefig (&figurine, colonne*100, 100 + ligne*100, 200, 100);				
				}
				cmpt0 = 1;
			}
			else if (strcmp(jeu->plateau[ligne][colonne], "R1")==0 && cmpt1 == 0)
			{
				if(ligne<4 && strcmp(jeu->plateau[ligne+1][colonne], "R1")==0) 
				{
					figurine=IMG_Load("renardverticale.png");
					affichefig (&figurine, colonne*100, 100 + ligne*100, 100, 200);
				}
				else 
				{
					figurine=IMG_Load("renardhorizontale.png");
					affichefig (&figurine, colonne*100, 100 + ligne*100, 200, 100);	
				}
				cmpt1 = 1;
			}
		}
	}
	boutons();/*On affiche deux zones de textes en haut du plateau*/
	SDL_RenderPresent(renderer2);
}

/*
Les boutons Quitter et Initialiser sont de simples textes blancs sur font noir pour plus de discretion
*/
void boutons()
{
	SDL_Rect *rect;
	int iW, iH;
	SDL_Color     couleur  = {255, 255, 255, 255};
	SDL_Surface * surf;
	SDL_Texture * texture;
	TTF_Font * font2 = TTF_OpenFont("fake.receipt.ttf", 35);/*une police plus grosse cette fois ci*/
	
	surf     = TTF_RenderText_Blended(font2, "Quitter", couleur);
	texture = SDL_CreateTextureFromSurface(renderer2, surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(renderer2, rect);
	rect->x = 25;
	rect->y = 25;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(renderer2, texture, NULL, rect);
	free(rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	
	surf     = TTF_RenderText_Blended(font2, "Initialiser", couleur);
	texture = SDL_CreateTextureFromSurface(renderer2, surf);
	SDL_QueryTexture(texture, NULL, NULL, &iW, &iH);
	rect = malloc(sizeof(SDL_Rect));
	SDL_RenderFillRect(renderer2, rect);
	rect->x = 225;
	rect->y = 25;
	rect->w = iW;
	rect->h = iH;
	SDL_RenderCopy(renderer2, texture, NULL, rect);
	free(rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
	
	TTF_CloseFont(font2);
}
	    
/*
utilisee dans plateau()
integre une surface a la fenetre du plateau a un certain endroit
Limite la redondance de code
Entree : pfigurine : pointeur de pointeur sur une figure/image dans notre cas
	x, y : absisse et ordonnee du debut de l image
	w : largeur de l image
	h : hauteur de l image
*/
void affichefig (SDL_Surface **pfigurine, int x, int y, int w, int h)
{
	SDL_Rect *rect;
	SDL_Texture  *avatar;
	
	avatar = SDL_CreateTextureFromSurface(renderer2, *pfigurine);
	
	rect = malloc(sizeof(SDL_Rect));
	rect->x= x;
	rect->y= y;
	rect->w= w;
	rect->h= h;
	SDL_RenderCopy(renderer2, avatar, NULL, rect);
	free(rect);
	SDL_DestroyTexture(avatar);
	SDL_FreeSurface(*pfigurine);
}

/*
Lors d'un clique sur la fenetre du jeu on a deux choit : soit on est dans la zone des boutons au dessus soit on est sur le plateau
Si on veut quitter alors on ferme la fenetre et on ouvre la fenetre des niveaux
Si on veut recommencer alors on relance initialiserNiveau() sur le jeu liberer et declarer et on met a jour l affichage
Sinon on identifie sur quelle case on a clique et si on a une source qui existe(precedent clique etait sur un element) on essai de le deplacer sur le nouveau clique
						Sinon on doit identifier la source : objet et numero
	et on regarde si on a gagne
Entree : x, y : absisse et ordonnee du clique
	jeu : le jeu en cours
	font : la police en cas de victoire ou de retour au choix du niveau
*/
void cliquePlateau(int x, int y, jeu_t * jeu, TTF_Font * font, int niveau)
{
	int ligne = 0, colonne = 0;
	char elementPlateau[5];
	if(y<100)
	{
		liberer(jeu);/*va tout changer dans les deux cas*/
		jeu = declarerJeu();
		if(x<225)
		{
			SDL_DestroyRenderer(renderer2);
			SDL_DestroyWindow(window2);
			etatFenetre = NIVEAUX;
			fenetre(&window, 390, 270);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
			remplirFenetreN(font);
		}
		else
		{
			initialiserNiveau(jeu, niveau-1);
			plateau(jeu);
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
			plateau(jeu);
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
		if (estGagne(jeu))
		{
			victoire(font, jeu);
		}
	}
	
}

/*
Initialise les librairies SDL utilisees
Ouvre la fenetre des niveaux
Tant qu'on n'arrete pas on regarde si il y a un evenement toutes les 10ms se qui laisse le temps a l'affichage de se faire correctement
Gere le clique sur la croix, le quitte et surtout le clique. Ici intervient etatFenetre car la fonction appelee differe.
Pour le clque sur la fenetre de victoire on la ferme et on ouvre sur la fenetre des niveaux
A la sorie de la boucle on ferme la fenetre en cours, on ferme les librairies et libere le jeu si necessaire.
Entree : jeu : la structure jeu allouee
*/
void principal(jeu_t * jeu)
{
	int niveau;
	TTF_Font * font;
	int running, width, height;
	SDL_Event event;
	
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
	remplirFenetreN(font);
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
							running = 0;
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
							cliquePlateau(event.button.x, event.button.y, jeu, font, niveau);
							break;
						case NIVEAUX:
							niveau = cliqueSourisN(event.button.x, event.button.y, jeu);
							break;
						case VICTOIRE:
							SDL_DestroyRenderer(renderer3);
							SDL_DestroyWindow(window3);
							liberer(jeu);
							jeu = declarerJeu();
							etatFenetre = NIVEAUX;
							fenetre(&window, 390, 270);
							renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
							remplirFenetreN(font);
							break;
					}
					break;
				case SDL_QUIT :
					printf("on quitte\n");
					running = 0;
			}
		}
		SDL_Delay(10); /*delai minimal*/
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
		case VICTOIRE:
			SDL_DestroyRenderer(renderer3);
			SDL_DestroyWindow(window3);
			break;
	}
	TTF_Quit();
	SDL_Quit();
	if(jeu != NULL)/*depend de si on a deja joue ou non*/
	{
		liberer(jeu);
	}
}
