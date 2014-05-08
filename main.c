#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"

extern int MM_PROF;
extern int SAVE_END;
extern int SAVE_AUTO;
extern int HEURISTIQUE_LVL;
extern char* SAVE_AUTO_NAME;

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
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-n") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			if(strcmp(argv[i+1], "h") == 0) n = 1;
			else if(strcmp(argv[i+1], "r1") == 0) n = 2;
			else if(strcmp(argv[i+1], "r2") == 0) n = 3;
			else if(strcmp(argv[i+1], "r3") == 0) n = 4;
			else return 1;
			i++;
		}
		
		/* fichier à charger */
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-c") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			fichierCharger = argv[i+1];
			i++;
		}
		
		/* fichier à tester */
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-t") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			fichierTest = argv[i+1];
			i++;
		}
		
		/* profondeur du minimax */
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-p") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			MM_PROF = atoi(argv[i+1]);
			if(MM_PROF == 0){
				printf("Impossible de faire un IA minimax avec un profondeur de recherche de 0\n");
			}
			if(MM_PROF > 10){
				printf("La profondeur du minimax est très grande. Le temps de calcul de l'IA risque d'être important.\n");
			}
			i++;
		}
		
		/* désactive la proposition de sauvegarde de fin de partie */
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-h") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			fichierTest = argv[i+1];
			if(strcmp(argv[i+1], "1") == 0) HEURISTIQUE_LVL = 1;
			else if(strcmp(argv[i+1], "2") == 0) HEURISTIQUE_LVL = 2;
			else{
				printf("La valeur [%s] n'est pas une valeur valide pour -h\n", argv[i+1]);
				exit(1);
			}
			i++;
		}
		
		/* désactive la proposition de sauvegarde de fin de partie */
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-d") == 0){
			SAVE_END = 0;
		}
		
		/* fichier de sauvegarde automatique à la fin d'une partie */
		else if(strlen(argv[i]) == 2 && strcmp(argv[i], "-s") == 0){
			if(i+1 >= argc || strlen(argv[i+1]) == 0 || argv[i+1][0] == '-') return 1;
			SAVE_AUTO_NAME = argv[i+1];
			SAVE_END = 0;
			SAVE_AUTO = 1;
			i++;
		}
	}
	
	j = initJeu(b, n);
	if(fichierCharger != NULL) chargerFichierPlateau(j, fichierCharger);
	if(fichierTest != NULL) chargerFichierTest(j, fichierTest);
	startJeu(j);
	freeJeu(j);
	return 0;
}
