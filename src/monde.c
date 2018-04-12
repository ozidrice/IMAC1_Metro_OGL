#include "monde.h"
static float VIT_DEFILEMENT_DEFAUT = .005;

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
	m->defilement_x = 0;
	m->vit_defilement_x = VIT_DEFILEMENT_DEFAUT;
	return m;
}

/*
*	Créé un fond à la fenetre
*/
void creerBackground(){
	glColor3f(.5,.5,.5);
	traceRectanglePlein(-1.,1.,1.,-1.);
}


/*
*	Affiche le monde et ses parametre dans la fenetre
*/
void afficherMonde(Monde *m){
	creerBackground();
	glColor3f(1,1,1);

	//Affichage joueur
	afficheElement(m->joueur);
	
	//Affichage des projectile
	Projectile *p_tmp = m->liste_projectiles;
	while(p_tmp != NULL){
		afficheElement(p_tmp);
		p_tmp = p_tmp->next;
	}

	//Affichage des element qui défilent
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(m->defilement_x,0,0);
	glPopMatrix();
}

/*
*	Fait lancer et déplacer les projectiles necessaires
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
		Projectile *p = lance_projectile(m->joueur);
		if(p != NULL){
			addElementToList(&m->liste_projectiles, p);
		}
	}
}

void defilerMonde(Monde *m){
	m->defilement_x -= m->vit_defilement_x;
	action(m);
}