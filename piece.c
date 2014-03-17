#include <stdlib.h>
#include <stdio.h>
#include "piece.h"

piece *initPiece(char x, char y, char couleur, type t){
	piece *tmp = malloc(sizeof(piece));
	tmp->x = x;
	tmp->y = y;
	tmp->couleur = couleur;
	tmp->t = t;
	return tmp;
}

void freePiece(piece *p){
	free(p);
}

int equalsPiece(piece *a, piece *b){
	return 	a->x == b->x &&
			a->y == b->y &&
			a->couleur == b->couleur &&
			a->t == b->t;
}

char* strPiece(piece *p){
	char *mot = malloc(sizeof(char)*7);
	sprintf(mot, "(%c,%c)%c%d", p->x, p->y, p->couleur, p->t);
	return mot;
}

int deplacementPiece(piece *p, char a, char b){
	return 1;
}
