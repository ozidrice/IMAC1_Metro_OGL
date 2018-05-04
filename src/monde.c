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


Uint32 obtenirPixel(SDL_Surface *surface, int x, int y)
{
    /*nbOctetsParPixel représente le nombre d'octets utilisés pour stocker un pixel.
    En multipliant ce nombre d'octets par 8 (un octet = 8 bits), on obtient la profondeur de couleur
    de l'image : 8, 16, 24 ou 32 bits.*/
    int nbOctetsParPixel = surface->format->BytesPerPixel;
    /* Ici p est l'adresse du pixel que l'on veut connaitre */
    /*surface->pixels contient l'adresse du premier pixel de l'image*/
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * nbOctetsParPixel;

    /*Gestion différente suivant le nombre d'octets par pixel de l'image*/
    switch(nbOctetsParPixel)
    {
        case 1:
            return *p;

        case 2:
            return *(Uint16 *)p;
        case 3:
	     /*Suivant l'architecture de la machine*/
            if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
                return p[0] << 16 | p[1] << 8 | p[2];
            else
                return p[0] | p[1] << 8 | p[2] << 16;

        case 4:
            return *(Uint32 *)p;
        default:
            return 0; 
    }
}

void chargerMonde(Monde *m){
	SDL_Surface *map = NULL;
	map = SDL_LoadBMP("img/2.bmp");
	
	int x,y;
	Uint8 r, g,b,a;
	
	for(y=0; y<map->h; y+=100)
	{
		for(x=0; x<map->w; x+=100)
		{
			Uint32 pixel = obtenirPixel(map,x,y);
			SDL_GetRGBA(pixel, map->format, &r, &g, &b, &a);
			if(r==255 && g==165 && b==0) /* Orange == obstacle */
			{
				Obstacle *o = creerObstacle(x/1000,y/1000);
				printf("x : %f, y: %f\n", o->posx, o->posy); 
				ajouterObstacle(m,o);
			}
			if(r==165 && g==0 && b==0) /* Rouge => ennemi */
			{
				Ennemi *en = creerEnnemi(0.9,y/1000);
				printf("x : %f, y: %f\n", en->posx, en->posy); 
				ajouterEnnemi(m,en);
			}
			if(r==255 && g==255 && b==165) /* Jaune => Bonus */
			{
				/* TO DO */
			}	
		}
	}
	SDL_FreeSurface(map);
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