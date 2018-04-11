#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>
#include "forme.h"

typedef struct Element {
	int pv; //-1 si inf
	float posx, posy, taille;
<<<<<<< HEAD
	GLuint *texture;
}Element;
=======
	float vit_deplacement_x;
	float vit_deplacement_y;
	GLuint *texture;
}Joueur, Ennemi, Bonus, Obstacle;
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c


/* Malloc un element */
<<<<<<< HEAD
Element* initElement(int pv, float x, float y, float taille, char * path_texture);
=======
struct Element *initElement(int pv, float x, float y, float taille, float vit_deplacement_x, float vit_deplacement_y,char * path_texture);
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c

/*Déplace l'élement passé en paramètre */
void moving(struct Element* e, float x, float y);

/* Affiche un element sur la fenetre*/
void afficheElement(struct Element *e);

/*malloc un joueur*/
Joueur *creerJoueur();

/*malloc un Ennemi*/
Ennemi *creerEnnemi();

/*malloc un Bonus*/
Bonus *creerBonus();

/*malloc un Obstacle*/
Obstacle *creerObstacle();

#endif
