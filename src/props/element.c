#include <math.h>
#include "props/element.h"

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
	if(elem != NULL && *elem != NULL){	
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
	if(e!= NULL && *e != NULL){
		(*e)->posx += x*(*e)->vit_deplacement_x;
		(*e)->posy += y*(*e)->vit_deplacement_y;
		if(freeOnLeft == 1 && (*e)->posx+(*e)->taille < -1){
			removeElementFromList(e);
			moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
		}else{
			if(freeOnRight == 1 && (*e)->posx-(*e)->taille > 1){
				removeElementFromList(e);
				moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
			}else{
				if(freeOnTop == 1 && (*e)->posy-(*e)->taille > 1){
					removeElementFromList(e);
					moving(e,x,y,freeOnTop,freeOnRight,freeOnBottom,freeOnLeft);
				}else{
					if(freeOnBottom == 1 && (*e)->posy+(*e)->taille < -1){
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
*	Affiche la liste d'élément e sur la fenetre
*/
void afficheElement(struct Element *e){
	if(e != NULL){
		if(!e->texture)
			fprintf(stderr, "afficheElement : TEXTURE NULL\n");
		else{
			float ratio = windowRatio();
			// glColor3f(1,1,0);
			glBindTexture(GL_TEXTURE_2D, *(e->texture));
			traceRectanglePlein(e->posx-(e->taille/ratio), e->posy-(e->taille), e->posx+(e->taille/ratio), e->posy+(e->taille));
			glBindTexture(GL_TEXTURE_2D,0);
			// glColor3f(0,0,0);
		}
		afficheElement(e->next);
	}
}


/*___________________JOUEUR_____________________*/

/*
*	malloc un joueur
*/ 
Joueur *creerJoueur(GLuint *texture){
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
	return (Joueur*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
}


/*___________________ENNEMI_____________________*/

/*
*	malloc un Ennemi 
*/
Ennemi *creerEnnemi(float x, float y, float vit_deplacement_x, float vit_deplacement_y, Uint32 intervalle_projectile, int nombreProjectileParTir, float angleTir, float taille_projectile, float vit_deplacement_projectile, GLuint *texture){
	int pv = 5;
	int pa = 1;
	float taille = .1;
	return (Ennemi*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
}




/*___________________OBSTACLE_____________________*/

/*
*	malloc un Obstacle 
*/
Obstacle *creerObstacle(float x, float y, GLuint *texture){
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
	return (Obstacle*) initElement(pv,pa,x,y,taille,vit_deplacement_x,vit_deplacement_y,intervalle_projectile,nombreProjectileParTir,angleTir,taille_projectile,vit_deplacement_projectile,texture);
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
	GLuint *texture = get_texture("TEXTURE_PROJECTILE");
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
		return creerProjectileMultiple(e);
	}
	return NULL;
}

/*cos
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
		float diag_lenght = (e->taille*sqrt(2))/2+.01;
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
