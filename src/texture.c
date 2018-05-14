#include "texture.h"

static GLuint *TEXTURE_JOUEUR;
static GLuint *TEXTURE_PROJECTILE;
static GLuint *TEXTURE_OBSTACLE;
static GLuint *TEXTURE_ENNEMI;
static GLuint *TEXTURE_BONUS;
static GLuint *TEXTURE_MALUS;
static GLuint *TEXTURE_TITRE;
static GLuint *TEXTURE_MENU;


/*
*	Précharge les textures pour pouvoir les utiliser plus tard
*/
void preload_texture(){
	TEXTURE_JOUEUR = generateID("img/joueur.png");
	TEXTURE_PROJECTILE = generateID("img/USB.png");
	TEXTURE_OBSTACLE = generateID("img/wall.png");
	TEXTURE_ENNEMI = generateID("img/old2.png");
	TEXTURE_BONUS = generateID("img/infinity.png");
	TEXTURE_MALUS = generateID("img/malus.png");
	TEXTURE_TITRE = generateID("img/littlejourney.png");
	printf("%d\n",*TEXTURE_MALUS);
	TEXTURE_MENU = generateID("img/menu.PNG");
}

/*
*	Free les textures chargés
*/
void free_texture(){
	glDeleteTextures(1,TEXTURE_JOUEUR);
	glDeleteTextures(1,TEXTURE_PROJECTILE);
	glDeleteTextures(1,TEXTURE_OBSTACLE);
	glDeleteTextures(1,TEXTURE_ENNEMI);
	glDeleteTextures(1,TEXTURE_BONUS);
	glDeleteTextures(1,TEXTURE_MALUS);
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
	if(strcmp(str,"TEXTURE_BONUS") == 0)
		return TEXTURE_BONUS;
	if(strcmp(str,"TEXTURE_MALUS") == 0)
		return TEXTURE_MALUS;
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
