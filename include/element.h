#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>
#include "forme.h"
#include <png.h>

typedef struct Element {
	int pv; //-1 si inf
	float posx, posy, taille;
	float vit_deplacement_x;
	float vit_deplacement_y;
	GLuint *texture;
}Joueur, Ennemi, Bonus, Obstacle;


/* Malloc un element */
struct Element *initElement(int pv, float x, float y, float taille, float vit_deplacement_x, float vit_deplacement_y,char * path_texture);

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
