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

#include "affichage/forme.h"
#include "affichage/texture.h"
#include "affichage/windows.h"
#include "affichage/background.h"
#include "monde/monde.h"
#include "monde/jeu.h"
#include "props/element.h"


/* permet l'affichage de tout les éléments du menu */
void Elements(char *str_button1, int fin);

/* Affiche l'image du Menu */
int afficheMenu(char *str_button1, int fin);

/* permet Affichage du titre */
void afficheTitre();

/* affiche bouton et texte du bouton */
void afficheBouton(char *str_button1);

/* Libère la texture appliquée pour le menu */
void freeMenu();

#endif
