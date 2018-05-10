#include "props/bonus.h"

/*
*	malloc un Bonus 
*	duree_effet : -1 --> inf
*/
Bonus *creerBonus(float x, float y, GLuint *texture, Uint32 duree_effet, int type){
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
	return (Bonus*) creerElementDeclencheur(elem, duree_effet,type);
}


void collisionBonus(Bonus **liste_b, Monde *m){
	collisionElementDeclencheur(1,liste_b,m);
}



/*
*	Active les effet du bonus
*/
void actionBonus(int typeBonus, Monde *monde){
	switch(typeBonus){
		case 1:
			monde->joueur->pv++;
		default :
			break;
	}
}

/*
*	Retire les effets du bonus (si le bonus a une durée)
*/
void undoActionBonus(int typeBonus, Monde *monde){
	switch(typeBonus){
		default :
			break;
	}
}
