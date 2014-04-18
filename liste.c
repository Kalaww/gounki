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

int deploiementAutoriser(liste *l, char couleur, char commencePar, char x, char y, char a, char b, char a1, char b1){
	piece *depart, *arrivee;
	int sens = (couleur == 'b')? 1 : -1;
	depart = getPieceByCoordListe(l, x, y);
	arrivee = getPieceByCoordListe(l, a, b);
	if(depart == NULL || (arrivee != NULL && (arrivee->couleur != depart->couleur || arrivee->t == cccarre || arrivee->t == rrrond || arrivee->t == crrond || arrivee->t == ccrond))){
		return 0;
	}

	if(depart->t == carre || depart->t == rond) return 0;

	if(((depart->t == ccarre || depart->t == cccarre)&& commencePar == '*') ||((depart->t == rrond ||depart->t == rrrond)&& commencePar == '+')) return 0;
	else if((b == '0' && couleur == 'n') || (b == '9' && couleur == 'b')){
		if(b1 == y+sens && (y == '8' || y == '1')) return 1;
		if(depart->t == ccarre && a == a1 && a1 == x && y == b-2*sens && deploiementPossibleSurCases(l, couleur, x, y, a, b)) return 1;
		if(depart->t == cccarre && a == a1 && a1 == x && (y == b-2*sens || y == b-3*sens) && deploiementPossibleSurCases(l, couleur, x, y, a, b)) return 1;
		if(depart->t == rrond && y == b-2*sens && b1 == b-sens && ((a == depart->x-2 && a1 == depart->x-1) || (a == depart->x+2 && a1 == depart->x+1))
			&& deploiementPossibleSurCases(l, couleur, x, y, a, b)) return 1;
		if(depart->t == rrrond && b == depart->y+3*sens && b1 == depart->y+sens && ((a == depart->x-3 && a1 == depart->x-1) || (a == depart->x+3 && a1 == depart->x+1))
			&& deploiementPossibleSurCases(l, couleur, x, y, a, b)) return 1;
		if(depart->t == crond){
			if(commencePar == '+'){
				return (((y == '7' || y == '2') && (a1 == depart->x && b1 == depart->y+sens) && b == b1+sens && (a == a1-1 || a == a1+1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b))
						|| ((y == '8' || y == '1') && ((a1 == depart->x && b1 == depart->y+sens) || ((a1 == depart->x-1 || a1 == depart->x+1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b)))));
			}else{
				return (b1 == depart->y+sens && (a1 == depart->x-1 || a1 == depart->x+1) && (a == a1 && b == b1+sens && deploiementPossibleSurCases(l, couleur, a1, b1, a, b)));
			}
		}
		/*if(depart->t == ccrond){
			if((y == '6' && couleur == 'b') || (y == '3' && couleur =='n'){
				if(commancePar == '+'){
					return x == a1 && y == b1+2*sens && (a == a1-1 || a == a1+1) && b == b1+sens && deploiementPossibleSurCases(l, couleur, x, y+sens, a1, b1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b);
				}else{
					return b1 == y+sens && (a1 == x-1 || a1 == x+1);
				}
			}
		}*/
	}
	if(depart->t == ccarre){
		if(commencePar == '*') return 0;
		return (((a == depart->x-2 && b == depart->y && a1 == depart->x-1 && b1 == depart->y) ||
			(a == depart->x+2 && b == depart->y && a1 == depart->x-1 && b1 == depart->y) ||
			(a == depart->x && b == depart->y+2*sens && a1 == depart->x && b1 == depart->y+sens))
			&& deploiementPossibleSurCases(l, couleur, x, y, a, b));
	}else if(depart->t == rrond){
		if(commencePar == '+') return 0;
		return (b == depart->y+2*sens && b1 == depart->y+sens && ((a == depart->x-2 && a1 == depart->x-1) || (a == depart->x+2 && a1 == depart->x+1))
			&& deploiementPossibleSurCases(l, couleur, x, y, a, b));
	}else if(depart->t == crond){
		if(commencePar == '+'){
			return (((a1 == depart->x-1 && b1 == depart->y) || (a1 == depart->x+1 && b1 == depart->y) || (a1 == depart->x && b1 == depart->y+sens))
					&& b == b1+sens && (a == a1-1 || a == a1+1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
		}else{
			return (b1 == depart->y+sens && (a1 == depart->x-1 || a1 == depart->x+1) && ((a == a1-1 && b == b1) || (a == a1+1 && b == b1) || (a == a1 && b == b1+sens)) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
		}
	}else if(depart->t == cccarre){
		if(commencePar == '*') return 0;
		return (((a == depart->x-3 && b == depart->y && a1 == depart->x-1 && b1 == depart->y) ||
			(a == depart->x+3 && b == depart->y && a1 == depart->x+1 && b1 == depart->y) ||
			(a == depart->x && b == depart->y+3*sens && a1 == depart->x && b1 == depart->y+sens))
			&& deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
	}else if(depart->t == rrrond){
		if(commencePar == '+') return 0;
		return (b == depart->y+3*sens && b1 == depart->y+sens && ((a == depart->x-3 && a1 == depart->x-1) || (a == depart->x+3 && a1 == depart->x+1))
			&& deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
	}else if(depart->t == ccrond){
		if(commencePar == '+'){
			return (((a1 == depart->x-2 && b1 == depart->y) || (a1 == depart->x+2 && b1 == depart->y) || (a1 == depart->x && b1 == depart->y+2*sens))
					&& b == b1+sens && (a == a1-1 || a == a1+1) && deploiementPossibleSurCases(l, couleur, x, y, a1, b1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
		}else{
			return (b1 == depart->y+sens && (a1 == depart->x-1 || a1 == depart->x+1) && ((a == a1-2 && b == b1) || (a == a1+2 && b == b1) || (a == a1 && b == b1+2*sens))
					&& deploiementPossibleSurCases(l, couleur, x, y, a1, b1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
		}
	}else if(depart->t == crrond){
		if(commencePar == '+'){
			return (((a1 == depart->x-1 && b1 == depart->y) || (a1 == depart->x+1 && b1 == depart->y) || (a1 == depart->x && b1 == depart->y+sens))
					&& b == b1+2*sens && (a == a1-2 || a == a1+2) && deploiementPossibleSurCases(l, couleur, x, y, a1, b1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
		}else{
			return (b1 == depart->y+2*sens && (a1 == depart->x-2 || a1 == depart->x+2) && ((a == a1-1 && b == b1) || (a == a1+1 && b == b1) || (a == a1 && b == b1+sens))
					&& deploiementPossibleSurCases(l, couleur, x, y, a1, b1) && deploiementPossibleSurCases(l, couleur, a1, b1, a, b));
		}
	}
	return 0;
}

int deploiementPossibleSurCases(liste *l, char couleur, char x, char y, char a, char b){
	piece *tmp;
	int sens, sens2;
	int i, j;
	if(x == a){
		sens = (y < b)? 1 : -1;
		for(i = y; (y < b && i < b) || (y > b && i > b); i+=sens){
			tmp = getPieceByCoordListe(l, x, i);
			if(tmp != NULL && (tmp->couleur != couleur|| tmp->t == cccarre || tmp->t == rrrond || tmp->t == crrond || tmp->t == ccrond)) return 0;
		}
	}else if(y == b){
		sens = (x < a)? 1 : -1;
		for(i = x; (x < a && i < a) || (x > a && i > a); i+=sens){
			tmp = getPieceByCoordListe(l, i, y);
			if(tmp != NULL && (tmp->couleur != couleur|| tmp->t == cccarre || tmp->t == rrrond || tmp->t == crrond || tmp->t == ccrond)) return 0;
		}
	}else{
		sens = (x < a)? 1 : -1;
		sens2 = (y < b)? 1 : -1;
		j = y;
		for(i = x; (x < a && i < a) || (x > a && i > a); i+=sens){
			tmp = getPieceByCoordListe(l, i, j);
			if(tmp != NULL && (tmp->couleur != couleur|| tmp->t == cccarre || tmp->t == rrrond || tmp->t == crrond || tmp->t == ccrond)) return 0;
			j+=sens2;
		}
	}
	printf("{{Deploiement possible sur cases}}\n");
	return 1;
}

int deploiementPiece(liste *l, char commencePar, char x, char y, char a, char b, char a1, char b1){
	piece *depart, *tmp;
	depart = getPieceByCoordListe(l, x, y);
	if(depart == NULL) return 0;
	if(depart->t == ccarre){
		tmp = getPieceByCoordListe(l, a1, b1);
		if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, carre));
		else{
			if(!empilementUnique(tmp, carre)) return 0;
		}
		tmp = getPieceByCoordListe(l, a, b);
		if(tmp ==NULL) addListe(l, initPiece(a, b, depart->couleur, carre));
		else{
			if(!empilementUnique(tmp, carre)) return 0;
		}
	}else if(depart->t == rrond){
		tmp = getPieceByCoordListe(l, a1, b1);
		if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, rond));
		else{
			if(!empilementUnique(tmp, rond)) return 0;
		}
		tmp = getPieceByCoordListe(l, a, b);
		if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, rond));
		else{
			if(!empilementUnique(tmp, rond)) return 0;
		}
	}else if(depart->t == crond){
		if(commencePar == '+'){
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
			tmp = getPieceByCoordListe(l, a, b);
			if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
		}else{
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
			tmp = getPieceByCoordListe(l, a, b);
			if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
		}
	}else if(depart->t == cccarre){
		tmp = getPieceByCoordListe(l, a1, b1);
		if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, carre));
		else{
			if(!empilementUnique(tmp, carre)) return 0;
		}
		if(a == a1)
			b1+= (b-b1)/2;
		else
			a1+= (a-a1)/2;
		tmp = getPieceByCoordListe(l, a1, b1);
		if(tmp == NULL) addListe(l, initPiece(a1, b1, depart->couleur, carre));
		else{
			if(!empilementUnique(tmp, carre)) return 0;
		}
		tmp = getPieceByCoordListe(l, a, b);
		if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, carre));
		else{
			if(!empilementUnique(tmp, carre)) return 0;
		}
	}else if(depart->t == rrrond){
		tmp = getPieceByCoordListe(l, a1, b1);
		if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, rond));
		else{
			if(!empilementUnique(tmp, rond)) return 0;
		}
		b1+= (b-b1)/2;
		a1+= (a-a1)/2;
		tmp = getPieceByCoordListe(l, a1, b1);
		if(tmp == NULL) addListe(l, initPiece(a1, b1, depart->couleur, rond));
		else{
			if(!empilementUnique(tmp, rond)) return 0;
		}
		tmp = getPieceByCoordListe(l, a, b);
		if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, rond));
		else{
			if(!empilementUnique(tmp, rond)) return 0;
		}
	}else if(depart->t == ccrond){
		if(commencePar == '+'){
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
			if(a == a1)
				b1-= b-b1;
			else
				a1-= a-a1;
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1, depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
			tmp = getPieceByCoordListe(l, a, b);
			if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
		}else{
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
			if(a == a1)
				b1+= b-b1;
			else
				a1+= a-a1;
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1, depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
			tmp = getPieceByCoordListe(l, a, b);
			if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
		}
	}else if(depart->t == crrond){
		if(commencePar == '+'){
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
			b1+= b-b1;
			a1+= a-a1;
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1, depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
			tmp = getPieceByCoordListe(l, a, b);
			if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
		}else{
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1,depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
			b1-= b-b1;
			a1-= a-a1;
			tmp = getPieceByCoordListe(l, a1, b1);
			if(tmp == NULL) addListe(l, initPiece(a1, b1, depart->couleur, rond));
			else{
				if(!empilementUnique(tmp, rond)) return 0;
			}
			tmp = getPieceByCoordListe(l, a, b);
			if(tmp == NULL) addListe(l, initPiece(a, b, depart->couleur, carre));
			else{
				if(!empilementUnique(tmp, carre)) return 0;
			}
		}
	}
	removeListe(l, depart);
	if(b > '8') return 2;
	if(b < '1') return 3;
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

