#ifndef _ELEMENT_
#define _ELEMENT_

#include <stdlib.h>
#include <stdio.h>
#include "forme.h"

typedef struct Element {
	int pv;
	float posx, posy, taille;
	char* texture;
}Element;

typedef struct ennemi {
	Element e;
	/* ... */
}Ennemi;

/* Malloc un element */
Element* initElement(int pv, float x, float y, float taille, char * texture);

/* Affiche un element sur la fenetre*/
void afficheElement(Element *e);

#endif
