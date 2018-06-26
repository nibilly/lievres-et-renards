#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "moteur.h"
#include "initialisation.h"


/*Change les positions et actualise le plateau*/
/*si renards : orientation necessaire et le premier appel pour positionner la premiere fois on met la tete avant la queue*/
/*                decaler sur la case où l'on veut que le corps du renard soit. Tete ou queue peu importe*/
/*Entrees : jeu : structure des structures*/
/*          objet : type element deplace*/
/*          numero : indice de l'objet a deplace dans le tableau correspondant*/
/*          ligne et colonne : positions*/
void deplacer(jeu_t * jeu, objet_t objet, int numero, int ligne, int colonne)
{
    int ancienneLigne, ancienneColonne;
    int ancienneLigne2, ancienneColonne2; /*seulement pour les renards et sa concerne leur queue*/
    int diffTete, diffQueue, diff;
    char num[5];/*le numero en chaine de caractères*/
    sprintf(num, "%d", numero);/*transformer le int en char*/
    if (verifplateau(ligne, colonne) && verifPasObstacle(jeu, ligne, colonne)) 
    {
        switch(objet)
        {
            case LAPIN :
                if(verifLapin(jeu, numero, ligne, colonne))
                {
                    ancienneLigne = jeu->lapins[numero].position->ligne;
                    ancienneColonne = jeu->lapins[numero].position->colonne;
                    
                    jeu->lapins[numero].position->ligne = ligne;
                    jeu->lapins[numero].position->colonne = colonne;
                    
                    strcpy(jeu->plateau[ancienneLigne][ancienneColonne], jeu->trous[ancienneLigne][ancienneColonne]);
                    strcpy(jeu->plateau[ligne][colonne], "L");
                    strcat(jeu->plateau[ligne][colonne], num);
                    if(strcmp(jeu->trous[ligne][colonne], "O ") == 0)
                    {
                        jeu->lapins[numero].estSauve = 1;
                    }
                    else
                    {
                        jeu->lapins[numero].estSauve = 0;
                    }
                }
                break;
                
            case RENARD :
                ancienneLigne = jeu->renards[numero].tete->ligne;
                ancienneColonne = jeu->renards[numero].tete->colonne;
                ancienneLigne2 = jeu->renards[numero].queue->ligne;
                ancienneColonne2 = jeu->renards[numero].queue->colonne;
                /*Toujours la tete en haut ou a droite*/
                if(jeu->renards[numero].orientation == VERTICALE)
                {
                    diffTete = ancienneLigne - ligne;
                    diffQueue = ancienneLigne2 - ligne;
                    if(diffQueue <= 0)
                    {
                        diff = diffQueue;
                    }
                    else
                    {
                        diff = diffTete;
                    }
                    jeu->renards[numero].tete->ligne -= diff;
                    jeu->renards[numero].queue->ligne -= diff;
                }
                else
                {
                    diffTete = ancienneColonne - colonne;
                    diffQueue = ancienneColonne2 - colonne;
                    if(diffQueue <= 0)
                    {
                        diff = diffQueue;
                    }
                    else
                    {
                        diff = diffTete;
                    }
                    jeu->renards[numero].tete->colonne -= diff;
                    jeu->renards[numero].queue->colonne -= diff;
                }
                strcpy(jeu->plateau[ancienneLigne][ancienneColonne], jeu->trous[ancienneLigne][ancienneColonne]);
                strcpy(jeu->plateau[ancienneLigne2][ancienneColonne2], jeu->trous[ancienneLigne2][ancienneColonne2]);
                
                strcpy(jeu->plateau[jeu->renards[numero].tete->ligne][jeu->renards[numero].tete->colonne], "R");
                strcat(jeu->plateau[jeu->renards[numero].tete->ligne][jeu->renards[numero].tete->colonne], num);
                
                strcpy(jeu->plateau[jeu->renards[numero].queue->ligne][jeu->renards[numero].queue->colonne], "R");
                strcat(jeu->plateau[jeu->renards[numero].queue->ligne][jeu->renards[numero].queue->colonne], num);
                break;
            default :
                printf("Objet non deplaçable ici\n");
        }
    }
}

/*Affiche le plateau de jeu*/
/*Entree : jeu : pointeur sur la structure des structures*/
void afficher(jeu_t * jeu)
{
    int i, j;
    printf("  0 1 2 3 4\n");
    for(i=0; i<5; i++)
    {
        printf("%d ", i);
        for(j=0; j<5; j++)
        {
            printf("%s", jeu->plateau[i][j]);
        }
        printf("\n");
    }
}

/*Verifie que les coordonnées sont dans le plateau
Sortie : 0 si on sort du plateau, 1 sinon*/
int verifplateau (int ligne, int colonne) {
    int i = 0;
    if(0<=ligne) 
    {
        if (ligne<=4)
        {
            if (0<=colonne)
            {
                if (colonne<=4) 
                {
                    i=1;
                }
            }
        }
    }
    return i;
}

/*Verfie qu'il n'y a pas d'objet sur les coordonnées données
Sortie : 0 si il y a un obstacle sur la case du plateau, 1 sinon.
Est considéres comme obstacle tous ce qui est ni une case vide ni un trou*/
int verifPasObstacle(jeu_t * jeu, int ligne, int colonne) {
    int i = 0;
    if (strcmp(jeu->plateau[ligne][colonne], "O ") == 0 || strcmp(jeu->plateau[ligne][colonne], "- ") == 0) 
    {
        i=1;
    }
    
    return i;
}



/*Verifie que le déplacement du lapin n'est pas en diagonale, qu'il y a bien que des obstacles sur son saut
Sortie : 0 si le mouvement est impossible, 1 sinon */
int verifLapin(jeu_t * jeu, int numero, int ligne, int colonne)
{
    int code = 1;
    int cptObstacles = 0;
    int parcours;/*indice de chaque element entre le lapin et les coordonnées*/
    int incrementeur;
    int ancienneLigne, ancienneColonne;
    ancienneLigne = jeu->lapins[numero].position->ligne;
    ancienneColonne = jeu->lapins[numero].position->colonne;
    if (ancienneLigne == ligne)
    {
        if (ancienneColonne == colonne)
        {
            code = 0;
            printf("mouvement impossible : les diagonales ne sont pas autorisé\n");/*il ne va plus soit en verticale soit en horizontale*/
        }
        else
        /*le lapin va se deplacer a l horizontale*/
        {
            if(ancienneColonne < colonne)
            {
                incrementeur = 1;
            }
            else
            {
                incrementeur = -1;
            }
            
            parcours = ancienneColonne + incrementeur;
            
            while(parcours != colonne && code)
            {
                if(verifPasObstacle(jeu, ligne, parcours))
                {
                    code = 0;
                }
                parcours += incrementeur;
                cptObstacles++;
            }
        }
    }
    else
    
    {
        if (ancienneColonne != colonne)
        {
            code = 0;
            printf("mouvement impossible : les diagonales ne sont pas autorisé\n"); /*il ne va plus soit en verticale soit en horizontale*/
        }
        else
        /*le lapin va se depalcer a la verticale*/
        {
            if(ancienneLigne < ligne)
            {
                incrementeur = 1;
            }
            else
            {
                incrementeur = -1;
            }
            
            parcours = ancienneLigne + incrementeur;
            
            while(parcours != ligne && code)
            {
                if(verifPasObstacle(jeu, parcours, colonne))
                {
                    code = 0;
                }
                parcours += incrementeur;
                cptObstacles++;
            }
        }
    }
    if(cptObstacles == 0)
    {
        code = 0;
        printf("mouvement impossible : il faut sauter par dessus un obstacle.\n");
    }
    return code;   
}

/*on vérifie que tous les lapins sont sauvés
Sortie : 1 si la partie est gagnée et 0 si on a perdue*/
int estGagne(jeu_t * jeu)
{
    int i, gagne = 1;
    for(i = 0 ; i<3 ; i++)
    {
        if(!jeu->lapins[i].estSauve) /*on parcour les 3 lapins, a savoir qu'un lapin qui n'est pas utilisé dans le niveau est considérés comme sauvés dés l'initialisation*/
        {
            gagne = 0;
        }
    }
    return gagne;
}


/*Permet de jouer au jeu textuellement
Affiche en boucle le plateau et un menu de choix
Le joueur saisi au clavier ce quiest demandé*/
void moteurJeu(jeu_t * jeu, int niveau)
{
    int choix;
    int ligne;
    int colonne;
    int quitter = 0;
    while(0==estGagne(jeu)&&0==quitter) /*tant que tout les lapins ne sont pas sauvés ou que le joueur na pas souhaité quitte le jeu*/
    {
        afficher(jeu);
        printf("------Menu------\n");
        
        printf("1)Deplacer Lapin 0\n");
        printf("2)Deplacer Lapin 1\n");
        printf("3)Deplacer Lapin 2\n");
        printf("4)Deplacer Renard 0\n");
        printf("5)Deplacer Renard 1\n");
        printf("6)Reinitialiser niveau\n");
        printf("0)Quitter\n");
        
        printf("=> Choix :");
        scanf("%d%*c",&choix);
        
        
        if (0!=choix && 6 != choix && 7!= choix )
        {
            printf("Choisisez les coordonees:\n");
            printf("ligne :");
            scanf("%d%*c",&ligne);
            printf("colonne :");
            scanf("%d%*c",&colonne);
        }
        
        switch(choix)
        {
            case 0:
                quitter = 1;
                break;
            case 1:
                deplacer(jeu, LAPIN, 0, ligne, colonne);
                break;
            case 2:
                deplacer(jeu, LAPIN, 1, ligne, colonne);
                break;
            case 3:
                deplacer(jeu, LAPIN, 2, ligne, colonne);
                break;
            case 4:
                deplacer(jeu, RENARD, 0, ligne, colonne);
                break;
            case 5:
                deplacer(jeu, RENARD, 1, ligne, colonne);
                break;
            case 6:
                libererTrous(jeu->plateau);
                jeu->plateau = initTrous();
                initialiserNiveau(jeu, niveau);
                break;
            default:
                printf("Choix incorrect\n");
        }
        printf("\n");
        
    }
    if(!quitter)
    {
        afficher(jeu);
        printf("la partie est gagnée !!!!!!\n");
    }
} 
