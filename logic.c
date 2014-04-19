#include <stdlib.h>
#include <stdio.h>
#include "logic.h"


int deplaValide(liste *l, char couleur, char x, char y, char a, char b){
	piece *depart;
	liste *cases;
	noeud *tmp;
	
	depart = getPieceByCoordListe(l, x, y);
	if(depart == NULL){
		printf("Aucune pièce sur la case de départ\n");
		return 0;
	}
	
	cases = deplaCasesPossibles(l, depart->t, depart->couleur, depart->x, depart->y);
	tmp = cases->first;
	while(tmp != NULL){
		if(tmp->p->x == a && tmp->p->y == b) return 1;
		printf("Case possible : %c,%c\n", tmp->p->x, tmp->p->y);
		tmp = tmp->next;
	}
	
	return 0;
}

liste* deplaCasesPossibles(liste *l, type t, char couleur, char x, char y){
	liste *cases = initListe();
	int sens = (couleur == 'b')? 1 : -1;
	
	if(t == carre || t == crond || t == crrond){
		if(deplaPossibleSurCase(l, couleur, x-1, y)) addListe(cases, initPiece(x-1, y, couleur, t));
		if(deplaPossibleSurCase(l, couleur, x+1, y)) addListe(cases, initPiece(x+1, y, couleur, t));
		if(deplaPossibleSurCase(l, couleur, x, y+sens)) addListe(cases, initPiece(x, y+sens, couleur, t));
	}
	
	if(t == rond || t == crond || t == ccrond){
		if(deplaPossibleSurCase(l, couleur, x-1, y+sens)) addListe(cases, initPiece(x-1, y+sens, couleur, t));
		if(deplaPossibleSurCase(l, couleur, x+1, y+sens)) addListe(cases, initPiece(x+1, y+sens, couleur, t));
	}
	
	if(t == ccarre || t == ccrond){
		/*rebond*/
		if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y) == NULL) addListe(cases, initPiece(x, y, couleur, t));
		/*normal*/
		}else if(x > 'b'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && deplaPossibleSurCase(l, couleur, x-2, y)) addListe(cases, initPiece(x-2, y, couleur, t));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL) addListe(cases, initPiece(x, y, couleur, t));
		/*normal*/
		}else if(x < 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && deplaPossibleSurCase(l, couleur, x+2, y)) addListe(cases, initPiece(x+2, y, couleur, t));
		}
		
		/*victoire*/
		if((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')){
			addListe(cases, initPiece(x, y+sens, couleur, t));
		/*normal*/
		}else if((couleur == 'b' && y < '8') || (couleur == 'n' && y > '1')){
			if(getPieceByCoordListe(l, x, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+2+sens)) addListe(cases, initPiece(x, y+2*sens, couleur, t));
		}
	}
	
	if(t == rrond || t == crrond){
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x >= 'b'){
			addListe(cases, initPiece(x-1, y+sens, couleur, t));
		/*rebond*/
		}else if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+2*sens)) addListe(cases, initPiece(x, y+2*sens, couleur, t));
		/*normal*/
		}else if(x > 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x-2, y+2*sens)) addListe(cases, initPiece(x-2, y+2*sens, couleur, t));
		}
		
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x <= 'g'){
			addListe(cases, initPiece(x+1, y+sens, couleur, t));
		/*rebond*/
		}else if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+2*sens)) addListe(cases, initPiece(x, y+2*sens, couleur, t));
		/*normal*/
		}else if(x < 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x+2, y+2*sens)) addListe(cases, initPiece(x+2, y+2*sens, couleur, t));
		}
	}
	
	if(t == cccarre){
		/*rebond*/
		if(x == 'c'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && getPieceByCoordListe(l, x-2, y) == NULL) addListe(cases, initPiece(x-1, y, couleur, t));
		/*rebond*/
		}else if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && deplaPossibleSurCase(l, couleur, x+1, y)) addListe(cases, initPiece(x+1, y, couleur,t));
		/*normal*/
		}else if(x > 'c'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && getPieceByCoordListe(l, x-2, y) == NULL && deplaPossibleSurCase(l, couleur, x-3, y)) addListe(cases, initPiece(x-3, y, couleur, t));
		}
		
		/*rebond*/
		if(x == 'f'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && getPieceByCoordListe(l, x+2, y) == NULL) addListe(cases, initPiece(x+1, y, couleur, t));
		/*rebond*/
		}else if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && deplaPossibleSurCase(l, couleur, x-1, y)) addListe(cases, initPiece(x-1, y, couleur, t));
		/*normal*/
		}else if(x < 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && getPieceByCoordListe(l, x+2, y) == NULL && deplaPossibleSurCase(l, couleur, x+3, y)) addListe(cases, initPiece(x+3, y, couleur, t));
		}
		
		/*victoire*/
		if((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')){
			addListe(cases, initPiece(x, y+sens, couleur, t));
		/*victoire*/
		}else if((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')){
			if(getPieceByCoordListe(l, x, y+sens) == NULL) addListe(cases, initPiece(x, y+2*sens, couleur, t));
		/*normal*/
		}else if((couleur == 'b' && y < '7') || (couleur == 'n' && y > '2')){
			if(getPieceByCoordListe(l, x, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+3+sens)) addListe(cases, initPiece(x, y+3*sens, couleur, t));
		}
	}
	
	if(t == rrrond){
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x > 'a'){
			addListe(cases, initPiece(x-1, y+sens, couleur, t));
		/*victoire + rebond*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x == 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL) addListe(cases, initPiece(x, y+2*sens, couleur, t));
		/*victoire*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x > 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL) addListe(cases, initPiece(x-2, y+2*sens, couleur, t));
		/*rebond*/
		}else if(x == 'c'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x-2, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x-1, y+3*sens)) addListe(cases, initPiece(x-1, y+3*sens, couleur, t));
		/*rebond*/
		}else if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x+1, y+3*sens)) addListe(cases, initPiece(x+1, y+3*sens, couleur, t));
		/*normal*/
		}else if(x > 'c'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x-2, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x-3, y+3*sens)) addListe(cases, initPiece(x-3, y+3*sens, couleur, t));
		}
		
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x < 'h'){
			addListe(cases, initPiece(x+1, y+sens, couleur, t));
		/*victoire + rebond*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x == 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL) addListe(cases, initPiece(x, y+2*sens, couleur, t));
		/*victoire*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x < 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL) addListe(cases, initPiece(x+2, y+2*sens, couleur, t));
		/*rebond*/
		}else if(x == 'f'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x+2, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x+1, y+3*sens)) addListe(cases, initPiece(x+1, y+3*sens, couleur, t));
		/*rebond*/
		}else if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x-1, y+3*sens)) addListe(cases, initPiece(x-1, y+3*sens, couleur, t));
		/*normal*/
		}else if(x < 'f'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x+2, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x+3, y+3*sens)) addListe(cases, initPiece(x+3, y+3*sens, couleur, t));
		}
	}
	
	return cases;
}

int deplaPossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || tmp->couleur != couleur || tmp->t == carre || tmp->t == rond || tmp->t == crond || tmp->t == ccarre || tmp->t == rrond;
}

int deplaPiece(liste *l, char x, char y, char a, char b){
	piece *depart, *arrivee, *tmp;
	depart = getPieceByCoordListe(l, x, y);
	if(depart == NULL) return 0;
	tmp = initPiece(depart->x, depart->y, depart->couleur, depart->t);
	removeListe(l, depart);
	arrivee = getPieceByCoordListe(l, a, b);
	if(arrivee != NULL){
		if(arrivee->couleur != tmp->couleur){
			removeListe(l, arrivee);
		}else{
			if(empilementPiece(tmp, arrivee))
				removeListe(l, arrivee);
			else
				return 0;
		}
	}
	tmp->x = a;
	tmp->y = b;
	addListe(l, tmp);
	if(b == '0') return 3;
	if(b == '9') return 2;
	return 1;
}


/* DEPLOIEMENT */

liste *deploCasesPossibles(liste *l, type t, char couleur, char x, char y){
	liste *cases = initListe();
	int sens = (couleur == 'b')? 1 : -1;
	
	if(t == carre || t == rond) return 0;
	
	if(t == ccarre){
		/*rebond*/
		if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y)) addListe(cases, initPiece(chars(x-1, x, 'a'), chars(y, y, '0'), couleur, t));
		/*normal*/
		}else if(x > 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y)) addListe(cases, initPiece(chars(x-1, x-2, 'a'), chars(y, y, '0'), couleur, t));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y)) addListe(cases, initPiece(chars(x+1, x, 'a'), chars(y, y, '0'), couleur, t));
		/*normal*/
		}else if(x < 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y)) addListe(cases, initPiece(chars(x+1, x+2, 'a'), chars(y, y, '0'), couleur, t));
		}
		
		/*victoire*/
		if((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')){
			addListe(cases, initPiece(chars(x, x, 'a'), chars(y+sens, y+sens, '0'), couleur, t));
		/*normal*/
		}else if((couleur == 'b' && y < '8') || (couleur == 'n' && y > '1')){
			if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListe(cases, initPiece(chars(x, x, 'a'), chars(y+sens, y+2*sens, '0'), couleur, t));
		}
	}
	
	if(t == rrond){
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x >= 'b'){
			addListe(cases, initPiece(chars(x-1, x-1, 'a'), chars(y+sens, y+sens, '0'), couleur, t));
		/*rebond*/
		}else if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListe(cases, initPiece(chars(x-1, x, 'a'), chars(y+sens, y+2*sens, '0'), couleur, t));
		/*normal*/
		}else if(x > 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens)) addListe(cases, initPiece(chars(x-1, x-2, 'a'), chars(y+sens, y+2*sens, '0'), couleur, t));
		}
		
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x <= 'g'){
			addListe(cases, initPiece(chars(x+1, x+1, 'a'), chars(y+sens, y+sens, '0'), couleur, t));
		/*rebond*/
		}else if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListe(cases, initPiece(chars(x+1, x, 'a'), chars(y+sens, y+2*sens, '0'), couleur, t));
		/*normal*/
		}else if(x > 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens)) addListe(cases, initPiece(chars(x+1, x+2, 'a'), chars(y+sens, y+2*sens, '0'), couleur, t));
		}
	}
}

int deploPossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || (tmp->couleur == couleur && (tmp->t == carre || tmp->t == rond || tmp->t == ccarre || tmp->t == rrond || tmp->t == crond));
}

char chars(char a, char b, char ref){
	char c;
	c = a - ref;
	c += (b-ref)/10;
	return c;
}
