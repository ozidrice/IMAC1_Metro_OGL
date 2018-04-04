#include <stdio.h>
#include <stdlib.h>
#include "jeu.h"

int main(int argc, char const *argv[])
{
	if(launch() == 1)
		return EXIT_SUCCESS;
	return EXIT_FAILURE;
}