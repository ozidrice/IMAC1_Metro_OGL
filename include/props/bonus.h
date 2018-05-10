#ifndef _BONUS_
#define _BONUS_

#include "monde/monde.h"
#include "props/elementDeclencheur.h"

void collisionBonus(Bonus **liste_b, Monde *m);

/*	Active les effet du bonus*/
void actionBonus(int typeBonus, Monde *monde);
/*Retire les effets du bonus (si le bonus a une durée)*/
void undoActionBonus(int typeBonus, Monde *monde);

/* Malloc un Bonus */
Bonus *creerBonus(float x, float y, GLuint *texture, Uint32 duree_effet, int type);

#endif
