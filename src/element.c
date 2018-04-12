#include "element.h"
#include "monde.h"

static GLuint *TEXTURE_JOUEUR;
static GLuint *TEXTURE_PROJECTILE;

void preload_texture(){
	TEXTURE_JOUEUR = generateID("img/player.png");
	TEXTURE_PROJECTILE = generateID("img/projectile.png");

}

/* 
*	Malloc un element 
*/
struct Element *initElement(int pv, int pa, 
	float x, float y, float taille, 
	float vit_deplacement_x, float vit_deplacement_y, 
	Uint32 intervalle_projectile, float taille_projectile, float vit_deplacement_projectile_x, float vit_deplacement_projectile_y,
	GLuint *texture){
	
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
	element->last_launch = 0;
	element->intervalle_projectile = intervalle_projectile;
	element->taille_projectile = taille_projectile;
	element->vit_deplacement_projectile_x = vit_deplacement_projectile_x;
	element->vit_deplacement_projectile_y = vit_deplacement_projectile_y;
	element->texture = texture;
	element->next = 0;
	return element;
}

/*
*	Ajoute un élément à la liste
*/
void addElementToList(struct Element **list, struct Element *elem){
	if(*list == NULL){
		*list = elem;
	}else{
		struct Element *tmp = *list;
		while(tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = elem;
	}
}

/*
*	Attaque la cible,
*	return 1 si la cible meurt
*	0 sinon
*/
int attaque(struct Element *attanquant, struct Element *cible){
	if(cible->pv == -1)
		return 0;
	cible->pv -= attanquant->pa;
	return cible->pv <= 0;
}


/*
*	Déplace un élement en prenant compte de sa vitesse de déplacement
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
	traceRectanglePlein(e->posx-(e->taille/2), e->posy-(e->taille/2), e->posx+(e->taille/2), e->posy+(e->taille/2));
	glBindTexture(GL_TEXTURE_2D,0);
}

/*
*	Lance un projectile si le délai depuis la dernier lancement est suffisement grand
*	Return le projectile si a été lancé
*	NULL sinon
*/
Projectile *lance_projectile(struct Element *e){
	Uint32 now = SDL_GetTicks();
	if(now - e->last_launch > e->intervalle_projectile){
		e->last_launch = SDL_GetTicks();
		return creerProjectile(e->posx+(e->taille/2), e->posy, e->taille_projectile, e->pa, e->vit_deplacement_projectile_x, e->vit_deplacement_projectile_y);
	}
	return NULL;
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
	Uint32 intervalle_projectile = 2000;
	float taille_projectile = .03;
	float vit_deplacement_projectile_x = 1/20.;
	float vit_deplacement_projectile_y = 0;
	GLuint *texture = TEXTURE_JOUEUR;
	return (Joueur*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
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
	Uint32 intervalle_projectile = 0;
	float taille_projectile = .03;
	float vit_deplacement_projectile_x = 0;
	float vit_deplacement_projectile_y = 0;
	GLuint *texture = NULL;
	return (Ennemi*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
}


/*___________________BONUS_____________________*/

/*
*	malloc un Bonus 
*/
Bonus *creerBonus(float x, float y){
	int pv = -1;
	int pa = 1; 
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	Uint32 intervalle_projectile = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile_x = 0;
	float vit_deplacement_projectile_y = 0;
	GLuint *texture = NULL;
	return (Bonus*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
}


/*___________________OBSTACLE_____________________*/

/*
*	malloc un Obstacle 
*/
Obstacle *creerObstacle(float x, float y){
	int pv = -1;
	int pa = 1; 
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	Uint32 intervalle_projectile = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile_x = 0;
	float vit_deplacement_projectile_y = 0;
	GLuint *texture = NULL;
	return (Obstacle*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
}


/*___________________PROJECTILE_____________________*/

/*
*	malloc un Projectile 
*/
Projectile *creerProjectile(float x, float y, float taille, int pa, float vit_deplacement_x, float vit_deplacement_y){
	int pv = -1;
	Uint32 intervalle_projectile = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile_x = 0;
	float vit_deplacement_projectile_y = 0;
	GLuint *texture = TEXTURE_PROJECTILE;
	return (Projectile*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
}


