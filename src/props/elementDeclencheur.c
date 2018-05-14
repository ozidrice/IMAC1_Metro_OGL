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
		struct ElementDeclencheur *fils = (*elemDec)->next;
		free(*elemDec);
		*elemDec = fils;
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


/*
*	Type: 
*		1 --> Bonus 
*		2 --> Malus
*/
int activerElementDeclencheur(int type, struct ElementDeclencheur **liste_elemDec, Monde *monde){
	if(liste_elemDec != NULL && *liste_elemDec != NULL){
		if((*liste_elemDec)->timer_debut != -1)
			fprintf(stderr, "Malus already running\n");
		else{
			switch(type){
				case 1:
					actionBonus((*liste_elemDec)->type,monde);
					break;
				case 2: 
					actionMalus((*liste_elemDec)->type,monde);
					break;
				default:
					break;
			}
			if((*liste_elemDec)->duree_effet == 0){
				removeElementDeclencheurFromList(liste_elemDec);
				return 1;
			}else{
				removeElementFromList(&((*liste_elemDec)->elem));
				(*liste_elemDec)->timer_debut = SDL_GetTicks();
			}
		}
	}
	return 0;
}



/*
*	Type: 
*		1 --> Bonus 
*		2 --> Malus
*/
void gererElementDeclencheurActif(int type, struct ElementDeclencheur **liste_elemDec, Monde *monde){
	if(liste_elemDec != NULL && *liste_elemDec != NULL){
		int asBeenDeleted = 0;
		if((*liste_elemDec)->timer_debut != -1){
			Uint32 current = SDL_GetTicks();
			if((*liste_elemDec)->timer_debut+(*liste_elemDec)->duree_effet < current){
				switch(type){
					case 1:
						undoActionBonus((*liste_elemDec)->type,monde);
						break;
					case 2: 
						undoActionMalus((*liste_elemDec)->type,monde);
						break;
					default:
						break;
				}
				removeElementDeclencheurFromList(liste_elemDec);
				asBeenDeleted = 1;
			}
		}
		if(asBeenDeleted == 1){
			gererElementDeclencheurActif(type,liste_elemDec,monde);
		}else{
			gererElementDeclencheurActif(type,&((*liste_elemDec)->next),monde);
		}
	}
}



