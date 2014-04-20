#include <stdlib.h>
#include <stdio.h>
#include "logic.h"

/* DEPLECEMENT */

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
		if(x > 'a' && deplaPossibleSurCase(l, couleur, x-1, y)) addListe(cases, initPiece(x-1, y, couleur, t));
		if(x < 'h' && deplaPossibleSurCase(l, couleur, x+1, y)) addListe(cases, initPiece(x+1, y, couleur, t));
		if(deplaPossibleSurCase(l, couleur, x, y+sens)) addListe(cases, initPiece(x, y+sens, couleur, t));
	}
	
	if(t == rond || t == crond || t == ccrond){
		if(x > 'a' && deplaPossibleSurCase(l, couleur, x-1, y+sens)) addListe(cases, initPiece(x-1, y+sens, couleur, t));
		if(x < 'h' && deplaPossibleSurCase(l, couleur, x+1, y+sens)) addListe(cases, initPiece(x+1, y+sens, couleur, t));
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

listeC *deploCasesPossibles(liste *l, type t, char couleur, char x, char y){
	listeC *cases = initListeC();
	int sens = (couleur == 'b')? 1 : -1;
	
	if(t == carre || t == rond) return cases;
	
	if(t == ccarre){
		/*rebond*/
		if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y)) addListeC(cases, initCoords(x-1, x, y, y));
		/*normal*/
		}else if(x > 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y)) addListeC(cases, initCoords(x-1, x-2, y, y));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y)) addListeC(cases, initCoords(x+1, x, y, y));
		/*normal*/
		}else if(x < 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y)) addListeC(cases, initCoords(x+1, x+2, y, y));
		}
		
		/*victoire*/
		if((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')){
			addListeC(cases, initCoords(x, x, y+sens, y+sens));
		/*normal*/
		}else if((couleur == 'b' && y < '8') || (couleur == 'n' && y > '1')){
			if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListeC(cases, initCoords(x, x, y+sens, y+2*sens));
		}
	}
	
	if(t == rrond){
		/*rebond*/
		if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListeC(cases, initCoords(x-1, x, y+sens, y+2*sens));
		/*normal*/
		}else if(x > 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens)) addListeC(cases, initCoords(x-1, x-2, y+sens, y+2*sens));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListeC(cases, initCoords(x+1, x, y+sens, y+2*sens));
		/*normal*/
		}else if(x < 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens)) addListeC(cases, initCoords(x+1, x+2, y+sens, y+2*sens));
		}
	}
	
	if(t == crond){
		/*CARRE*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y)){
			if(deploPossibleSurCase(l, couleur, x-2, y+sens)) addListeC(cases, initCoords(x-1, x-2, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x-1, x, y, y+sens));
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y)){
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x+1, x, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x+2, y+sens)) addListeC(cases, initCoords(x+2, x, y, y+sens));
		}
		
		if((couleur == 'b' && y == '8') || (couleur == '1' && y == '1')){
			if(x > 'a') addListeC(cases, initCoords(x, x-1, y+sens, y+sens));
			if(x < 'h') addListeC(cases, initCoords(x, x+1, y+sens, y+sens));
		}else if(((couleur == 'b' && y < '8') || (couleur == 'n' && y > '1')) && deploPossibleSurCase(l, couleur, x, y+sens)){
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x, x-1, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x, x+1, y+sens, y+2*sens));
		}
		
		
		/*ROND*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+sens)){
			if(deploPossibleSurCase(l, couleur, x-2, y+sens)) addListeC(cases, initCoords(x-1, x-2, y+sens, y+sens));
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x-1, x, y+sens, y+sens));
			
			if((couleur == 'b' && y == '8') || (couleur == '1' && y == '1')){
				addListeC(cases, initCoords(x-1, x-1, y+sens, y+sens));
			}else{
				if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x-1, x-1, y+sens, y+2*sens));
			}
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+sens)){
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x+1, x, y+sens, y+sens));
			if(deploPossibleSurCase(l, couleur, x+2, y+sens)) addListeC(cases, initCoords(x+1, x+2, y+sens, y+sens));
			
			if((couleur == 'b' && y == '8') || (couleur == '1' && y == '1')){
				addListeC(cases, initCoords(x+1, x+1, y+sens, y+sens));
			}else{
				if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x+1, x+1, y+sens, y+2*sens));
			}
		}
	}
	
	if(t == cccarre){
		/*rebond*/
		if(x == 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x+1, y)) addListeC(cases, initCoords(x-1, x+1, y, y));
		/*rebond*/
		}else if(x == 'b'){
			if(deploDoublePossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y)) addListeC(cases, initCoords(x-1, x-1, y, y));
		/*normal*/
		}else if(x > 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y) && deploPossibleSurCase(l, couleur, x-3, y))
				addListeC(cases, initCoords(x-1, x-3, y, y));
		}
		
		/*rebond*/
		if(x == 'f'){
			if(deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x-1, y)) addListeC(cases, initCoords(x+1, x-1, y, y));
		/*rebond*/
		}else if(x == 'g'){
			if(deploDoublePossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y)) addListeC(cases, initCoords(x+1, x+1, y, y));
		/*normal*/
		}else if(x < 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y) && deploPossibleSurCase(l, couleur, x+3, y))
				addListeC(cases, initCoords(x+1, x+3, y, y));
		}
		
		/*victoire*/
		if((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')){
			addListeC(cases, initCoords(x, x, y+sens, y+sens));
		/*victoire*/
		}else if((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')){
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x, x, y+sens, y+2*sens));
		/*normal*/
		}else if((couleur == 'b' && y < '7') || (couleur == 'n' && y > '2')){
			if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens) && deploPossibleSurCase(l, couleur, x, y+3*sens))
				addListeC(cases, initCoords(x, x, y+sens, y+3*sens));
		}
	}
	
	if(t == rrrond){
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x > 'a'){
			addListeC(cases, initCoords(x-1, x-1, y+sens, y+sens));
		/*victoire + rebond*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoords(x-1, x, y+sens, y+2*sens));
		/*victoire*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x > 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoords(x-1, x-2, y+sens, y+2*sens));
		/*rebond*/
		}else if(x == 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens) && deploPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoords(x-1, x-1, y+sens, y+3*sens));
		/*rebond*/
		}else if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens) && deploPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoords(x-1, x+1, y+sens, y+3*sens));
		/*normal*/
		}else if(x > 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens) && deploPossibleSurCase(l, couleur, x-3, y+3*sens))
				addListeC(cases, initCoords(x-1, x-3, y+sens, y+3*sens));
		}
		
		/*victoire*/
		if(((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')) && x < 'h'){
			addListeC(cases, initCoords(x+1, x+1, y+sens, y+sens));
		/*victoire + rebond*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoords(x+1, x, y+sens, y+2*sens));
		/*victoire*/
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && x < 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoords(x+1, x+2, y+sens, y+2*sens));
		/*rebond*/
		}else if(x == 'f'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens) && deploPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoords(x+1, x+1, y+sens, y+3*sens));
		/*rebond*/
		}else if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens) && deploPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoords(x+1, x-1, y+sens, y+3*sens));
		/*normal*/
		}else if(x < 'f'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens) && deploPossibleSurCase(l, couleur, x+3, y+3*sens))
				addListeC(cases, initCoords(x+1, x+3, y+sens, y+3*sens));
		}
	}
	
	if(t == ccrond){
		/*CARRE*/
		if(x == 'b' && deploPossibleSurCase(l, couleur, x-1, y)){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoords(x-1, x-1, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoords(x-1, x+1, y, y+sens));
		}else if(x > 'b' && deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y)){
			if(x > 'c' && deploPossibleSurCase(l, couleur, x-3, y+sens)) addListeC(cases, initCoords(x-1, x-3, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoords(x-1, x-1, y, y+sens));
		}
		
		if(x == 'g' && deploPossibleSurCase(l, couleur, x+1, y)){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoords(x+1, x+1, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoords(x+1, x-1, y, y+sens));
		}else if(x < 'g' && deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y)){
			if(x < 'f' && deploPossibleSurCase(l, couleur, x+3, y+sens)) addListeC(cases, initCoords(x+1, x+3, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoords(x+1, x+1, y, y+sens));
		}
		
		if((couleur == 'b' && y == '8') || (couleur == 'n' && y == '1')){
			if(x > 'a') addListeC(cases, initCoords(x, x-1, y+sens, y+sens));
			if(x < 'h') addListeC(cases, initCoords(x, x+1, y+sens, y+sens));
		}else if(((couleur == 'b' && y == '7') || (couleur == 'n' && y == '2')) && deploPossibleSurCase(l, couleur, x, y+sens)){
			if(x > 'a') addListeC(cases, initCoords(x, x-1, y+sens, y+2*sens));
			if(x < 'h') addListeC(cases, initCoords(x, x+1, y+sens, y+2*sens));
		}else if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)){
			if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+3*sens)) addListeC(cases, initCoords(x, x-1, y+sens, y+3*sens));
			if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+3*sens)) addListeC(cases, initCoords(x, x+1, y+sens, y+3*sens));
		}
		
		/*ROND*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+sens)){
			if(x == 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploDoublePossibleSurCase(l, couleur, x-1, y+sens)){
				addListeC(cases, initCoords(x-1, x-1, y+sens, y+sens));
			}else if(x > 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploPossibleSurCase(l, couleur, x-3, y+sens)){
				addListeC(cases, initCoords(x-1, x-3, y+sens, y+sens));
			}
			
			if(x == 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploDoublePossibleSurCase(l, couleur, x-1, y+sens)){
				addListeC(cases, initCoords(x-1, x-1, y+sens, y+sens));
			}else if(x < 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+sens)){
				addListeC(cases, initCoords(x-1, x+1, y+sens, y+sens));
			}
			
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens) && deploPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoords(x-1, x-1, y+sens, y+3*sens));
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+sens)){
			if(x == 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploDoublePossibleSurCase(l, couleur, x+1, y+sens)){
				addListeC(cases, initCoords(x+1, x+1, y+sens, y+sens));
			}else if(x > 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+sens)){
				addListeC(cases, initCoords(x+1, x-1, y+sens, y+sens));
			}
			
			if(x == 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploDoublePossibleSurCase(l, couleur, x+1, y+sens)){
				addListeC(cases, initCoords(x+1, x+1, y+sens, y+sens));
			}else if(x < 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploPossibleSurCase(l, couleur, x+3, y+sens)){
				addListeC(cases, initCoords(x+1, x+3, y+sens, y+sens));
			}
			
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens) && deploPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoords(x+1, x+1, y+sens, y+3*sens));
		}
	}
	
	if(t == crrond){
		/*CARRE*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y)){
			if(x == 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+2*sens)){
				addListeC(cases, initCoords(x-1, x-1, y, y+2*sens));
			}else if (x > 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploPossibleSurCase(l, couleur, x-3, y+2*sens)){
				addListeC(cases, initCoords(x-1, x-3, y, y+2*sens));
			}
			
			if(x == 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+2*sens)){
				addListeC(cases, initCoords(x-1, x-1, y, y+2*sens));
			}else if(x < 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+2*sens)){
				addListeC(cases, initCoords(x-1, x+1, y, y+2*sens));
			}
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y)){
			if(x == 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+2*sens)){
				addListeC(cases, initCoords(x+1, x+1, y, y+2*sens));
			}else if (x > 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+2*sens)){
				addListeC(cases, initCoords(x+1, x-1, y, y+2*sens));
			}
			
			if(x == 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+2*sens)){
				addListeC(cases, initCoords(x+1, x+1, y, y+2*sens));
			}else if(x < 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploPossibleSurCase(l, couleur, x+3, y+2*sens)){
				addListeC(cases, initCoords(x+1, x+3, y, y+2*sens));
			}
		}
		
		if(deploPossibleSurCase(l, couleur, x, y+sens)){
			if(x == 'b' && deploPossibleSurCase(l, couleur, x-1, y+2*sens) && deploPossibleSurCase(l, couleur, x, y+3*sens)){
				addListeC(cases, initCoords(x, x, y+sens, y+3*sens));
			}else if(x > 'b' && deploPossibleSurCase(l, couleur, x-1, y+2*sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens)){
				addListeC(cases, initCoords(x, x-2, y+sens, y+3*sens));
			}
			
			if(x == 'g' && deploPossibleSurCase(l, couleur, x+1, y+2*sens) && deploPossibleSurCase(l, couleur, x, y+3*sens)){
				addListeC(cases, initCoords(x, x, y+sens, y+3*sens));
			}else if(x <'g' && deploPossibleSurCase(l, couleur, x+1, y+2*sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens)){
				addListeC(cases, initCoords(x, x+2, y+sens, y+3*sens));
			}
		}
		
		/*ROND*/
		if(x == 'b' && deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)){
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x-1, x-1, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x-1, x+1, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x, y+3*sens)) addListeC(cases, initCoords(x-1, x, y+sens, y+3*sens));
		}else if(x > 'b' && deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens)){
			if(x > 'c' && deploPossibleSurCase(l, couleur, x-3, y+2*sens)) addListeC(cases, initCoords(x-1, x-3, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x-1, x-1, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x-2, y+3*sens)) addListeC(cases, initCoords(x-1, x-2, y+sens, y+3*sens));
		}
		
		if(x == 'g' && deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)){
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x+1, x-1, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x+1, x+1, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x, y+3*sens)) addListeC(cases, initCoords(x+1, x, y+sens, y+3*sens));
		}else if(x < 'g' && deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens)){
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x+1, x+1, y+sens, y+2*sens));
			if(x < 'f' && deploPossibleSurCase(l, couleur, x+3, y+2*sens)) addListeC(cases, initCoords(x+1, x+3, y+sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+2, y+3*sens)) addListeC(cases, initCoords(x+1, x+2, y+sens, y+3*sens));
		}
	}
	
	return cases;
}

int deploValide(liste *l, char couleur, char commencePar, char x, char y, char a, char b, char a1, char b1){
	piece *depart;
	listeC *cases;
	noeudC *tmp;
	
	depart = getPieceByCoordListe(l, x, y);
	if(depart == NULL){
		printf("Aucune pièce sur la case de départ\n");
		return 0;
	}
	
	cases = deploCasesPossibles(l, depart->t, depart->couleur, depart->x, depart->y);
	tmp = cases->first;
	while(tmp != NULL){
		printf("Case possible : [%c,%c][%c,%c]\n", tmp->c->x1, tmp->c->y1, tmp->c->x, tmp->c->y);
		if(tmp->c->x1 == a1 && tmp->c->y1 == b1 && tmp->c->x == a && tmp->c->y == b){
			if(y == tmp->c->y1 || x == tmp->c->x1) return commencePar == '+';
			else return commencePar == '*';
		}
		tmp = tmp->next;
	}
	
	return 0;
}

int deploPieceDouble(liste *l, char couleur, char commencePar, char x, char y, char a, char b, char a1, char b1){
	piece *depart;
	char t;
	depart = getPieceByCoordListe(l, x, y);
	
	if(depart == NULL) return 0;
	t = depart->t;
	removeListe(l, depart);
	if(t == ccarre){
		deploSurCase(l, couleur, a1, b1, carre);
		deploSurCase(l, couleur, a, b, carre);
	}else if(t == rrond){
		deploSurCase(l, couleur, a1, b1, rond);
		deploSurCase(l, couleur, a, b, carre);
	}else if(t == crond){
		deploSurCase(l, couleur, a1, b1, ((commencePar == '+')? carre : rond));
		deploSurCase(l, couleur, a, b, ((commencePar == '+')? rond : carre));
	}
	
	if(b > '8') return 2;
	if(b < '1') return 3;
	return 1;
}

int deploPieceTriple(liste *l, char couleur, char commencePar, char x, char y, char a, char b, char a1, char b1, char a2, char b2){
	piece *depart;
	char t;
	depart = getPieceByCoordListe(l, x, y);
	
	if(depart == NULL) return 0;
	t = depart->t;
	removeListe(l, depart);
	if(t  == cccarre){
		deploSurCase(l, couleur, a1, b1, carre);
		deploSurCase(l, couleur, a2, b2, carre);
		deploSurCase(l, couleur, a, b, carre);
	}else if(t == rrrond){
		deploSurCase(l, couleur, a1, b1, rond);
		deploSurCase(l, couleur, a2, b2, rond);
		deploSurCase(l, couleur, a, b, rond);
	}else if(t == ccrond){
		if(commencePar == '+'){
			deploSurCase(l, couleur, a1, b1, carre);
			deploSurCase(l, couleur, a2, b2, carre);
			deploSurCase(l, couleur, a, b, rond);
		}else{
			deploSurCase(l, couleur, a1, b1, rond);
			deploSurCase(l, couleur, a2, b2, carre);
			deploSurCase(l, couleur, a, b, carre);
		}
	}else if(t == crrond){
		if(commencePar == '+'){
			deploSurCase(l, couleur, a1, b1, carre);
			deploSurCase(l, couleur, a2, b2, rond);
			deploSurCase(l, couleur, a, b, rond);
		}else{
			deploSurCase(l, couleur, a1, b1, rond);
			deploSurCase(l, couleur, a2, b2, rond);
			deploSurCase(l, couleur, a, b, carre);
		}
	}
	
	if(b > '8') return 2;
	if(b < '1') return 3;
	return 1;
}

void deploSurCase(liste *l, char couleur, char x, char y, type t){
	piece *arrivee = getPieceByCoordListe(l, x, y);
	if(arrivee == NULL) addListe(l, initPiece(x, y, couleur, t));
	else empilementUnique(arrivee, t);
}

int deploPossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || (tmp->couleur == couleur && (tmp->t == carre || tmp->t == rond || tmp->t == ccarre || tmp->t == rrond || tmp->t == crond));
}

int deploDoublePossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || (tmp->couleur == couleur && (tmp->t == carre || tmp->t == rond));
}
