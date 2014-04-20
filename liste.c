#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "liste.h"

liste *initListe(){
	liste *l = malloc(sizeof(liste));
	l->length = 0;
	l->first = NULL;
	return l;
}

void freeListe(liste *l){
	if(l && l->first) freeNoeudRecursive(l->first);
	free(l);
}

void freeNoeud(noeud *n){
	if(!n) return;
	freePiece(n->p);
	free(n);
}

void freeNoeudRecursive(noeud *n){
	if(n && n->next) freeNoeudRecursive(n->next);
	freeNoeud(n);
}

void addListe(liste *l, piece *p){
	noeud *n = malloc(sizeof(noeud));
	n->p = p;
	n->next = l->first;
	l->first = n;
	l->length++;
}

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

listeC *initListeC(){
	listeC *l = malloc(sizeof(listeC));
	l->length = 0;
	l->first = NULL;
	return l;
}

void freeListeC(listeC *l){
	if(l && l->first) freeNoeudRecursiveC(l->first);
	free(l);
}

void freeNoeudC(noeudC *n){
	if(!n) return;
	free(n);
}

void freeNoeudRecursiveC(noeudC *n){
	if(n && n->next) freeNoeudRecursiveC(n->next);
	freeNoeudC(n);
}

void addListeC(listeC *l, coords *p){
	noeudC *n = malloc(sizeof(noeudC));
	n->c = p;
	n->next = l->first;
	l->first = n;
	l->length++;
}

void removeListeC(listeC *l, coords *p){
	noeudC *courant, *tmp;
	if(l == NULL || l->first == NULL || l->length == 0) return;
	courant = l->first;
	if(equalsCoords(p, courant->c)){
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

int equalsCoords(coords *a, coords *b){
	return a->x == b->x && a->y == b->y && a->x1 == b->x1 && a->y1 == b->y1;
}

