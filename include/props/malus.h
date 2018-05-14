#ifndef _MALUS_
#define _MALUS_

#include "monde/monde.h"
#include "props/elementDeclencheur.h"

void collisionMalus(Malus **liste_m, Monde *m);

/*	Active les effet du malus*/
void actionMalus(int typeMalus, Monde *monde);
/*Retire les effets du malus (si le malus a une durée)*/
void undoActionMalus(int typeMalus, Monde *monde);

/* Malloc un Malus */
Malus *creerMalus(float x, float y, GLuint *texture, Uint32 duree_effet, int type);
#endif