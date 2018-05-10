#include "props/elementDeclencheur.h"

/*
*	Malloc un élément déclencheur d'action
*	duree_effet : -1 --> inf
*/
struct ElementDeclencheur *creerElementDeclencheur(struct Element *elem, Uint32 duree_effet, int type){
	struct ElementDeclencheur *e = malloc(sizeof(struct ElementDeclencheur));
	if(e != NULL){
		e->elem = elem;
		e->type = type;
		e->duree_effet = duree_effet;
		e->timer_debut = -1;
		e->next = NULL;
	}
	return e;
}


/*
*	Ajoute un élément à la liste
*/
void addElementDeclencheurToList(struct ElementDeclencheur **list, struct ElementDeclencheur *elemDec){
	if(*list == NULL){
		*list = elemDec;
	}else{
		while((*list)->next != NULL){
			list = &((*list)->next);
		}
		(*list)->next = elemDec;
	}
}

/*
*	Retire et free l'élément de la liste
*/
void removeElementDeclencheurFromList(struct ElementDeclencheur **elemDec){
	if(*elemDec != NULL){
		printf("FREE : %p\n",	*elemDec);
		fflush(stdout);	
		struct ElementDeclencheur *fils = (*elemDec)->next;
		// removeElementFromList(&((*elemDec)->elem));
		free(*elemDec);
		elemDec = &fils;
	}	
}

/*
*	Free la liste d'éléments
*/
void freeElementDeclencheur(struct ElementDeclencheur *elemDec){
	if(elemDec != NULL){
		freeElementDeclencheur(elemDec->next);
		free(elemDec);
	}
}


/* 
*	Affiche la liste d'élément e sur la fenetre
*/
void afficheElementDeclencheur(struct ElementDeclencheur *e){
	while(e != NULL){
		afficheElement(e->elem);
		e = e->next;
	}
}

void movingElementDeclencheur(struct ElementDeclencheur **e, float x, float y, int freeOnTop, int freeOnRight, int freeOnBottom, int freeOnLeft){
	if(e != NULL && *e != NULL){
		struct ElementDeclencheur *fils = (*e)->next;
		if((*e)->timer_debut == -1){
			moving(&((*e)->elem),x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
		}
		//Si l'élément déclencheur n'est pas actif et que son élément a été free
		if((*e)->timer_debut == -1 && (*e)->elem == NULL){
			*e = fils;
			movingElementDeclencheur(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
		}
		else{
			movingElementDeclencheur(&((*e)->next),x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
		}
	}
}


/*___________________BONUS_____________________*/

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



/*___________________MALUS_____________________*/

/*
*	malloc malus
*	duree_effet : -1 --> inf
*/
Malus *creerMalus(float x, float y, GLuint *texture, Uint32 duree_effet, int type){
	int pv = -1;
	int pa = 1; 
	float taille = .05; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = -1/100.;
	vit_deplacement_y = 0; 
	Uint32 intervalle_projectile = 0;
	int nombreProjectileParTir = 0;
	float angleTir = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile = 0;
	struct Element *elem = initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
	return (Malus*) creerElementDeclencheur(elem, duree_effet,type);
}