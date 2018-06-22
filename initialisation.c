#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "initialisation.h"

/*permet de faire toutes les allocations necessaires a la structure jeu_t*/
/*Sortie : un pointeur sur jeu_t*/
jeu_t * declarerJeu()
{
    jeu_t * jeu;/*pointeur sur la structure qui detient toutes les structures*/
    int i;/*indice de parcours des tableaux*/
    jeu = malloc(sizeof(jeu_t));
    jeu->lapins = malloc(3*sizeof(lapin_t));
    jeu->renards = malloc(2*sizeof(renard_t));
    jeu->champignons = malloc(3*sizeof(champignon_t));
    for(i = 0; i<3; i++)
    {
       jeu->lapins[i].position = malloc(sizeof(position_t));
       if(i<2)/*il n'y a pas trois renards*/
       {
           jeu->renards[i].tete = malloc(sizeof(position_t));
           jeu->renards[i].queue = malloc(sizeof(position_t));
       }
       jeu->champignons[i].position = malloc(sizeof(position_t));
    }
    jeu->trous = initTrous();
    jeu->plateau = initTrous();
    jeu->nbDeplacements = 0;
    return jeu;
}

/*Creer la matrice des trous afin de savoir directement si telle ou telle case*/
/* est un trou(0) ou pas(1)*/
/*Sortie : un pointeur sur un tableau de pointeurs sur des tableaux de char*/
char *** initTrous()
{
    char *** trous;
    int i, j;
    trous = malloc(5*sizeof(char **));/*5 pointeurs sur des pointeurs*/
    for(i=0; i<5; i++)
    {
        trous[i] = malloc(5*sizeof(char*));/*5 pointeurs sur des char*/
        for(j=0; j<5; j++)
        {
            trous[i][j] = malloc(2*sizeof(char));
            strcpy(trous[i][j], "- ");
        }
    }
    strcpy(trous[0][0], "O ");
    strcpy(trous[0][4], "O ");
    strcpy(trous[2][2], "O ");
    strcpy(trous[4][0], "O ");
    strcpy(trous[4][4], "O ");
    return trous;
}

/*libere toutes les structures de jeu_t*/
void liberer(jeu_t * jeu)
{
    int i;
    libererTrous(jeu->trous);
    libererTrous(jeu->plateau);
    for(i = 0; i<3; i++)
    {
       free(jeu->lapins[i].position);
       if(i<2)/*il n'y a pas trois renards*/
       {
           free(jeu->renards[i].tete);
           free(jeu->renards[i].queue);
       }
       free(jeu->champignons[i].position);
    }
    free(jeu->lapins);
    free(jeu->renards);
    free(jeu->champignons);
    free(jeu);
}

/*libere la matrice des trous et plateau*/
void libererTrous(char *** trous)
{
    int i, j;
    for(i=0; i<5; i++)
    {
        for(j=0; j<5; j++)
        {
            free(trous[i][j]);
        }
        free(trous[i]);
    }
    free(trous);
    trous = NULL;
}

/*initialiser niveau prend un int qui correspond au niveau et initialise le plateau de jeu
attention on commence a 0*/
void initialiserNiveau(jeu_t * jeu, int n)
{
    int i;
    FILE * file = fopen("niveaux.txt", "r");
    if(file)
    {
        
        int v1, v2, v3, v4;
        char c1;
        char num[5];/*le numero en chaine de caractères*/
        fseek(file, 51 * n, SEEK_SET); /*pour aller sur la ligne du niveau choisie*/
        for(i=1 ; i<9 ; i++)
        {
            if(i<4)
            {
                fscanf(file, "%d %d %d\n",&v1, &v2, &v3); /*les coordonées du lapin et si il est sauvé ou non*/
                jeu->lapins[i-1].estSauve = v3; /* la specificite!!! on est des genies*/
            }
            else
            {
                if(i>5)
                {
                    fscanf(file, "%d %d\n", &v1, &v2); /*les coordonées du champignons*/
                
                }
                else
                {
                    fscanf(file, "%d %d %d %d %c\n", &v1, &v2, &v3, &v4, &c1); /*les coordonées des têtes et queun du renard ainsi que le position verticale ou horizontale*/
                }
            }
            if(v1 != 5)
            {
                switch(i)
                {
                    case 1:
                    case 2:
                    case 3:
                        sprintf(num, "%d", i-1);/*transformer le int en char*/
                        /*deplacer(jeu, LAPIN, i-1, v1, v2);*/
                        jeu->lapins[i-1].estSauve = v3;
                        /*scanf("%c", &c1);*/
                        jeu->lapins[i-1].position->ligne = v1;
                        jeu->lapins[i-1].position->colonne = v2;
            
                        strcpy(jeu->plateau[v1][v2], "L");
                        strcat(jeu->plateau[v1][v2], num);
                    break;
                    case 4:
                    case 5:
                        if (c1=='V')
                        {
                            jeu->renards[i-4].orientation = VERTICALE;
                        }
                        else
                        {
                            jeu->renards[i-4].orientation = HORIZONTALE;
                        }
                        jeu->renards[i-4].tete->ligne = v1;
                        jeu->renards[i-4].tete->colonne = v2;
                        jeu->renards[i-4].queue->ligne = v3;
                        jeu->renards[i-4].queue->colonne = v4;
                        strcpy(jeu->plateau[v1][v2], "R");
                        sprintf(num, "%d", i-4);
                        strcat(jeu->plateau[v1][v2], num);
                        strcpy(jeu->plateau[v3][v4], "R");
                        strcat(jeu->plateau[v3][v4], num);
                    break;
                    case 6:
                    case 7:
                    case 8:
                        jeu->champignons[i-6].position->ligne = v1;
                        jeu->champignons[i-6].position->colonne = v2;
                        strcpy(jeu->plateau[v1][v2], "C ");
                    break;
                    default:
                        printf("Choix incorrect\n");
                }
            }
        }
        fclose(file);
    }
}