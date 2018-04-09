#include "element.h"

/* 
*	Malloc un element 
*/
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

/* 
*	Affiche un element sur la fenetre
*/
void afficheElement(Element *e){
	traceRectanglePlein(e->posx, e->posy, e->posx+e->taille, e->posy+e->taille);
}
