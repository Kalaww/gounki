#include <stdio.h>
#include "jeu.h"

int main(){
	jeu *j = initJeu();
	startJeu(j);
	freeJeu(j);
	return 0;
}
