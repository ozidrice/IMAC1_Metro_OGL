#ifndef _collision_
#define _collision_

#include <stdlib.h>
#include <stdio.h>

#include "props/elementDeclencheur.h"
#include "monde/monde.h"
#include "props/element.h"
#include "props/bonus.h"
#include "props/malus.h"



/*	Renvoie 1 si les elements sont en collision
*	0 sinon
*/
int estEncollision(struct Element *e1, struct Element *e2);

/*	Test collisions entre les listes d'elem
*	Retire les elements mort des listes
*/
void collision(struct Element **liste1, struct Element **liste2);


/*
*	Type: 
*		1 --> Bonus 
*		2 --> Malus
*/
void collisionElementDeclencheur(int type, struct ElementDeclencheur **liste_elemDec, Monde *m);
#endif
