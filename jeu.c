#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"

jeu *initJeu(){
	jeu *j = malloc(sizeof(jeu));
	j->list = initListe();
	j->joueur = 'b';
	j->tour = 1;
	initPlateau(j->list);
	return j;
}

void freeJeu(jeu *j){
	if(j) freeListe(j->list);
	free(j);
}

void startJeu(jeu *j){
	char sortie = 0, x, y, a, b, erreur = 1, *vide;
	char input[10];
	while(sortie != 1){
		printPlateau(j);
		do{
			printf("Quelle pièce souhaitez vous déplacer ? ");
			fgets(input, sizeof(input), stdin);
			vide = strchr(input, '\n');
			if(vide) *vide = 0;
			if(strlen(input) == 1 && input[0] == 'q'){
				erreur = 0;
				sortie = 1;
			}else if(estMouvement(input)){
				x = input[0];
				y = input[1];
				a = input[3];
				b = input[4];
				erreur = 0;
				printf("Déplacement de (%c,%c) en (%c,%c) : ", x, y, a, b);
				if(!mouvementAutoriser(j->list, j->joueur, x, y, a, b))
					printf("[impossible]");
				else 
					printf("[succès]");
				printf("\n");
			}else{
				printf("Mauvaises coordonnées !\n");
			}
		}while(erreur);
		j->joueur = (j->joueur == 'b')? 'n' : 'b';
	}
	printf("Fermeture du jeu\n");
}

int estMouvement(char input[]){
	return strlen(input) == 5 
		&& input[0] >= 'a' && input[0] <= 'h'
		&& input[1] >= '1' && input[1] <= '8'
		&& input[2] == '-'
		&& input[3] >= 'a' && input[3] <= 'h'
		&& input[4] >= '1' && input[4] <= '8';
}

void initPlateau(liste *l){
	char colonne;
	int impair = carre, pair = rond;
	for(colonne = 'a'; colonne <= 'h'; colonne++){
		piece *p1 = initPiece(colonne, '1', 'b', impair);
		piece *p2 = initPiece(colonne, '2', 'b', pair);
		piece *p3 = initPiece(colonne, '7', 'n', impair);
		piece *p4 = initPiece(colonne, '8', 'n', pair);
		addListe(l, p1);
		addListe(l, p2);
		addListe(l, p3);
		addListe(l, p4);
		impair = (impair == carre)? rond : carre;
		pair = (pair == carre)? rond : carre;
	}
}

void printPlateau(jeu *j){
	char colonne, ligne;
	piece *p;
	printf("     a  b  c  d  e  f  g  h\n"); 	
	printf("    -------------------------\n");
	for(ligne = '8'; ligne >= '1'; ligne--){
		printf(" %c | ", ligne);
		for(colonne = 'a'; colonne <= 'h'; colonne++){
			p = getPieceByCoordListe(j->list, colonne, ligne);
			if(p)
				printf("%c%d ", p->couleur, p->t);
			else
				printf(" . ");
		}
		printf("|");
		if(ligne == '5') printf("  TOUR %d (%s)", j->tour, (j->joueur == 'b')? "blanc" : "noir");
		printf("\n");
	}
	printf("    -------------------------\n");
}
