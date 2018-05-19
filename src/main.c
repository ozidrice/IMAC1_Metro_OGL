#include "monde/jeu.h"

int main(int argc, char const *argv[])
{
	if(afficheMenu("    Jouer",0) == 1){
		if(launch() == 1){
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
