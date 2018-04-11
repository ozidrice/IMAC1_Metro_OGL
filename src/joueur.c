#include "joueur.h"

/*
*	malloc un joueur
*/
Joueur *creerJoueur(){
	Joueur *j = (Joueur *)malloc(sizeof(Joueur));
	if(j != NULL){
		j->e = initElement(5., -0.9, 0, 0.05, "img/0.png");
		j->vit_deplacement_x = 1/100.;
		j->vit_deplacement_y = 1/100.;
	}
	return j;
}


/*
*	affiche un joueur sur la fenetre
*/
void afficheJoueur(Joueur *j){
	glColor3f(1.,0,0);
	afficheElement(j->e);
}

/* Déplace le joueur de x en x et de y en y*/
void deplacer(Joueur *j, float x, float y){
	moving(j->e, j->vit_deplacement_x*x, j->vit_deplacement_y*y);
}
