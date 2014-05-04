#include "liste.h"

#ifndef H_JEU
#define H_JEU
#include "logic.h"

typedef struct jeu{
	liste *list;
	liste *starter;
	char joueur;
	int tour;
	int blanc;
	int noir;
	listeH *coups;
	listeH *recoups;
} jeu;

jeu *initJeu(int, int);
void freeJeu(jeu*);
void startJeu(jeu*);
int estMouvement(char[], char);
int estDeploiementDouble(char[], char);
int estDeploiementTriple(char[], char);
int estPieceDuJoueur(liste*, char, char, char);
int testVictoire(liste*, char);
void jouerHistorique(jeu *);
void initPlateau(liste*);
void printPlateau(jeu *);
void chargerFichierTest(jeu*, char*);
void sauvegarderHistorique(jeu*, char*);
void chargerFichierPlateau(jeu*, char*);
void sauvegarderPlateau(jeu*, char*);
char* randomIA(jeu*);
char* jouerIA(jeu*);
int evaluationPlateau(jeu*, char);
char* meilleurCoups(jeu*);
int minimaxMax(jeu*, int, int, char, int, int);
int minimaxMin(jeu*, int, int, char, int, int);
char* minimaxIA(jeu*, int);

#endif
