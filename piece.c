#include <stdlib.h>
#include <stdio.h>
#include "piece.h"

piece *initPiece(char x, char y, char couleur, type t){
	piece *tmp = malloc(sizeof(piece));
	tmp->x = x;
	if(y > '9') tmp->y = '9';
	else if(y < '0') tmp->y = '0';
	else tmp->y = y;
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

int empilementPiece(piece *depart, piece *arrivee){
	if(depart->t == cccarre || depart->t == rrrond || arrivee->t == cccarre || arrivee->t == rrrond
		|| ((depart->t == ccarre|| depart->t == rrond || depart->t == crond) && (arrivee->t == rrond || arrivee->t == ccarre || arrivee->t == crond))){
		return 0;
	}
	
	if(depart->t == carre){
		if(arrivee->t == rond) depart->t = crond;
		else if(arrivee->t == carre) depart->t = ccarre;
		else if(arrivee->t == ccarre) depart->t = cccarre;
		else if(arrivee->t == rrond) depart->t = crrond;
		else if(arrivee->t == crond) depart->t = ccrond;
	}else if(depart->t == rond){
		if(arrivee->t == rond) depart->t = rrond;
		else if(arrivee->t == carre) depart->t = crond;
		else if(arrivee->t == ccarre) depart->t = ccrond;
		else if(arrivee->t == rrond) depart->t = rrrond;
		else if(arrivee->t == crond) depart->t = crrond;
	}else if(depart->t == ccarre){
		if(arrivee->t == carre) depart->t = cccarre;
		else if(arrivee->t == rond) depart->t = ccrond;
	}else if(depart->t == rrond){
		if(arrivee->t == carre) depart->t = crrond;
		else if(arrivee->t == rond) depart->t = rrrond;
	}else if(depart->t == crond){
		if(arrivee->t == carre) depart->t = ccrond;
		else if(arrivee->t == rond) depart->t = crrond;
	}
	return 1;
}

int empilementUnique(piece *arrivee, type valeur){
	if(arrivee->t == cccarre || arrivee->t == rrrond || arrivee->t == ccrond || arrivee->t == crrond) return 0;
	if(valeur == rrrond || valeur == cccarre || valeur == ccrond || valeur == crrond || 
		((valeur == ccarre || valeur == rrond || valeur == crond) && (arrivee->t == ccarre || arrivee->t == rrond || arrivee->t == crond))) return 0;
	
	if(arrivee->t == carre){
		switch(valeur){
			case carre:
				arrivee->t = ccarre; break;
			case rond:
				arrivee->t = crond; break;
			case ccarre:
				arrivee->t = cccarre; break;
			case rrond :
				arrivee->t = crrond; break;
			case crond:
				arrivee->t = ccrond; break;
			default:
				break;
		}
	}else if(arrivee->t == rond){
		switch(valeur){
			case carre:
				arrivee->t = crond; break;
			case rond:
				arrivee->t = rrond; break;
			case ccarre:
				arrivee->t = ccrond; break;
			case rrond :
				arrivee->t = rrrond; break;
			case crond:
				arrivee->t = crrond; break;
			default:
				break;
		}
	}else if(arrivee->t == ccarre){
		switch(valeur){
			case carre:
				arrivee->t = cccarre; break;
			case rond:
				arrivee->t = ccrond; break;
			default:
				break;
		}
	}else if(arrivee->t == rrond){
		switch(valeur){
			case carre:
				arrivee->t = crrond; break;
			case rond:
				arrivee->t = rrrond; break;
			default:
				break;
		}
	}else if(arrivee->t == crond){
		switch(valeur){
			case carre:
				arrivee->t = ccrond; break;
			case rond:
				arrivee->t = crrond; break;
			default:
				break;
		}
	}
	return 1;
}
