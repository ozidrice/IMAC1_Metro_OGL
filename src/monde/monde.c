#include <math.h>
#include "monde/monde.h"
static float VIT_DEFILEMENT_DEFAUT = 1; //n fois la vitesse de déplacement définie de l'élement

/* 
*	Malloc un monde 
*/
Monde *creerMonde(){
	Monde *m = (Monde *)malloc(sizeof(Monde));
	m->joueur = creerJoueur(get_texture("TEXTURE_JOUEUR"));
	m->liste_projectiles = NULL;
	m->liste_ennemis = NULL;
	m->liste_obstacle = NULL;
	m->liste_bonus = NULL;
	m->liste_malus = NULL;
	m->background = creerBackground("img/fondjeu.png",6.,.001);
	m->vit_defilement_x = VIT_DEFILEMENT_DEFAUT;
	return m;
}

/*
*	Affiche le monde et ses parametre dans la fenetre
*/
void afficherMonde(Monde *m){
	afficheBackground(m->background);
	afficheElement(m->joueur);
	afficheElement(m->liste_projectiles);
	afficheElement(m->liste_ennemis);
	afficheElement(m->liste_obstacle);
	afficheElement(m->liste_ennemis);	
	afficheElementDeclencheur(m->liste_bonus);
	afficheElementDeclencheur(m->liste_malus);
}



/* lance la map correspondant au niveau */

void LancerMonde(Monde *m, int niveau){
	char * MAP = NULL;
 	switch(niveau) {
        case 1:
            MAP = "bin/map/map7.bmp";
              break;
        case 2:
			MAP = "bin/map/map6.bmp";
              break;
        case 3:
			MAP = "bin/map/map5.bmp"; 
           	  break;
        default:
 	 	  break;
    }
	chargerMonde(m,MAP);
}

/*
*	Return 1 si est finit
*	0 sinon
*/
int est_finit(Monde *m){
	if(m->joueur == NULL){
		printf("1\n");
		return 1;   
	}
	// printf("%p\n",m->liste_ennemis );
	if(m->liste_ennemis == NULL){
		printf("2\n");
		return 1;
	}
	return 0;
}

/*
*	Fait les actions necessaires à la prochaine frame
*/
void action(Monde *m){
	defilerMonde(m);
	defilerProjectiles(m);
	
	generateNewProjectiles(m,m->joueur);
	generateNewProjectiles(m,m->liste_ennemis);
	
	collisionsJoueur(m);
	collisionsElement(m);
	collisionsElementDeclencheur(m);
}

/*
*	Fait les calculs necessaire avec les collisions entre les elem
*/
void collisionsElement(Monde *m){
	Obstacle **o_tmp = &(m->liste_obstacle);
	Projectile **p_tmp = &(m->liste_projectiles);
	Ennemi **e_tmp = &(m->liste_ennemis);
	collision(p_tmp, o_tmp);
	collision(p_tmp, e_tmp);
}

/*
*	Fait les calculs necessaire avec les collisions entre les elem declencheurs
*/
void collisionsElementDeclencheur(Monde *m){
	Malus **b_tmp = &(m->liste_bonus);
	Bonus **m_tmp = &(m->liste_malus);
	collisionBonus(b_tmp,m);
	collisionMalus(m_tmp,m);
	gererElementDeclencheurActif(1,b_tmp,m);
	gererElementDeclencheurActif(2,m_tmp,m);
}

/*
*	Fait les calculs necessaire avec les collisions entre le joueurs et les elem
*/
void collisionsJoueur(Monde *m){
	collision(&m->joueur, &(m->liste_projectiles));
	collision(&m->joueur, &(m->liste_obstacle));
	collision(&m->joueur, &(m->liste_ennemis));
}

/*
*	 Ajoute le Malus ma au monde 
*/

void ajouterMalus(Monde *m, Malus *ma){
	addElementDeclencheurToList(&m->liste_malus,ma);
}

/*
*	 Ajoute le Bonus b au monde 
*/
void ajouterBonus(Monde *m, Bonus *b){
	addElementDeclencheurToList(&m->liste_bonus,b);
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
	moving(&(m->liste_obstacle), 1., 1., 0,0,0,1.);
	moving(&(m->liste_ennemis), 1., 1., 0,0,0,1.);
	movingElementDeclencheur(&(m->liste_bonus), 1., 1., 0,0,0,0);
	movingElementDeclencheur(&(m->liste_malus), 1., 1., 0,0,0,0);
}




/*
*	Fait défiler les projectiles à leur vitesse de déplacement
*/
void defilerProjectiles(Monde *m){
	moving(&(m->liste_projectiles),1,1,1,1,1,1);
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



/* Charge le monde (ajouter lien vers le fichier de la map en parametre ?) */
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
				Obstacle *o = creerObstacle(x*0.001,((map->h - y)*0.001)-0.4,get_texture("TEXTURE_OBSTACLE"));
				ajouterObstacle(m,o);
			}
			if(r==165 && g==0 && b==0) /* Rouge => ennemi */
			{
				Ennemi *en = creerEnnemi(x*0.001,((map->h - y)*0.001)-0.4,-1/1000.,0,2000,5,-M_PI,1/100.,-1/100.,get_texture("TEXTURE_ENNEMI"));
				ajouterEnnemi(m,en);
			}
			if(r==255 && g==255 && b==165) /* Jaune => Bonus */
			{
				Bonus *b = creerBonus(x*0.001,((map->h - y)*0.001)-0.4,get_texture("TEXTURE_BONUS"),0,1);
				ajouterBonus(m,b);			
			}

			if(r==165 && g==0 && b==255) /* Violet => Malus */
			{
				Malus *ma = creerMalus(x*0.001,((map->h - y)*0.001)-0.4,get_texture("TEXTURE_MALUS"),1000,1);
				ajouterMalus(m,ma);			
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
	freeElementDeclencheur(m->liste_bonus);
	freeElementDeclencheur(m->liste_malus);
	freeBackground(m->background);
	free(m);
}

/*
*	Créé les projectiles necessaire
*/
void generateNewProjectiles(Monde *m, struct Element *liste_elem){
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
