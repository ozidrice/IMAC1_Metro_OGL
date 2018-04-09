#include "joueur.h"

/*
*	malloc un joueur
*/
Joueur *creerJoueur(){
	Joueur *j = (Joueur *)malloc(sizeof(Joueur));
	if(j != NULL){
		j->e = initElement(5., -0.9, 0, 0.05, NULL);
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