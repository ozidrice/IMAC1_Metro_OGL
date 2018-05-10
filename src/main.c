#include "jeu.h"
#include "menu.h"

int main(int argc, char const *argv[])
{
	if(launch() == 1)
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}
