#include "liste.h"

#ifndef H_JEU
#define H_JEU
#include "logic.h"

typedef struct jeu{
	liste *list;
	char joueur;
	int tour;
	int blanc;
	int noir;
	listeH *coups;
} jeu;

jeu *initJeu(int, int);
void freeJeu(jeu*);
void startJeu(jeu*);
int estMouvement(char[], char);
int estDeploiementDouble(char[], char);
int estDeploiementTriple(char[], char);
int estPieceDuJoueur(liste*, char, char, char);
void jouerHistorique(jeu *);
void initPlateau(liste*);
void printPlateau(jeu *);
void chargerFichierTest(jeu*, char*);
void sauvegarderHistorique(jeu*, char*);

#endif
