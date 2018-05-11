#ifndef _MENU_
#define _MENU_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL_ttf.h>
#include <png.h>

#include "forme.h"
#include "texture.h"
#include "windows.h"
#include "background.h"
#include "monde.h"
#include "jeu.h"
#include "element.h"


/* gère choix du joueur */
int actionBouton();

/* permet l'affichage de tout les éléments du menu */
void ElementMenu();

/* Affiche l'image du Menu */
int afficheMenu();

/* permet Affichage du titre */
void afficheTitre();

/* affiche bouton et texte du bouton */
void afficheBouton();

/* Libère la texture appliquée pour le menu */
void freeMenu();

#endif
