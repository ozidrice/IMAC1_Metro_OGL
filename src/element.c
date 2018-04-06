#include "element.h"

Element* initElement(int pv, float x, float y, float taille, char * texture){
	Element* element = malloc(sizeof(Element));
	if (!element)
		return NULL;
	element->pv= pv;
	element->posx=x;
	element->posy=y;
	element->taille=taille;
	return element;
	
}

void moving(Element* e, float x, float y){
	e->posx += x;
	e->posy += y;
}


