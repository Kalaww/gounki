#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"

jeu *initJeu(int blanc, int noir){
	jeu *j = malloc(sizeof(jeu));
	j->list = initListe();
	j->starter = initListe();
	j->joueur = 'b';
	j->blanc = blanc;
	j->noir = noir;
	j->tour = 1;
	j->coups = initListeH();
	initPlateau(j->list);
	initPlateau(j->starter);
	return j;
}

void freeJeu(jeu *j){
	if(j){
		freeListe(j->list);
		freeListe(j->starter);
		freeListeH(j->coups);
	}
	free(j);
}

void startJeu(jeu *j){
	char sortie = 0, x, y, a, b, a1, b1, a2, b2, commencePar, erreur = 1, *vide;
	char nomSauvegarde[100];
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
			}else if(strlen(input) == 1 && input[0] == 'c'){
				printf("Historique des coups :\n");
				printListeH(j->coups);
			}else if(strlen(input) == 1 && input[0] == 'r'){
				printf("Annulation du dernier coups joué\n");
				removeListeH(j->coups, j->coups->last->c);
				jouerHistorique(j);
				j->joueur = (j->joueur = 'b')? 'n' : 'b';
				if(j->joueur == 'n') j->tour--;
				erreur = 0;
			}else if(strlen(input) == 1 && input[0] == 'h'){
				printf("c : historique des coups\nr : annuler dernier coups\ns : sauvegarder l'historique des coups\nS : sauvegarder le plateau\nq : quitter\n");
			}else if(strlen(input) == 1 && input[0] == 's'){
				printf("[ATTENTION] Sauvegarder un historique de coups d'une configuration de départ personnalisée ne pourra être rejoué que avec cette configuration\n");
				printf("Nom du fichier de sauvegarde ? ");
				fgets(nomSauvegarde, sizeof(nomSauvegarde), stdin);
				vide = strchr(nomSauvegarde, '\n');
				if(vide) *vide = 0;
				sauvegarderHistorique(j, nomSauvegarde);
				printf("Sauvegarde terminée.\n");
			}else if(strlen(input) == 1 && input[0] == 'S'){
				printf("Nom du fichier de sauvegarde ? ");
				fgets(nomSauvegarde, sizeof(nomSauvegarde), stdin);
				vide = strchr(nomSauvegarde, '\n');
				if(vide) *vide = 0;
				sauvegarderPlateau(j, nomSauvegarde);
				printf("Sauvegarde terminée.\n");
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

void jouerHistorique(jeu *j){
	noeudH *courant;
	noeud *starterC;
	int victoire;
	
	freeListe(j->list);
	j->list = initListe();
	j->joueur = 'b';
	j->tour = 1;
	
	starterC = j->starter->first;
	while(starterC != NULL){
		addListe(j->list, initPiece(starterC->p->x, starterC->p->y, starterC->p->couleur, starterC->p->t));
		starterC = starterC->next;
	}
	
	courant = j->coups->first;
	while(courant != NULL){
		if(estMouvement(courant->c, j->joueur)){
			if(estPieceDuJoueur(j->list, courant->c[0], courant->c[1], j->joueur) && deplaValide(j->list, j->joueur, courant->c[0], courant->c[1], courant->c[3], courant->c[4])){
				victoire = deplaPiece(j->list, courant->c[0], courant->c[1], courant->c[3], courant->c[4]);
			}else{
				printf("Erreur : mouvement impossible %s\n", courant->c);
				exit(1);
			}
		}else if(estDeploiementDouble(courant->c, j->joueur)){
			if(estPieceDuJoueur(j->list, courant->c[0], courant->c[1], j->joueur) && deploValide(j->list, j->joueur, courant->c[2], courant->c[0], courant->c[1], courant->c[6], courant->c[7], courant->c[3], courant->c[4])){
				victoire = deploPieceDouble(j->list, j->joueur, courant->c[2], courant->c[0], courant->c[1], courant->c[6], courant->c[7], courant->c[3], courant->c[4]);
			}else{
				printf("Erreur : mouvement impossible %s\n", courant->c);
				exit(1);
			}
		}else if(estDeploiementTriple(courant->c, j->joueur)){
			if(estPieceDuJoueur(j->list, courant->c[0], courant->c[1], j->joueur) && deploValide(j->list, j->joueur, courant->c[2], courant->c[0], courant->c[1], courant->c[9], courant->c[10], courant->c[3], courant->c[4])){
				victoire = deploPieceTriple(j->list, j->joueur, courant->c[2], courant->c[0], courant->c[1], courant->c[9], courant->c[10], courant->c[3], courant->c[4], courant->c[6], courant->c[7]);
			}else{
				printf("Erreur : mouvement impossible %s\n", courant->c);
				exit(1);
			}
		}else{
			printf("ERREUR : %s n'est pas un coups reconnu", courant->c);
			exit(1);
		}
		
		if(victoire > 1){
			if(victoire == 2) printf("Victoire du joueur Blanc !\n");
			else if(victoire == 3) printf("Victoire du joueur Noir !\n");
			else printf("Le jeu s'est terminé sans victoire.\n");
			return;
		}
		
		j->joueur = (j->joueur == 'b')? 'n' : 'b';
		if(j->joueur == 'b') j->tour++;
		courant = courant->next;
	}
}

void chargerFichierTest(jeu *j, char *nomFichier){
	FILE *file;
	char * ligne = NULL;
	size_t len = 0;
	
	file = fopen(nomFichier, "r");
	if(file == NULL){
		printf("Impossible d'ouvrir le fichier\n");
		exit(1);
	}
	
	while(getline(&ligne, &len, file) != -1){
		ligne[strlen(ligne)-1] = '\0';
		addListeH(j->coups, ligne);
	}
	
	if(ligne) free(ligne);
	jouerHistorique(j);
	fclose(file);
}

void sauvegarderHistorique(jeu *j, char *nomFichier){
	FILE *file;
	noeudH *courant;
	
	file = fopen(nomFichier, "w");
	if(file == NULL){
		printf("Impossible d'ouvrir le fichier\n");
		return;
	}
	
	courant = j->coups->first;
	while(courant != NULL){
		fprintf(file, "%s\n", courant->c);
		courant = courant->next;
	}
	
	fclose(file);
}

void chargerFichierPlateau(jeu *j, char *nomFichier){
	FILE *file;
	char *ligne = NULL, x, y;
	type t;
	size_t len = 0;
	
	freeListe(j->list);
	freeListe(j->starter);
	j->list = initListe();
	j->starter = initListe();
	
	file = fopen(nomFichier, "r");
	if(file == NULL){
		printf("Impossible d'ouvrir le fichier\n");
		exit(1);
	}
	
	x = 'a';
	y = '1';
	while(getline(&ligne, &len, file) != -1){
		ligne[strlen(ligne)-1] = '\0';
		if(strlen(ligne) == 2){
			switch(ligne[1]){
				case '0':
					t = vide; break;
				case '1':
					t = carre; break;
				case '2':
					t = rond; break;
				case '3':
					t = ccarre; break;
				case '4':
					t = rrond; break;
				case '5':
					t = cccarre; break;
				case '6':
					t = rrrond; break;
				case '7':
					t = crond; break;
				case '8':
					t = ccrond; break;
				case '9':
					t = crrond; break;
				default:
					printf("Aucune pièce correspond à %c\n", ligne[1]);
					exit(1);
					break;
			}
			if(ligne[0] == 'B'){
				addListe(j->list, initPiece(x, y, 'b', t));
				addListe(j->starter, initPiece(x, y, 'b', t));
			}else if(ligne[0] == 'N'){
				addListe(j->list, initPiece(x, y, 'n', t));
				addListe(j->starter, initPiece(x, y, 'n', t));
			}
		}else{
			printf("La ligne '%s' n'est pas au bon format\n", ligne);
			exit(1);
		}
		
		x++;
		if(x > 'h'){
			x = 'a';
			y++;
		}
	}
	
	fclose(file);
}

void sauvegarderPlateau(jeu *j, char *nomFichier){
	FILE *file;
	char x, y;
	piece *p;
	
	file = fopen(nomFichier, "w");
	if(file == NULL){
		printf("Impossible d'ouvrir le fichier\n");
		return;
	}
	
	for(y = '1'; y <= '8'; y++){
		for(x = 'a'; x <= 'h'; x++){
			p = getPieceByCoordListe(j->list, x, y);
			if(p == NULL) fprintf(file, "V0\n");
			else fprintf(file, "%c%d\n", ((p->couleur == 'b')? 'B':'N'), p->t);
		}
	}
	
	fclose(file);
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
	printf("    -------------------------     h: liste des commandes\n");
}
