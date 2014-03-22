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
int estMouvement(char[]);
int estDeploiement(char[]);
void initPlateau(liste*);
void printPlateau(jeu *j);

#endif
