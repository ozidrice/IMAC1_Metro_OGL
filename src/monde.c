#include <math.h>
#include "monde.h"
static float VIT_DEFILEMENT_DEFAUT = 0; //n fois la vitesse de déplacement définie de l'élement

/* génère texture à partir d'un chemin en paramètres */
GLuint *generateID(char *chemin){
	SDL_Surface* texture_img;
		texture_img= IMG_Load(chemin);
		if(texture_img==NULL){
			fprintf(stderr, "Le pointeur est NULL, déso.\n");
		        return NULL;
		}
	GLuint *textureID = malloc(sizeof(GLuint));
	glGenTextures(1,textureID);
	
	glBindTexture(GL_TEXTURE_2D, *textureID);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		texture_img->w,
		texture_img->h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		texture_img->pixels);

	glBindTexture(GL_TEXTURE_2D,0);
	SDL_FreeSurface(texture_img);
	return textureID;
}

/* 
*	Malloc un monde 
*/
Monde *creerMonde(){
	Monde *m = (Monde *)malloc(sizeof(Monde));
	m->joueur = creerJoueur();
	m->liste_projectiles = NULL;
	m->liste_ennemis = NULL;
	m->liste_obstacle = NULL;
	m->liste_bonus = NULL;
	m->vit_defilement_x = VIT_DEFILEMENT_DEFAUT;
	return m;
}

/*
*	Créé un fond à la fenetre
*/
void creerBackground(){
	glColor3f(.5,.5,.5);
	traceRectanglePlein(-1.,1.,1.,-1.);
	glColor3f(1,1,1);
}


/*
*	Affiche le monde et ses parametre dans la fenetre
*/
void afficherMonde(Monde *m){
	creerBackground();
	afficheElement(m->joueur);
	afficheElement(m->liste_projectiles);
	afficheElement(m->liste_ennemis);
	afficheElement(m->liste_obstacle);
}

/*
*	Fait les actions necessaires à la prochaine frame
*/
void action(Monde *m){
	defilerMonde(m);
	defilerProjectiles(m);
	
	generateNewProjectiles(m,m->joueur);
	generateNewProjectiles(m,m->liste_ennemis);
	
	colisionsJoueur(m);
	colisionsElement(m);
}

/*
*	Fait les calculs necessaire avec les collisions entre les elem
*/
void colisionsElement(Monde *m){
	Projectile **o_tmp = &(m->liste_obstacle);
	Projectile **p_tmp = &(m->liste_projectiles);
	Projectile **e_tmp = &(m->liste_ennemis);
	colision(p_tmp, o_tmp);
	colision(p_tmp, e_tmp);
}

/*
*	Fait les calculs necessaire avec les collisions entre le joueurs et les elem
*/
void colisionsJoueur(Monde *m){
	colision(&m->joueur, &(m->liste_projectiles));
	colision(&m->joueur, &(m->liste_obstacle));
	colision(&m->joueur, &(m->liste_ennemis));
}


/*
*	Ajoute l'obstacle o au monde
*/
void ajouterObstacle(Monde *m, Obstacle *o){
	addElementToList(&m->liste_obstacle,o);
}

/*
*	Ajoute l'ennemi e au monde
*/
void ajouterEnnemi(Monde *m, Ennemi *e){
	addElementToList(&m->liste_ennemis,e);
}

/*
*	Fait défiler le monde d'une unité de défilement
*/
void defilerMonde(Monde *m){
	moving(&(m->liste_obstacle),-VIT_DEFILEMENT_DEFAUT ,0,1);
}

/*
*	Fait défiler les projectiles à leur vitesse de déplacement
*/
void defilerProjectiles(Monde *m){
	moving(&(m->liste_projectiles),1,1,1);
}

/*
*	Charge le monde (ajouter lien vers le fichier de la map en parametre ?)
*/
void chargerMonde(Monde *m){
	//JUSTE POUR TEST
	Ennemi *e = creerEnnemi(.8,0,0,0,2000.,7,-M_PI,1/100.,-1/1000.);
	//float x, float y, float vit_deplacement_x, float vit_deplacement_y,Uint32 intervalle_projectile, int nombreProjectileParTir, float taille_projectile, float vit_deplacement_projectile_x, float vit_deplacement_projectile_y
	ajouterEnnemi(m,e);
}

/*
*	free tous les élements du monde
*/
void freeMonde(Monde *m){
	freeElement(m->joueur);
	freeElement(m->liste_obstacle);
	freeElement(m->liste_projectiles);
	freeElement(m->liste_ennemis);
}

/*
*	Créé les projectiles necessaire
*/
void generateNewProjectiles(Monde *m, struct Element *liste_elem){;
	if(liste_elem != NULL){
		do{
			Projectile *p_tmp = lance_projectile(liste_elem);
			if(p_tmp != NULL){
				addElementToList(&(m->liste_projectiles), p_tmp);
			}
			liste_elem = liste_elem->next;
		}while(liste_elem != NULL);
	}
}
