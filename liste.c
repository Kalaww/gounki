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

int mouvementAutoriser(liste *l, char couleur, char x, char y, char a, char b){
	piece *depart, *arrivee;
	int sens = (couleur == 'b')? 1 : -1;
	depart = getPieceByCoordListe(l, x, y);
	arrivee = getPieceByCoordListe(l, a, b);
	if(depart == NULL){
		printf("Aucune pièce sur la case de départ\n");
		return 0;
	}
	
	if(depart->t == carre && 
			((a == depart->x-1 && b == depart->y) || 
			(a == depart->x+1 && b == depart->y) ||
			(a == depart->x && b == depart->y+sens))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == rond && b == depart->y+sens &&
			(a == depart->x-1 || a == depart->x+1)){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == ccarre &&
			((a == depart->x-2 && b == depart->y && getPieceByCoordListe(l, x-1, y) == NULL) || 
			(a == depart->x+2 && b == depart->y && getPieceByCoordListe(l, x+1, y) == NULL) ||
			(a == depart->x && b == depart->y+2*sens && getPieceByCoordListe(l, x, y+sens) == NULL))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == rrond && b == depart->y+2*sens &&
			((a == depart->x-2 && getPieceByCoordListe(l, x-1, y+sens) == NULL) || 
			(a == depart->x+2 && getPieceByCoordListe(l, x+1, y+sens) == NULL))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == cccarre && 
			((a == depart->x-3 && b == depart->y && getPieceByCoordListe(l, x-1, y) == NULL && getPieceByCoordListe(l, x-2, y) == NULL) || 
			(a == depart->x+3 && b == depart->y && getPieceByCoordListe(l, x+1, y) == NULL && getPieceByCoordListe(l, x+2, y) == NULL) ||
			(a == depart->x && b == depart->y+3*sens && getPieceByCoordListe(l, x, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == rrrond && b == depart->y+3*sens &&
			((a == depart->x-3 && getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x-2, y+2*sens) == NULL) || 
			(a == depart->x+3 && getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x+2, y+2*sens) == NULL))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == crond && 
			((a == depart->x-1 && b == depart->y) || 
			(a == depart->x+1 && b == depart->y) ||
			(a == depart->x && b == depart->y+sens) ||
			(b == depart->y+sens && (a == depart->x-1 || a == depart->x+1)))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == ccrond &&
			((a == depart->x-2 && b == depart->y && getPieceByCoordListe(l, x-1, y) == NULL) || 
			(a == depart->x+2 && b == depart->y && getPieceByCoordListe(l, x+1, y) == NULL) ||
			(a == depart->x && b == depart->y+2*sens && getPieceByCoordListe(l, x, y+sens) == NULL) ||
			(b == depart->y+sens && (a == depart->x-1 || a == depart->x+1)))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}else if(depart->t == crrond &&
			((a == depart->x-1 && b == depart->y) || 
			(a == depart->x+1 && b == depart->y) ||
			(a == depart->x && b == depart->y+sens) ||
			(b == depart->y+2*sens && ((a == depart->x-2 && getPieceByCoordListe(l, x-1, y+sens) == NULL) || (a == depart->x+2 && getPieceByCoordListe(l, x+1, y+sens) == NULL))))){
		return deplacementPiece(l, depart, arrivee, a, b);
	}
	return 0;
}

int deplacementPiece(liste *l, piece *depart, piece *arrivee, char a, char b){
	if(arrivee != NULL){
		if(arrivee->couleur != depart->couleur){
			removeListe(l, arrivee);
		}else{
			if(empilementPiece(depart, arrivee))
				removeListe(l, arrivee);
			else
				return 0;
		}
	}
	depart->x = a;
	depart->y = b;
	return 1;
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

