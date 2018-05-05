#include "monde.h"
static float VIT_DEFILEMENT_DEFAUT = 1; //n fois la vitesse de déplacement définie de l'élement

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
*	Affiche le monde et ses parametre dans la fenetre
*/
void afficherMonde(Monde *m){
	creerBackground();

	afficheElement(m->joueur);
	
	afficheElement(m->liste_projectiles);

	afficheElement(m->liste_obstacle);

	afficheElement(m->liste_ennemis);
	
	afficheElement(m->liste_bonus);
}



/* lance la map correspondant au niveau */

void LancerMonde(Monde *m, int niveau){
	char * MAP = NULL;
 	switch(niveau) {
            case 1:
                MAP = "img/map6.bmp";
                  break;
            case 2:
		MAP = "img/map5.bmp";
                  break;
            case 3:
		MAP = "img/map5.bmp"; 
               	  break;
            default:
     	 	  break;
            }
	chargerMonde(m,MAP);
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
			// if(estEnColision(m->joueur,p_tmp))
				//TODO
			p_tmp = p_tmp->next;
		}while(p_tmp != NULL);
	}
	//Avec un obstacle
	if(m->liste_obstacle != NULL){	
		Obstacle *o_tmp = m->liste_obstacle;
		do{
			// if(estEnColision(m->joueur,o_tmp))
				//TODO
			o_tmp = o_tmp->next;
		}while(o_tmp != NULL);
	}
	//Avec un bonus
	if(m->liste_bonus != NULL){	
		Bonus *b_tmp = m->liste_bonus;
		do{
			// if(estEnColision(m->joueur,o_tmp))
				//TODO
			b_tmp = b_tmp->next;
		}while(b_tmp != NULL);
	}
}

/*
*	 Ajoute le Bonus b au monde 
*/
void ajouterBonus(Monde *m, Bonus *b){
	addElementToList(&m->liste_bonus,b);
}


/*
*	Ajoute l'obstacle o au monde
*/
void ajouterObstacle(Monde *m, Obstacle *o){
	addElementToList(&m->liste_obstacle,o);
}

/*
*	Ajoute l'ennemi en au monde
*/
void ajouterEnnemi(Monde *m, Ennemi *en){
	addElementToList(&m->liste_ennemis,en);
}

/*
*	Fait défiler le monde d'une unité de défilement
*/
void defilerMonde(Monde *m){
	moving(m->liste_obstacle,-VIT_DEFILEMENT_DEFAUT ,0);
	moving(m->liste_ennemis,-VIT_DEFILEMENT_DEFAUT ,0);
	moving(m->liste_bonus,-VIT_DEFILEMENT_DEFAUT ,0);
}


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


/*
*	Charge le monde (ajouter lien vers le fichier de la map en parametre ?)
*/

void chargerMonde(Monde *m, char * MAP){

	SDL_Surface *map = NULL;
	map = SDL_LoadBMP(MAP);
	
	int x,y;
	Uint8 r, g,b,a;
	
	for(y=0; y<map->h; y+=22)
	{
		for(x=0; x<map->w; x+=22)
		{
			Uint32 pixel = obtenirPixel(map,x,y);
			SDL_GetRGBA(pixel, map->format, &r, &g, &b, &a);
			if(r==255 && g==165 && b==0) /* Orange == obstacle */
			{
				Obstacle *o = creerObstacle(x*0.001,((map->h - y)*0.001)-0.4);
				//printf(" obstacle : x : %f, y: %f\n", o->posx, o->posy); 
				ajouterObstacle(m,o);
			}
			if(r==165 && g==0 && b==0) /* Rouge => ennemi */
			{
				Ennemi *en = creerEnnemi(x*0.001,((map->h - y)*0.001)-0.4);
				//printf(" Ennemi : x : %f, y: %f\n", en->posx, en->posy); 
				ajouterEnnemi(m,en);
			}
			if(r==255 && g==255 && b==165) /* Jaune => Bonus */
			{
				Bonus *b = creerBonus(x*0.001,((map->h - y)*0.001)-0.4);
				ajouterBonus(m,b);			
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
	freeElement(m->liste_bonus);
}
