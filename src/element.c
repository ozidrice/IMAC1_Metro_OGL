#include "element.h"
#include "monde.h"

/* 
*	Malloc un element 
*/
struct Element *initElement(int pv, int pa, 
	float x, float y, float taille, 
	float vit_deplacement_x, float vit_deplacement_y, 
	float frequence_projectile, float taille_projectile,
	char * path_texture){
	
	struct Element* element = malloc(sizeof(struct Element));
	if (!element)
		return NULL;
	element->pv= pv;
	element->pa= pa;
	element->posx=x;
	element->posy=y;
	element->taille=taille;
	element->vit_deplacement_x = vit_deplacement_x;
	element->vit_deplacement_y = vit_deplacement_y;
	element->frequence_projectile = frequence_projectile;
	element->taille_projectile = taille_projectile;
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
	int pv = 5;
	int pa = 1; 
	float x = -.9;
	float y = 0;
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	float frequence_projectile = 1;
	float taille_projectile = .03;
	char * path_texture = "img/perso.png";
	return (Joueur*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,frequence_projectile,taille_projectile,path_texture);
}


/*___________________ENNEMI_____________________*/

/*
*	malloc un Ennemi 
*/
Ennemi *creerEnnemi(float x, float y){
	int pv = 5;
	int pa = 1;
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	float frequence_projectile = 1;
	float taille_projectile = .03;
	char * path_texture = NULL;
	return (Ennemi*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,frequence_projectile,taille_projectile,path_texture);
}


/*___________________BONUS_____________________*/

/*
*	malloc un Bonus 
*/
Bonus *creerBonus(float x, float y){
	int pv = 5;
	int pa = 1; 
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	float frequence_projectile = 1;
	float taille_projectile = .03;
	char * path_texture = NULL;
	return (Bonus*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,frequence_projectile,taille_projectile,path_texture);
}


/*___________________OBSTACLE_____________________*/

/*
*	malloc un Obstacle 
*/
Obstacle *creerObstacle(float x, float y){
	int pv = 5;
	int pa = 1; 
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	float frequence_projectile = 1;
	float taille_projectile = .03;
	char * path_texture = NULL;
	return (Obstacle*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,frequence_projectile,taille_projectile,path_texture);
}


/*___________________PROJECTILE_____________________*/

/*
*	malloc un Projectile 
*/
Projectile *creerProjectile(float x, float y){
	int pv = 5;
	int pa = 1; 
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y; 
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	float frequence_projectile = 1;
	float taille_projectile = .03;
	char * path_texture = "img/projectile.png";
	return (Projectile*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,frequence_projectile,taille_projectile,path_texture);
}


