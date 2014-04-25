#ifndef H_LISTE
#define H_LISTE
#include "piece.h"

typedef struct coords{
	char x;
	char y;
	char x1;
	char y1;
	char x2;
	char y2;
} coords;

typedef struct noeud{
	piece *p;
	struct noeud *next;
} noeud;

typedef struct liste{
	int length;
	struct noeud *first;
} liste;

typedef struct noeudC{
	coords *c;
	struct noeudC *next;
} noeudC;

typedef struct listeC{
	int length;
	struct noeudC *first;
} listeC;

typedef struct listeH{
	int length;
	struct noeudH *first;
	struct noeudH *last;
} listeH;

typedef struct noeudH{
	char c[20];
	struct noeudH *next;
} noeudH;

liste *initListe();
void freeListe(liste*);
void freeNoeud(noeud*);
void freeNoeudRecursive(noeud*);
void addListe(liste*, piece*);
void removeListe(liste*, piece*);
void printListe(liste*);
piece *getPieceByCoordListe(liste*, char, char);

listeC *initListeC();
void freeListeC(listeC*);
void freeNoeudC(noeudC*);
void freeNoeudRecursiveC(noeudC*);
void addListeC(listeC*, coords*);
void removeListeC(listeC*, coords*);
void printListeC(listeC*);

int equalsCoords(coords*, coords*);
coords *initCoordss(char, char, char, char, char, char);
coords *initCoords(char, char, char, char);
coords *initCoord(char, char);

listeH *initListeH();
void freeListeH(listeH*);
void freeNoeudH(noeudH*);
void freeNoeudRecursiveH(noeudH*);
void addListeH(listeH*, char*);
void removeListeH(listeH*, char*);
void printListeH(listeH*);
void removeLastH(listeH*);

#endif
