#ifndef _MONDE_
#define _MONDE_

#include <png.h>
typedef struct monde Monde;
#include "props/element.h"
#include "props/elementDeclencheur.h"
#include "affichage/forme.h"
#include "affichage/background.h"
typedef struct monde
{
	Joueur *joueur;
	Projectile *liste_projectiles;
	Ennemi *liste_ennemis; 
	Obstacle *liste_obstacle;
	Bonus *liste_bonus;
	Malus *liste_malus;
	Background *background;
	float vit_defilement_x;
}Monde;
#include "props/collision.h"


/* Affiche le monde et ses parametre dans la fenetre */
void afficherMonde(Monde *m);


/* Ajoute le malus m au Monde */
void ajouterMalus(Monde *m, Malus *ma);

/* Ajoute le bonus b au Monde */
void ajouterBonus(Monde *m, Bonus *b);

/* Ajoute l'obstacle o au Monde */
void ajouterObstacle(Monde *m, Obstacle *o);

/* Ajoute l'ennemi e au Monde */
void ajouterEnnemi(Monde *m, Ennemi *e);

/* Charge le monde (ajouter lien vers le fichier de la map en parametre ?) */
void chargerMonde(Monde *m, char * MAP);

/* Gestion des niveaux */
void LancerMonde(Monde *m, int niveau);

/* obtient un pixel de la surface */
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);

/* Ajoute l'obstacle o au Monde */
void ajouterObstacle(Monde *m, Obstacle *o);

/*	Ajoute l'ennemi e au monde*/
void ajouterEnnemi(Monde *m, Ennemi *e);

/* obtient un pixel de la surface */
Uint32 obtenirPixel(SDL_Surface *surface, int x, int y);

/* Malloc un monde */
Monde *creerMonde();

/* free tous les élements du monde */
void freeMonde(Monde *m);


void defilerMonde(Monde *m);
void defilerProjectiles(Monde *m);

/*	Créé les projectiles necessaire*/
void generateNewProjectiles(Monde *m, struct Element *liste_elem);


/*Fait lancer et déplacer les élements necessaires*/
void action(Monde *m);

void collisionsElement(Monde *m);
void collisionsJoueur(Monde *m);

/*	Fait les calculs necessaire avec les collisions entre les elem declencheurs*/
void collisionsElementDeclencheur(Monde *m);


#endif
