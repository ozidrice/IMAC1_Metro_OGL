#include "props/malus.h"


/*
*	malloc malus
*	duree_effet : -1 --> inf
*/
Malus *creerMalus(float x, float y, GLuint *texture, Uint32 duree_effet, int type){
	int pv = -1;
	int pa = 1; 
	float taille = .05; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = -1/1000.;
	vit_deplacement_y = 0; 
	Uint32 intervalle_projectile = 0;
	int nombreProjectileParTir = 0;
	float angleTir = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile = 0;
	struct Element *elem = initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
	return (Malus*) creerElementDeclencheur(elem, duree_effet,type);
}


void collisionMalus(Malus **liste_m, Monde *m){
	collisionElementDeclencheur(2,liste_m,m);
}


/*
*	Active les effet du malus
*/
void actionMalus(int typeMalus, Monde *monde){
	switch(typeMalus){
		case 1:
			monde->joueur->pv--;
			break;
		case 2:
			monde->joueur->taille = 0.3;
			break;
		default :
			break;
	}
}

/*
*	Retire les effets du malus (si le malus a une durée)
*/
void undoActionMalus(int typeMalus, Monde *monde){
	switch(typeMalus){
		case 2:
			monde->joueur->taille = 0.17;
			break;
		default :
			break;
	}
}
