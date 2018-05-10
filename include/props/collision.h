#ifndef _collision_
#define _collision_

#include <stdlib.h>
#include <stdio.h>

#include "props/elementDeclencheur.h"
#include "monde/monde.h"
#include "props/element.h"



/*	Renvoie 1 si les elements sont en collision
*	0 sinon
*/
int estEncollision(struct Element *e1, struct Element *e2);

/*	Test collisions entre les listes d'elem
*	Retire les elements mort des listes
*/
void collision(struct Element **liste1, struct Element **liste2);

void collisionBonus(Bonus *liste_b, Monde *m);

void collisionMalus(Malus *liste_m, Monde *m);

int activerMalus(Malus **m, Monde *monde);

void gererMalusActif(Malus **m, Monde *monde);

void desactiverMalus(Malus *m, Monde *monde);
#endif
