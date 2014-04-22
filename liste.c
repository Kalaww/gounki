#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

/* LISTE PIECES */

/* Initialise une liste de pièces */
liste *initListe(){
	liste *l = malloc(sizeof(liste));
	l->length = 0;
	l->first = NULL;
	return l;
}

/* Free liste de pièces */
void freeListe(liste *l){
	if(l && l->first) freeNoeudRecursive(l->first);
	free(l);
}

/* Free noeud de pièce */
void freeNoeud(noeud *n){
	if(!n) return;
	freePiece(n->p);
	free(n);
}

/* Free recursif de noeud de pièce */
void freeNoeudRecursive(noeud *n){
	if(n && n->next) freeNoeudRecursive(n->next);
	freeNoeud(n);
}

/* Ajoute une pièce à la liste */
void addListe(liste *l, piece *p){
	noeud *n = malloc(sizeof(noeud));
	n->p = p;
	n->next = l->first;
	l->first = n;
	l->length++;
}

/*Enlève une pièce de la liste */
void removeListe(liste *l, piece *p){
	noeud *courant, *tmp;
	if(l == NULL || l->first == NULL || l->length == 0) return;
	courant = l->first;
	if(equalsPiece(p, courant->p)){
		l->first = courant->next;
		l->length--;
		freeNoeud(courant);
		return;
	}
	while(courant->next != NULL){
		if(equalsPiece(p, courant->next->p)){
			tmp = courant->next;
			courant->next = courant->next->next;
			freeNoeud(tmp);
			l->length--;
			return;
		}
		courant = courant->next;
	}
}

/* Récupère la pièce aux coordonnées x,y, NULL sinon */
piece *getPieceByCoordListe(liste *l, char x, char y){
	noeud *courant;
	if(l == NULL || l->first == NULL || l->length == 0) return NULL;
	courant = l->first;
	while(courant != NULL){
		if(courant->p->x == x && courant->p->y == y) return courant->p;
		courant = courant->next;
	}
	return NULL;
}

/* Affiche la liste de pièces */
void printListe(liste *l){
	noeud* courant;
	courant = l->first;
	while(courant != NULL){
		printf("[%s]", strPiece(courant->p));
		courant = courant->next;
	}
	printf("\n");
}



/*LISTE COORDS */

/* Initialise une liste de coordonnées doubles */
listeC *initListeC(){
	listeC *l = malloc(sizeof(listeC));
	l->length = 0;
	l->first = NULL;
	return l;
}

/* Free liste de coordonnées doubles */
void freeListeC(listeC *l){
	if(l && l->first) freeNoeudRecursiveC(l->first);
	free(l);
}

/* Free noeud de coordonnées doubles */
void freeNoeudC(noeudC *n){
	if(!n) return;
	free(n->c);
	free(n);
}

/* Free noeud récursif de coordonnées doubles */
void freeNoeudRecursiveC(noeudC *n){
	if(n && n->next) freeNoeudRecursiveC(n->next);
	freeNoeudC(n);
}

/* Ajoute une coordonnée double à la liste */
void addListeC(listeC *l, coords *p){
	noeudC *n = malloc(sizeof(noeudC));
	n->c = p;
	n->next = l->first;
	l->first = n;
	l->length++;
}

/* Enlève la coordonée double de la liste */
void removeListeC(listeC *l, coords *p){
	noeudC *courant, *tmp;
	if(l == NULL || l->first == NULL || l->length == 0) return;
	courant = l->first;
	if(equalsCoords(p, courant->next->c)){
		l->first = courant->next;
		l->length--;
		freeNoeudC(courant);
		return;
	}
	while(courant->next != NULL){
		if(equalsCoords(p, courant->next->c)){
			tmp = courant->next;
			courant->next = courant->next->next;
			freeNoeudC(tmp);
			l->length--;
			return;
		}
		courant = courant->next;
	}
}

/* Initialise une coordonnée double */
coords *initCoords(char x1, char x, char y1, char y){
	coords *tmp = malloc(sizeof(coords));
	tmp->x = x;
	if(y > '9') tmp->y = '9';
	else if(y < '0') tmp->y = '0';
	else tmp->y = y;
	
	tmp->x1 = x1;
	if(y1 > '9') tmp->y1 = '9';
	else if(y1 < '0') tmp->y1 = '0';
	else tmp->y1 = y1;
	return tmp;
}

/* Initialise une coordonnée double ne contenant qu'une coordonnée */
coords *initCoord(char x, char y){
	coords *tmp = malloc(sizeof(coords));
	tmp->x = x;
	if(y > '9') tmp->y = '9';
	else if(y < '0') tmp->y = '0';
	else tmp->y = y;
	return tmp;
}

/* Test égalité de deux coordonnées doubles */
int equalsCoords(coords *a, coords *b){
	return a->x == b->x && a->y == b->y && a->x1 == b->x1 && a->y1 == b->y1;
}


/* LISTE COUPS */

/* Initialise une liste de coups */
listeH *initListeH(){
	listeH *l = malloc(sizeof(listeH));
	l->length = 0;
	l->first = NULL;
	l->last = NULL;
	return l;
}

/* Free liste de coups */
void freeListeH(listeH *l){
	if(l && l->first) freeNoeudRecursiveH(l->first);
	free(l);
}

/* Free noeud d'un coups */
void freeNoeudH(noeudH *n){
	if(!n) return;
	free(n);
}

/* Free récursif d'un noeud d'un coups */
void freeNoeudRecursiveH(noeudH *n){
	if(n && n->next) freeNoeudRecursiveH(n->next);
	freeNoeudH(n);
}

/* Ajoute le coups à la liste */
void addListeH(listeH *l, char *s){
	noeudH *n = malloc(sizeof(noeudH));
	strcpy(n->c, s);
	n->next = NULL;
	if(l->first == NULL) l->first = n;
	if(l->last) l->last->next = n;
	l->last = n;
	l->length++;
}

/* Enlève le coups de la liste */
void removeListeH(listeH *l, char *p){
	noeudH *courant, *tmp;
	if(l == NULL || l->first == NULL || l->length == 0) return;
	courant = l->first;
	if(strcmp(p, courant->c) == 0){
		if(l->first == l->last) l->last = NULL;
		l->first = courant->next;
		l->length--;
		freeNoeudH(courant);
		return;
	}
	while(courant->next != NULL){
		if(strcmp(p, courant->next->c) == 0){
			tmp = courant->next;
			courant->next = courant->next->next;
			freeNoeudH(tmp);
			if(courant->next == NULL) l->last = courant;
			l->length--;
			return;
		}
		courant = courant->next;
	}
}

/* Affiche la liste de coups */
void printListeH(listeH *l){
	noeudH* courant;
	courant = l->first;
	while(courant != NULL){
		printf("[%s]", courant->c);
		courant = courant->next;
	}
	printf("\n");
}
