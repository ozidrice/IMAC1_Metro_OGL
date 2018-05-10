// #include "monde.h"
#include "props/collision.h"


/*
*	Renvoie 1 si les elements sont en collision
*	0 sinon
*/
int estEncollision(struct Element *e1, struct Element *e2){
	if(e1 == NULL || e2 == NULL)
		return 0;
	float ratio = windowRatio();
	if(e1->posx+(e1->taille/ratio) > e2->posx-(e2->taille/ratio) && e1->posx-(e1->taille/ratio) < e2->posx+(e2->taille/ratio) &&
		e1->posy-e1->taille < e2->posy+e2->taille && e1->posy+e1->taille > e2->posy-e2->taille
		){
		return 1;
	}
	return 0;
}

/*
*	Test collisions entre les listes d'elem
*	Retire les elements mort des listes
*/
void collision(struct Element **liste1, struct Element **liste2){
	if(*liste1 != NULL && *liste2 != NULL){
		//Foreach liste1
		do{
			int meurt_1 = 0, meurt_2 = 0;
			if(*liste2 != NULL){
				//Foreach liste2
				struct Element **liste2_tmp = liste2;
				do{
					meurt_2 = 0; 
					if(estEncollision(*liste1,*liste2_tmp)){
						meurt_1 = attaque(*liste2_tmp,*liste1);
						meurt_2 = attaque(*liste1,*liste2_tmp);
						if(meurt_1 == 1)
							removeElementFromList(liste1);
						if(meurt_2 == 1)
							removeElementFromList(liste2_tmp);
						else
							liste2_tmp = &((*liste2_tmp)->next);
					}else
						liste2_tmp = &((*liste2_tmp)->next);
				}while(*liste2_tmp != NULL);
			}
			if(meurt_1 == 0)
				liste1 = &((*liste1)->next);
		}while(*liste1 != NULL);
	}
}


void collisionBonus(Bonus *liste_b, Monde *m){
	// Joueur *j = m->joueur;
	// while(liste_b != NULL){
	// 	int asBeenDeleted = 0;
	// 	if(1 == estEncollision(liste_b->elem,j)){
	// 		if(1 == activerBonus(&liste_b,m))
	// 			asBeenDeleted = 1;
	// 	}
	// 	if(asBeenDeleted == 0)
	// 		liste_b = liste_b->next;
	// }
}


void collisionMalus(Malus *liste_m, Monde *m){
	Joueur *j = m->joueur;
	while(liste_m != NULL){
		int asBeenDeleted = 0;
		if(1 == estEncollision(liste_m->elem,j)){
			if(1 == activerMalus(&liste_m,m))
				asBeenDeleted = 1;
		}
		if(asBeenDeleted == 0)
			liste_m = liste_m->next;
	}
}

void gererMalusActif(Malus **m, Monde *monde){
	if(m != NULL && *m != NULL){
		int asBeenDeleted = 0;
		if((*m)->timer_debut != -1){
			Uint32 current = SDL_GetTicks();
			if((*m)->timer_debut+(*m)->duree_effet < current){
				desactiverMalus((*m),monde);
				Malus *fils = (*m)->next; 
				free(*m);
				*m = fils;
				asBeenDeleted = 1;
			}
		}
		if(asBeenDeleted == 1){
			gererMalusActif(m,monde);
		}else{
			gererMalusActif(&((*m)->next),monde);
		}
	}
}


/*
*	Retorune 1 si m supprimé
*/
int activerMalus(Malus **m, Monde *monde){
	if(m != NULL && *m != NULL){
		if((*m)->timer_debut != -1)
			fprintf(stderr, "Malus already running\n");
		else{
			//Action
			switch((*m)->type){
				case 1:
					monde->joueur->pv++;
				default :
					break;
			}
			if((*m)->duree_effet == 0){
				removeElementDeclencheurFromList(m);
				return 1;
			}else{
				removeElementFromList(&((*m)->elem));
				(*m)->timer_debut = SDL_GetTicks();
			}
		}
	}
	return 0;
}


void desactiverMalus(Malus *m, Monde *monde){
	if(m != NULL){
		//Action inverse (rétablissement du monde)
		switch(m->type){
			case 1: 
				monde->joueur->pv--;
			default :
				break;
		}
	}
}