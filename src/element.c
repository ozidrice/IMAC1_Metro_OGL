#include "element.h"
#include "monde.h"
<<<<<<< HEAD
=======
/*___________________ELEMENT_____________________*/
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c

/* 
*	Malloc un element 
*/
<<<<<<< HEAD
Element* initElement(int pv, float x, float y, float taille, char * path_texture){
	Element* element = malloc(sizeof(Element));
=======
struct Element *initElement(int pv, float x, float y, float taille, float vit_deplacement_x, float vit_deplacement_y, char * path_texture){
	struct Element* element = malloc(sizeof(struct Element));
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c
	if (!element)
		return NULL;
	element->pv= pv;
	element->posx=x;
	element->posy=y;
	element->taille=taille;
<<<<<<< HEAD
=======
	element->vit_deplacement_x = vit_deplacement_x;
	element->vit_deplacement_y = vit_deplacement_y;
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c
	element->texture = (path_texture == NULL) ? NULL : generateID(path_texture);
	return element;
}

void moving(struct Element *e, float x, float y){
	e->posx += x*e->vit_deplacement_x;
	e->posy += y*e->vit_deplacement_y;
}

/* 
*	Affiche un element sur la fenetre
*/
<<<<<<< HEAD
void afficheElement(Element *e){
=======
void afficheElement(struct Element *e){
>>>>>>> 296767f831ef38fe47a29c14bf4f9af24b37365c
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


