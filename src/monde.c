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

	afficheElement(m->liste_obstacle);
		
}

/*
*	Fait lancer et déplacer les élements necessaires
*/
void action(Monde *m){
	//Deplacement projectiles
	if(m->liste_projectiles != NULL){
		Projectile *p_tmp = m->liste_projectiles;
		do{
			moving(p_tmp,1,1);
			p_tmp = p_tmp->next;
		}while(p_tmp != NULL);
	}

	//Creation des projectiles
	if(m->joueur != NULL){
		Projectile *p_tmp = lance_projectile(m->joueur);
		if(p_tmp != NULL){
			addElementToList(&m->liste_projectiles, p_tmp);
		}
	}

	//Test colisions joueur
	//Avec un projectile
	if(m->liste_projectiles != NULL){	
		Projectile *p_tmp = m->liste_projectiles;
		do{
			if(estEnColision(m->joueur,p_tmp))
				//TODO
		}while(p_tmp != NULL);
	}
	//Avec un obstacle
	if(m->liste_obstacle != NULL){	
		Obstacle *o_tmp = m->liste_obstacle;
		do{
			if(estEnColision(m->joueur,o_tmp))
				//TODO
			o_tmp = o_tmp->next;
		}while(o_tmp != NULL);
	}
}

/*
*	Ajoute l'obstacle o au monde
*/
void ajouterObstacle(Monde *m, Obstacle *o){
	addElementToList(&m->liste_obstacle,o);
}

/*
*	Fait défiler le monde d'une unité de défilement
*/
void defilerMonde(Monde *m){
	moving(m->liste_obstacle,-VIT_DEFILEMENT_DEFAUT ,0);
}

/*
*	Charge le monde (ajouter lien vers le fichier de la map en parametre ?)
*/
void chargerMonde(Monde *m){
	//JUSTE POUR TEST
	Obstacle *o = creerObstacle(.8,0);
	ajouterObstacle(m,o);
}