#include <stdlib.h>
#include <stdio.h>
#include "logic.h"


int deplacementValide(liste *l, char couleur, char x, char y, char a, char b){
	piece *depart;
	liste *cases;
	noeud *tmp;
	
	depart = getPieceByCoordListe(l, x, y);
	if(depart == NULL){
		printf("Aucune pièce sur la case de départ\n");
		return 0;
	}
	
	cases = deplacementCasesValides(l, depart->t, depart->couleur, depart->x, depart->y);
	tmp = cases->first;
	while(tmp != NULL){
		if(tmp->p->x == a && tmp->p->y == b) return 1;
		printf("Case possible : %c,%c\n", tmp->p->x, tmp->p->y);
		tmp = tmp->next;
	}
	
	return 0;
}

liste* deplacementCasesValides(liste *l, type t, char couleur, char x, char y){
	liste *cases = initListe();
	int sens = (couleur == 'b')? 1 : -1;
	
	if(t == carre || t == crond || t == crrond){
		if(deplacementPossible(l, couleur, x, y, x-1, y)) addListe(cases, initPiece(x-1, y, couleur, t));
		if(deplacementPossible(l, couleur, x, y, x+1, y)) addListe(cases, initPiece(x+1, y, couleur, t));
		if(deplacementPossible(l, couleur, x, y, x, y+sens)) addListe(cases, initPiece(x, y+sens, couleur, t));
	}
	
	if(t == rond || t == crond || t == ccrond){
		if(deplacementPossible(l, couleur, x, y, x-1, y+sens)) addListe(cases, initPiece(x-1, y+sens, couleur, t));
		if(deplacementPossible(l, couleur, x, y, x+1, y+sens)) addListe(cases, initPiece(x+1, y+sens, couleur, t));
	}
	
	if(t == ccarre || t == ccrond){
		if(getPieceByCoordListe(l, x-1, y) == NULL && deplacementPossible(l, couleur, x, y, x-2, y)) addListe(cases, initPiece(x-2, y, couleur, t));
		if(getPieceByCoordListe(l, x+1, y) == NULL && deplacementPossible(l, couleur, x, y, x+2, y)) addListe(cases, initPiece(x+2, y, couleur, t));
		if(getPieceByCoordListe(l, x, y+sens) == NULL && deplacementPossible(l, couleur, x, y, x, y+2+sens)) addListe(cases, initPiece(x, y+2*sens, couleur, t));
	}
	
	if(t == rrond || t == crrond){
		if(getPieceByCoordListe(l, x-1, y+sens) == NULL && deplacementPossible(l, couleur, x, y, x-2, y+2*sens)) addListe(cases, initPiece(x-2, y+2*sens, couleur, t));
		if(getPieceByCoordListe(l, x+1, y+sens) == NULL && deplacementPossible(l, couleur, x, y, x+2, y+2*sens)) addListe(cases, initPiece(x+2, y+2*sens, couleur, t));
	}
	
	if(t == cccarre){
		if(getPieceByCoordListe(l, x-1, y) == NULL && getPieceByCoordListe(l, x-2, y) == NULL && deplacementPossible(l, couleur, x, y, x-3, y)) addListe(cases, initPiece(x-3, y, couleur, t));
		if(getPieceByCoordListe(l, x+1, y) == NULL && getPieceByCoordListe(l, x+2, y) == NULL && deplacementPossible(l, couleur, x, y, x+3, y)) addListe(cases, initPiece(x+3, y, couleur, t));
		if(getPieceByCoordListe(l, x, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplacementPossible(l, couleur, x, y, x, y+3+sens)) addListe(cases, initPiece(x, y+3*sens, couleur, t));
	}
	
	if(t == rrrond){
		if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x-2, y+sens) == NULL && deplacementPossible(l, couleur, x, y, x-3, y+3*sens)) addListe(cases, initPiece(x-3, y+3*sens, couleur, t));
		if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x+2, y+sens) == NULL && deplacementPossible(l, couleur, x, y, x+3, y+3*sens)) addListe(cases, initPiece(x+3, y+3*sens, couleur, t));
	}
	
	return cases;
}

int deplacementPossible(liste *l, char couleur, char x, char y, char a, char b){
	piece *tmp = getPieceByCoordListe(l, a, b);
	return tmp == NULL || tmp->couleur != couleur || tmp->t == carre || tmp->t == rond || tmp->t == crond || tmp->t == ccarre || tmp->t == rrond;
}

int deplacementPiece(liste *l, char x, char y, char a, char b){
	piece *depart, *arrivee;
	depart = getPieceByCoordListe(l, x, y);
	arrivee = getPieceByCoordListe(l, a, b);
	if(depart == NULL) return 0;
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
	if(b == '0') return 3;
	if(b == '9') return 2;
	return 1;
}
