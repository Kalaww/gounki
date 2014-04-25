#include <stdio.h>
#include <string.h>
#include "jeu.h"

int main(int argc, char *argv[]){
	jeu *j;
	int b = 0, n = 0, i;
	char *fichierCharger = NULL;
	char *fichierTest = NULL;
	
	for(i = 1; i < argc; i++){
		/* joueur blanc */
		if(strlen(argv[i]) == 2 && strcmp(argv[i], "-b") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			if(strcmp(argv[i+1], "h") == 0) b = 1;
			else if(strcmp(argv[i+1], "r1") == 0) b = 2;
			else if(strcmp(argv[i+1], "r2") == 0) b = 3;
			else if(strcmp(argv[i+1], "r3") == 0) b = 4;
			else return 1;
			i++;
		}
		
		/* joueur noir */
		if(strlen(argv[i]) == 2 && strcmp(argv[i], "-n") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			if(strcmp(argv[i+1], "h") == 0) n = 1;
			else if(strcmp(argv[i+1], "r1") == 0) n = 2;
			else if(strcmp(argv[i+1], "r2") == 0) n = 3;
			else if(strcmp(argv[i+1], "r3") == 0) n = 4;
			else return 1;
			i++;
		}
		
		/* fichier à charger */
		if(strlen(argv[i]) == 2 && strcmp(argv[i], "-c") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			fichierCharger = argv[i+1];
			i++;
		}
		
		/* fichier à tester */
		if(strlen(argv[i]) == 2 && strcmp(argv[i], "-t") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			fichierTest = argv[i+1];
			i++;
		}
	}
	
	printf("B:%d N:%d\n", b, n);
	printf("c: %s | t: %s\n", fichierCharger, fichierTest);
	
	j = initJeu(b, n);
	if(fichierCharger != NULL) chargerFichierPlateau(j, fichierCharger);
	if(fichierTest != NULL) chargerFichierTest(j, fichierTest);
	startJeu(j);
	freeJeu(j);
	return 0;
}
