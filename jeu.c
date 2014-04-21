#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"

jeu *initJeu(){
	jeu *j = malloc(sizeof(jeu));
	j->list = initListe();
	j->joueur = 'b';
	j->tour = 1;
	j->coups = initListeH();
	initPlateau(j->list);
	return j;
}

void freeJeu(jeu *j){
	if(j){
		freeListe(j->list);
		freeListeH(j->coups);
	}
	free(j);
}

void startJeu(jeu *j){
	char sortie = 0, x, y, a, b, a1, b1, a2, b2, commencePar, erreur = 1, *vide;
	char input[20];
	int victoire = 0, coupsSucces = 0;
	while(sortie != 1 && victoire < 2){
		printPlateau(j);
		erreur = 1;
		coupsSucces = 0;
		do{
			printf("Quelle pièce souhaitez vous déplacer ? ");
			fgets(input, sizeof(input), stdin);
			vide = strchr(input, '\n');
			if(vide) *vide = 0;
			if(strlen(input) == 1 && input[0] == 'q'){
				erreur = 0;
				sortie = 1;
			}else if(estMouvement(input, j->joueur)){
				x = input[0];
				y = input[1];
				a = input[3];
				b = input[4];
				printf("Déplacement de (%c,%c) en (%c,%c) : ", x, y, a, b);
				if(estPieceDuJoueur(j->list, x, y, j->joueur) && deplaValide(j->list, j->joueur, x, y, a, b)){
					victoire = deplaPiece(j->list, x, y, a, b);
					coupsSucces = 1;
					if(victoire){
						printf("[succès][%d]", victoire);
						erreur = 0;
					}
				}else{
					printf("[impossible]");
				}
				printf("\n");
			}else if(estDeploiementDouble(input, j->joueur)){
				x = input[0];
				y = input[1];
				a1 = input[3];
				b1 = input[4];
				a = input[6];
				b = input[7];
				commencePar = input[2];
				printf("Déploiement de (%c,%c) en (%c,%c) commençant par les %s en (%c,%c)\n", x, y, a, b, (commencePar == '+')? "carrés" : "ronds", a1, b1);
				if(estPieceDuJoueur(j->list, x, y, j->joueur) && deploValide(j->list, j->joueur, commencePar, x, y, a, b, a1, b1)){
					victoire = deploPieceDouble(j->list, j->joueur, commencePar, x, y, a, b, a1, b1);
					coupsSucces = 1;
					if(victoire){
						printf("[succès][%d]", victoire);
						erreur = 0;
					}
				}else{
					printf("[impossible]");
				}
				printf("\n");
			}else if(estDeploiementTriple(input, j->joueur)){
				x = input[0];
				y = input[1];
				a1 = input[3];
				b1 = input[4];
				a2 = input[6];
				b2 = input[7];
				a = input[9];
				b = input[10];
				commencePar = input[2];
				printf("Déploiement de (%c,%c) en (%c,%c) commençant par les %s en (%c,%c)(%c,%c)\n", x, y, a, b, (commencePar == '+')? "carrés" : "ronds", a1, b1, a2, b2);
				if(estPieceDuJoueur(j->list, x, y, j->joueur) && deploValide(j->list, j->joueur, commencePar, x, y, a, b, a1, b1)){
					coupsSucces = 1;
					victoire = deploPieceTriple(j->list, j->joueur, commencePar, x, y, a, b, a1, b1, a2, b2);
					if(victoire){
						printf("[succès][%d]", victoire);
						erreur = 0;
					}
				}else{
					printf("[impossible]");
				}
				printf("\n");
			}else{
				printf("Mauvaises coordonnées !\n");
			}
		}while(erreur);
		if(coupsSucces) addListeH(j->coups, input);
		j->joueur = (j->joueur == 'b')? 'n' : 'b';
		if(j->joueur == 'b') j->tour++;
		printListeH(j->coups);
	}
	if(victoire > 1){
		if(victoire == 2) printf("Victoire du joueur Blanc !\n");
		else if(victoire == 3) printf("Victoire du joueur Noir !\n");
		else printf("Le jeu s'est terminé sans victoire.\n");
	}
	printf("Fermeture du jeu\n");
}

int estMouvement(char input[], char couleur){
	return strlen(input) == 5 
		&& input[0] >= 'a' && input[0] <= 'h'
		&& input[1] >= '1' && input[1] <= '8'
		&& input[2] == '-'
		&& input[3] >= 'a' && input[3] <= 'h'
		&& ((couleur == 'n' && input[4] >= '0') || (input[4] >= '1')) && ((couleur == 'b' && input[5]  <= '9') || (input[5] <= '8'));
}

int estDeploiementDouble(char input[], char couleur){
	return strlen(input) == 8 
		&& input[0] >= 'a' && input[0] <= 'h'
		&& input[1] >= '1' && input[1] <= '8'
		&& (input[2] == '+' || input[2] == '*')
		&& input[3] >= 'a' && input[3] <= 'h'
		&& ((couleur == 'n' && input[4] >= '0') || (input[4] >= '1')) && ((couleur == 'b' && input[5]  <= '9') || (input[5] <= '8'))
		&& input[5] == '-'
		&& input[6] >= 'a' && input[6] <= 'h'
		&& ((couleur == 'n' && input[7] >= '0') || (input[7] >= '1')) && ((couleur == 'b' && input[7]  <= '9') || (input[7] <= '8'));
}

int estDeploiementTriple(char input[], char couleur){
	return strlen(input) == 11 
		&& input[0] >= 'a' && input[0] <= 'h'
		&& input[1] >= '1' && input[1] <= '8'
		&& (input[2] == '+' || input[2] == '*')
		&& input[3] >= 'a' && input[3] <= 'h'
		&& ((couleur == 'n' && input[4] >= '0') || (input[4] >= '1')) && ((couleur == 'b' && input[5]  <= '9') || (input[5] <= '8'))
		&& input[5] == '-'
		&& input[6] >= 'a' && input[6] <= 'h'
		&& ((couleur == 'n' && input[7] >= '0') || (input[7] >= '1')) && ((couleur == 'b' && input[7]  <= '9') || (input[7] <= '8'))
		&& input[8] == '-'
		&& input[9] >= 'a' && input[9] <= 'h'
		&& ((couleur == 'n' && input[10] >= '0') || (input[10] >= '1')) && ((couleur == 'b' && input[10]  <= '9') || (input[10] <= '8'));
}

int estPieceDuJoueur(liste *l, char x, char y, char couleur){
	piece *p = getPieceByCoordListe(l, x, y);
	if(p == NULL){
		printf("Aucune pièce sur cette case (%c,%c)", x, y);
		return 0;
	}else if(p->couleur != couleur){
		printf("La pièce est pas de la bonne couleur");
		return 0;
	}
	return 1;
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
		if(ligne == '8') printf("    1: c    2: r");
		if(ligne == '7') printf("    3: cc   4: rr");
		if(ligne == '6') printf("    5: ccc  6: rrr");
		if(ligne == '5') printf("    7: cr   8: ccr");
		if(ligne == '4') printf("    9: crr");
		if(ligne == '2') printf("    TOUR %d (%s)", j->tour, (j->joueur == 'b')? "blanc" : "noir");
		printf("\n");
	}
	printf("    -------------------------\n");
}
