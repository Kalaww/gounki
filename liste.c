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

int deplacementAutoriser(liste *l, char couleur, char x, char y, char a, char b){
	piece *depart, *arrivee;
	depart = getPieceByCoordListe(l, x, y);
	arrivee = getPieceByCoordListe(l, a, b);
	if(depart == NULL || (arrivee != NULL && arrivee->couleur != couleur)) return 0;
	return deplacementPiece(depart, a, b);
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

