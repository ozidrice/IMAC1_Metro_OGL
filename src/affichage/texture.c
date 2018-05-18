#include "affichage/texture.h"

static GLuint *TEXTURE_JOUEUR;
static GLuint *TEXTURE_PROJECTILE;
static GLuint *TEXTURE_OBSTACLE;
static GLuint *TEXTURE_ENNEMI;
static GLuint *TEXTURE_ENNEMI_BIG;
static GLuint *TEXTURE_BONUS_VIE;
static GLuint *TEXTURE_BONUS_VITESSE;
static GLuint *TEXTURE_BONUS_TAILLE;
static GLuint *TEXTURE_MALUS_VIE;
static GLuint *TEXTURE_MALUS_TAILLE;
static GLuint *TEXTURE_MALUS_TROU;
static GLuint *TEXTURE_TITRE;
static GLuint *TEXTURE_MENU;


/*
*	Précharge les textures pour pouvoir les utiliser plus tard
*/
void preload_texture(){
	TEXTURE_JOUEUR = generateID("img/joueur2.png");
	TEXTURE_PROJECTILE = generateID("img/USB.png");
	TEXTURE_OBSTACLE = generateID("img/obstacles.png");
	TEXTURE_ENNEMI = generateID("img/rat.png");
	TEXTURE_ENNEMI_BIG = generateID("img/ennemi_bigboss.png");
	TEXTURE_BONUS_VIE = generateID("img/bonus_pv.png");
	TEXTURE_BONUS_VITESSE = generateID("img/bonus_vitesse.png");
	TEXTURE_BONUS_TAILLE = generateID("img/bonus_taille.png");
	TEXTURE_MALUS_VIE = generateID("img/malus_pv.png");
	TEXTURE_MALUS_TAILLE = generateID("img/malus_taille.png");
	TEXTURE_MALUS_TROU = generateID("img/malus_trou.png");
	TEXTURE_TITRE = generateID("img/title.png");
	TEXTURE_MENU = generateID("img/menuu.png");

}

/*
*	Free les textures chargés
*/
void free_texture(){
	glDeleteTextures(1,TEXTURE_JOUEUR);
	glDeleteTextures(1,TEXTURE_PROJECTILE);
	glDeleteTextures(1,TEXTURE_OBSTACLE);
	glDeleteTextures(1,TEXTURE_ENNEMI);
	glDeleteTextures(1,TEXTURE_ENNEMI_BIG);
	glDeleteTextures(1,TEXTURE_BONUS_VIE);
	glDeleteTextures(1,TEXTURE_BONUS_VITESSE);
	glDeleteTextures(1,TEXTURE_BONUS_TAILLE);
	glDeleteTextures(1,TEXTURE_MALUS_TAILLE);
	glDeleteTextures(1,TEXTURE_MALUS_VIE);
	glDeleteTextures(1,TEXTURE_MALUS_TROU);
	glDeleteTextures(1,TEXTURE_TITRE);
	glDeleteTextures(1,TEXTURE_MENU);

}

/* 
*	Retourne la texture choisie
*/
GLuint *get_texture(char *str){
	if(strcmp(str,"TEXTURE_JOUEUR") == 0)
		return TEXTURE_JOUEUR;
	if(strcmp(str,"TEXTURE_OBSTACLE") == 0)
		return TEXTURE_OBSTACLE;
	if(strcmp(str,"TEXTURE_PROJECTILE") == 0)
		return TEXTURE_PROJECTILE;
	if(strcmp(str,"TEXTURE_ENNEMI") == 0)
		return TEXTURE_ENNEMI;
	if(strcmp(str,"TEXTURE_ENNEMI_BIG") == 0)
		return TEXTURE_ENNEMI_BIG;
	if(strcmp(str,"TEXTURE_BONUS_VIE") == 0)
		return TEXTURE_BONUS_VIE;
	if(strcmp(str,"TEXTURE_BONUS_VITESSE") == 0)
		return TEXTURE_BONUS_VITESSE;
	if(strcmp(str,"TEXTURE_BONUS_TAILLE") == 0)
		return TEXTURE_BONUS_TAILLE;
	if(strcmp(str,"TEXTURE_MALUS_VIE") == 0)
		return TEXTURE_MALUS_VIE;
	if(strcmp(str,"TEXTURE_MALUS_TAILLE") == 0)
		return TEXTURE_MALUS_TAILLE;
	if(strcmp(str,"TEXTURE_MALUS_TROU") == 0)
		return TEXTURE_MALUS_TROU;
	if(strcmp(str,"TEXTURE_TITRE") == 0)
		return TEXTURE_TITRE;
	if(strcmp(str,"TEXTURE_MENU") == 0)
		return TEXTURE_MENU;
	return NULL;
}

/* 
*	génère texture à partir d'un chemin en paramètres 
*/
GLuint *generateID(char *chemin){
	SDL_Surface* texture_img;
		texture_img= IMG_Load(chemin);
		if(texture_img==NULL){
			fprintf(stderr, "La texture n'a pas été trouvée.\n");
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
