#include "liste.h"

#ifndef H_JEU
#define H_JEU

typedef struct jeu{
	liste *list;
	char joueur;
	int tour;
} jeu;

jeu *initJeu();
void freeJeu(jeu*);
void startJeu(jeu*);
int estMouvement(char[], char);
int estDeploiement(char[], char);
int estPieceDuJoueur(liste*, char, char, char);
void initPlateau(liste*);
void printPlateau(jeu *j);

#endif
