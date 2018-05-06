#include "element.h"
#include "monde.h"

static GLuint *TEXTURE_JOUEUR;
static GLuint *TEXTURE_PROJECTILE;
static GLuint *TEXTURE_OBSTACLE;
static GLuint *TEXTURE_ENNEMI;
static GLuint *TEXTURE_FOND;
static GLuint *TEXTURE_BONUS;
static GLuint *TEXTURE_MALUS;

/*
*	Précharge les textures pour pouvoir les utiliser plus tard
*/
void preload_texture(){
	TEXTURE_JOUEUR = generateID("img/player.png");
	TEXTURE_PROJECTILE = generateID("img/USB.png");
	TEXTURE_OBSTACLE = generateID("img/wall.png");
	TEXTURE_ENNEMI = generateID("img/old2.png");
	TEXTURE_FOND = generateID("img/wall.png");
	TEXTURE_BONUS = generateID("img/bonus.png");
	TEXTURE_MALUS = generateID("img/malus.png");
}

/*
*	Free les textures chargés
*/
void free_texture(){
	glDeleteTextures(1,TEXTURE_JOUEUR);
	glDeleteTextures(1,TEXTURE_PROJECTILE);
	glDeleteTextures(1,TEXTURE_OBSTACLE);
	glDeleteTextures(1,TEXTURE_ENNEMI);
	glDeleteTextures(1,TEXTURE_FOND);
	glDeleteTextures(1,TEXTURE_BONUS);
	glDeleteTextures(1,TEXTURE_MALUS);
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
*	Free la liste d'éléments
*/
void freeElement(struct Element *e){
	if(e != NULL){
		freeElement(e->next);
		free(e);
	}
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
*	Déplace la liste d'élement e en prenant compte de sa vitesse de déplacement
*/
void moving(struct Element *e, float x, float y){
	if(e != NULL){
		e->posx += x*e->vit_deplacement_x;
		e->posy += y*e->vit_deplacement_y;
		moving(e->next,x,y);
	}
}

/*
*	Renvoie 1 si les elements sont en colision
*	0 sinon
*/
int estEnColision(struct Element *e1, struct Element *e2){
	if(e1 == NULL || e2 == NULL)
		return 0;
	if(e1->posx >= e2->posx - e2->taille && e1->posx <= e2->posx + e2->taille &&
		e1->posy >= e2->posy - e2->taille && e1->posy <= e2->posy + e2->taille)
		return 1;
	return 0;
}

/* 
*	Affiche la liste d'élément e sur la fenetre
*/
void afficheElement(struct Element *e){
	if(e != NULL){
		glBindTexture(GL_TEXTURE_2D, *(e->texture));
		traceRectanglePlein(e->posx-(e->taille/2), e->posy-(e->taille/2), e->posx+(e->taille/2), e->posy+(e->taille/2));
		glBindTexture(GL_TEXTURE_2D,0);
		afficheElement(e->next);
	}
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
	GLuint *texture = TEXTURE_ENNEMI;
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
	float vit_deplacement_projectile_y= 0;
	GLuint *texture = TEXTURE_BONUS;
	return (Bonus*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
}

/*___________________MALUS_____________________*/

/*
*	malloc malus
*/
Malus *creerMalus(float x, float y){
	int pv = -1;
	int pa = 1; 
	float taille = .1; 
	float vit_deplacement_x, vit_deplacement_y;
	vit_deplacement_x = vit_deplacement_y = 1/100.; 
	Uint32 intervalle_projectile = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile_x = 0;
	float vit_deplacement_projectile_y= 0;
	GLuint *texture = TEXTURE_MALUS;
	return (Malus*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
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
	GLuint *texture = TEXTURE_OBSTACLE;
	return (Obstacle*) initElement(pa,pv,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,taille_projectile,vit_deplacement_projectile_x,vit_deplacement_projectile_y,texture);
}

/*
* Image de fond
*/
void creerBackground(){
	glBindTexture(GL_TEXTURE_2D, *TEXTURE_FOND);
	traceRectanglePlein(-1.,1.,1.,-1.);
	glBindTexture(GL_TEXTURE_2D,0);

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

/*
*	Lance un projectile si le délai depuis la dernier lancement est suffisement grand
*	Return le projectile si a été lancé
*	NULL sinon
*/
Projectile *lance_projectile(struct Element *e){
	if(e == NULL || e->vit_deplacement_projectile_x == 0)
		return NULL;

	Uint32 now = SDL_GetTicks();
	if(now - e->last_launch > e->intervalle_projectile){
		e->last_launch = SDL_GetTicks();
		if(e->vit_deplacement_projectile_x > 0){
			return creerProjectile(e->posx+(e->taille/2), e->posy, e->taille_projectile, e->pa, e->vit_deplacement_projectile_x, e->vit_deplacement_projectile_y);
		}else{
			return creerProjectile(e->posx-(e->taille/2), e->posy, e->taille_projectile, e->pa, e->vit_deplacement_projectile_x, e->vit_deplacement_projectile_y);

		}
	}
	return NULL;
}


