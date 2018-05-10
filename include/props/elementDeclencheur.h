#ifndef _ELEMENT_DECLENCHEUR_
#define _ELEMENT_DECLENCHEUR_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <GL/glu.h>


#include "element.h"
typedef struct ElementDeclencheur{
	struct Element *elem;
	int type;
	Uint32 duree_effet; //0 = inf (en ms)
	Uint32 timer_debut; //-1 = pas encore démaré 
	struct ElementDeclencheur *next;
}Bonus, Malus;
#include "monde/monde.h"


/*	Malloc un élément déclencheur d'action*/
struct ElementDeclencheur *creerElementDeclencheur(struct Element *elem, Uint32 duree_effet, int type);


/*	Ajoute un élément à la liste*/
void addElementDeclencheurToList(struct ElementDeclencheur **list, struct ElementDeclencheur *elem);

void removeElementDeclencheurFromList(struct ElementDeclencheur **elemDec);

/*	Affiche la liste d'élément e sur la fenetre*/
void afficheElementDeclencheur(struct ElementDeclencheur *e);

void movingElementDeclencheur(struct ElementDeclencheur **e, float x, float y, int freeOnTop, int freeOnRight, int freeOnBottom, int freeOnLeft);

/* Malloc un Bonus */
Bonus *creerBonus(float x, float y, GLuint *texture, Uint32 duree_effet, int type);

/* Malloc un Malus */
Malus *creerMalus(float x, float y, GLuint *texture, Uint32 duree_effet, int type);

/*	Free la liste d'éléments*/
void freeElementDeclencheur(struct ElementDeclencheur *e);

#endif