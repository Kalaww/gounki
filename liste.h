#ifndef H_LISTE
#define H_LISTE
#include "piece.h"

typedef struct noeud{
	piece *p;
	struct noeud *next;
} noeud;

typedef struct liste{
	int length;
	struct noeud *first;
} liste;

liste *initListe();
void freeListe(liste*);
void freeNoeud(noeud*);
void freeNoeudRecursive(noeud*);
void addListe(liste*, piece*);
void removeListe(liste*, piece*);
void printListe(liste*);
piece *getPieceByCoordListe(liste*, char, char);
int deplacementPiece(liste*, char, char, char, char);
int deplacementAutoriser(liste*, char, char, char, char, char);
int deploiementAutoriser(liste*, char, char, char, char, char, char, char, char);
int deploiementPossibleSurCases(liste*, char, char, char, char, char);
int deploiementPiece(liste*, char, char, char, char, char, char, char);

#endif
