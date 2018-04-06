#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>

typedef struct Element {
	int pv;
	float posx, posy, taille;
	char* texture;
}Element;

typedef struct ennemi {
	Element e;
	/* ... */
}Ennemi;

/* Initialise joueur/ennemis/obstacle */
Element* initElement(int pv, float x, float y, float taille, char * texture);

/*Déplace l'élement passé en paramètre */
void moving(Element* e, float x, float y);

#endif
