#include "element.h"
#include "monde.h"

/* 
*	Malloc un element 
*/
struct Element *initElement(int pv, float x, float y, float taille, float vit_deplacement_x, float vit_deplacement_y, char * path_texture){
	struct Element* element = malloc(sizeof(struct Element));
	if (!element)
		return NULL;
	element->pv= pv;
	element->posx=x;
	element->posy=y;
	element->taille=taille;
	element->vit_deplacement_x = vit_deplacement_x;
	element->vit_deplacement_y = vit_deplacement_y;
	element->texture = (path_texture == NULL) ? NULL : generateID(path_texture);
	return element;
}

/*
*	Ajoute un élément à la liste
*/
void addElementToList(struct Element *list, struct Element *elem){
	if(list == NULL)
		list = elem;
	else{
		struct Element *tmp = list;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = elem;		
	}
}

/*
*	Déplace un élement
*/
void moving(struct Element *e, float x, float y){
	e->posx += x*e->vit_deplacement_x;
	e->posy += y*e->vit_deplacement_y;
}

/* 
*	Affiche un element sur la fenetre
*/
void afficheElement(struct Element *e){
	glBindTexture(GL_TEXTURE_2D, *(e->texture));
	traceRectanglePlein(e->posx, e->posy, e->posx+e->taille, e->posy+e->taille);
	glBindTexture(GL_TEXTURE_2D,0);
}


/*___________________JOUEUR_____________________*/

/*
*	malloc un joueur
*/ 
Joueur *creerJoueur(){
	return (Joueur*) initElement(5,-.9,0,.05,1/100.,1/100.,"img/0.png");
}


/*___________________ENNEMI_____________________*/

/*
*	malloc un Ennemi 
*/
Ennemi *creerEnnemi(){
	return (Ennemi*) initElement(5,-.9,0,.05,1/100.,1/100.,NULL);
}


/*___________________BONUS_____________________*/

/*
*	malloc un Bonus 
*/
Bonus *creerBonus(){
	return (Bonus*) initElement(5,-.9,0,.05,1/100.,1/100.,NULL);
}


/*___________________OBSTACLE_____________________*/

/*
*	malloc un Obstacle 
*/
Obstacle *creerObstacle(){
	return (Obstacle*) initElement(5,-.9,0,.05,1/100.,1/100.,NULL);
}


