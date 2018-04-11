#include "element.h"
#include "monde.h"

/* 
*	Malloc un element 
*/
Element* initElement(int pv, float x, float y, float taille, char * path_texture){
	Element* element = malloc(sizeof(Element));
	if (!element)
		return NULL;
	element->pv= pv;
	element->posx=x;
	element->posy=y;
	element->taille=taille;
	element->texture = (path_texture == NULL) ? NULL : generateID(path_texture);
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
	glBindTexture(GL_TEXTURE_2D, *(e->texture));
	traceRectanglePlein(e->posx, e->posy, e->posx+e->taille, e->posy+e->taille);
	glBindTexture(GL_TEXTURE_2D,0);
}
