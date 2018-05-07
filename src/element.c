#include <math.h>
#include "element.h"
#include "monde.h"
#include "windows.h"

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
	Uint32 intervalle_projectile, int nombreProjectileParTir, float angleTir, float taille_projectile, float vit_deplacement_projectile, 
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
	element->nombreProjectileParTir = nombreProjectileParTir;
	element->angleTir = angleTir;
	element->taille_projectile = taille_projectile;
	element->vit_deplacement_projectile = vit_deplacement_projectile;
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
		while((*list)->next != NULL){
			list = &((*list)->next);
		}
		(*list)->next = elem;
	}
}

/*
*	Retire et free l'élément de la liste
*/
void removeElementFromList(struct Element **elem){
	if(*elem != NULL){	
		struct Element *fils = (*elem)->next;
		free(*elem);
		*elem = fils;
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
*	Si free = 1 : Free l'élément si il sort de l'écran
*/
void moving(struct Element **e, float x, float y, int freeOnTop, int freeOnRight, int freeOnBottom, int freeOnLeft){
	if(*e != NULL){
		(*e)->posx += x*(*e)->vit_deplacement_x;
		(*e)->posy += y*(*e)->vit_deplacement_y;
		if(freeOnLeft == 1 && (*e)->posx < -1){
			removeElementFromList(e);
			moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
		}else{
			if(freeOnRight == 1 && (*e)->posx > 1){
				removeElementFromList(e);
				moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
			}else{
				if(freeOnTop == 1 && (*e)->posy > 1){
					removeElementFromList(e);
					moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
				}else{
					if(freeOnBottom == 1 && (*e)->posy < -1){
						removeElementFromList(e);
						moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
					}else{
						moving(&((*e)->next),x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
					}
				}
			}
		}
	}
}

/*
*	Renvoie 1 si les elements sont en colision
*	0 sinon
*/
int estEnColision(struct Element *e1, struct Element *e2){
	if(e1 == NULL || e2 == NULL)
		return 0;
	if(e1->posx > e2->posx - e2->taille && e1->posx < e2->posx + e2->taille &&
		e1->posy > e2->posy - e2->taille && e1->posy < e2->posy + e2->taille){
		return 1;
	}
	return 0;
}

/*
*	Test colisions entre les listes d'elem
*	Retire les elements mort des listes
*/
void colision(struct Element **liste1, struct Element **liste2){
	if(*liste1 != NULL && *liste2 != NULL){
		//Foreach liste1
		do{
			int meurt_1 = 0, meurt_2 = 0;
			if(*liste2 != NULL){
				//Foreach liste2
				struct Element **liste2_tmp = liste2;
				do{
					meurt_2 = 0; 
					if(estEnColision(*liste1,*liste2_tmp)){
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

/* 
*	Affiche la liste d'élément e sur la fenetre
*/
void afficheElement(struct Element *e){
	if(e != NULL){
		if(!e->texture)
			fprintf(stderr, "afficheElement : TEXTURE NULL\n");
		else{
			float ratio = windowRatio();
			glBindTexture(GL_TEXTURE_2D, *(e->texture));
			traceRectanglePlein(e->posx-(e->taille/ratio), e->posy-(e->taille), e->posx+(e->taille/ratio), e->posy+(e->taille));
			glBindTexture(GL_TEXTURE_2D,0);
		}
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
	int nombreProjectileParTir = 1;
	float angleTir = M_PI*2;
	float taille_projectile = .03;
	float vit_deplacement_projectile = 1/20.;
	GLuint *texture = TEXTURE_JOUEUR;
	return (Joueur*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
}


/*___________________ENNEMI_____________________*/

/*
*	malloc un Ennemi 
*/
Ennemi *creerEnnemi(float x, float y, float vit_deplacement_x, float vit_deplacement_y, Uint32 intervalle_projectile, int nombreProjectileParTir, float angleTir, float taille_projectile, float vit_deplacement_projectile){
	int pv = 5;
	int pa = 1;
	float taille = .1; 
	GLuint *texture = TEXTURE_ENNEMI;
	return (Ennemi*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
}


/*___________________BONUS_____________________*/

/*
*	malloc un Bonus 
*/
Bonus *creerBonus(float x, float y){
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
	GLuint *texture = TEXTURE_BONUS;
	return (Bonus*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
}

/*___________________MALUS_____________________*/

/*
*	malloc malus
*/
Malus *creerMalus(float x, float y){
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
	GLuint *texture = TEXTURE_MALUS;
	return (Malus*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
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
	vit_deplacement_x = -1/1000.;
	vit_deplacement_y = 0; 
	Uint32 intervalle_projectile = 0;
	int nombreProjectileParTir = 0;
	float angleTir = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile = 0;
	GLuint *texture = TEXTURE_OBSTACLE;
	return (Obstacle*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
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
	int pv = 1;
	Uint32 intervalle_projectile = 0;
	int nombreProjectileParTir = 0;
	float angleTir = 0;
	float taille_projectile = 0;
	float vit_deplacement_projectile = 0;
	GLuint *texture = TEXTURE_PROJECTILE;
	return (Projectile*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
}

/*
*	Lance un projectile si le délai depuis la dernier lancement est suffisement grand
*	Return le projectile si a été lancé
*	NULL sinon
*/
Projectile *lance_projectile(struct Element *e){
	if(e == NULL || e->vit_deplacement_projectile == 0)
		return NULL;

	Uint32 now = SDL_GetTicks();
	if(now - e->last_launch > e->intervalle_projectile){
		e->last_launch = SDL_GetTicks();
		if(e->vit_deplacement_projectile >= 0){
			return creerProjectileMultiple(e);
		}else{
			return creerProjectileMultiple(e);
		}
	}
	return NULL;
}

/*
*	Créé les projectiles necessaire à un tir 
*	en prenant en compte le nombreProjectileParTir
*/
Projectile *creerProjectileMultiple(struct Element *e){
	int i;
	Projectile *liste_projectiles = NULL;

	for (i = 0; i < e->nombreProjectileParTir; ++i)
	{
		Projectile *proj;
		float dep_y,dep_x;
		if(e->nombreProjectileParTir == 1){
			dep_y = 0;
			dep_x = 1.;
		}else{
			float angle = i/((e->nombreProjectileParTir-1)*1.)-.5;
			angle *= e->angleTir;
			dep_x = cos(angle);
			dep_y = sin(angle);

		}
		float diag_lenght = (e->taille*sqrt(2))/2 +.1;
		float ray = (e->taille/2)+diag_lenght;
		float posx , posy, vit_parent_x, vit_parent_y;
		if(e->angleTir > 0){
			posx = e->posx+ray*dep_x;
			posy = e->posy+ray*dep_y;
			vit_parent_x = vit_parent_y = 0;
		}
		else {
			posx = e->posx-ray*dep_x;
			posy = e->posy-ray*dep_y;
			vit_parent_x = -e->vit_deplacement_x;
			vit_parent_y = -e->vit_deplacement_y;
		}
			

		proj = creerProjectile(posx, posy, e->taille_projectile, e->pa, dep_x*e->vit_deplacement_projectile+vit_parent_x, dep_y*e->vit_deplacement_projectile+vit_parent_y);
		addElementToList(&liste_projectiles,proj);	
	}
	return liste_projectiles;
}