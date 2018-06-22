#ifndef STRUCTURES_H
#define STRUCTURES_H

/*positions de 0 a 4 car plateau de 5x5*/
typedef struct {
    int ligne;
    int colonne;
}position_t;

/*pour le renard*/
typedef enum {
    VERTICALE, HORIZONTALE
}orientation_t;

/*pour le deplacement*/
typedef enum {
    LAPIN, RENARD, CHAMPIGNON
}objet_t;

typedef struct {
    position_t * position;
    int estSauve;/*0 : non, 1 : oui*/ /*Par default c'est mis a 0*/
}lapin_t;

typedef struct {
    position_t * tete;
    position_t * queue;
    orientation_t orientation;
}renard_t;

typedef struct {
    position_t * position;
}champignon_t;

typedef struct {
    lapin_t * lapins;
    renard_t * renards;
    champignon_t * champignons;
    char *** trous;/*tableau de cinq pointeurs sur cinq pointeurs de tableaux de deux char */
    char *** plateau;/*affichage*/
    int nbDeplacements;
}jeu_t;

#endif