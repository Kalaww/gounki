#include <stdlib.h>
#include <stdio.h>
#include "logic.h"

/* DEPLACEMENT */

/* Test si le déplacement est valide */
int deplaValide(liste *l, char couleur, char x, char y, char a, char b){
	piece *depart;
	listeC *cases;
	noeudC *tmp;
	
	depart = getPieceByCoordListe(l, x, y);
	if(depart == NULL){
		printf("Aucune pièce sur la case de départ\n");
		return 0;
	}
	
	cases = deplaCasesPossibles(l, depart->t, depart->couleur, depart->x, depart->y);
	tmp = cases->first;
	while(tmp != NULL){
		if(tmp->c->x == a && tmp->c->y == b) return 1;
		tmp = tmp->next;
	}
	
	return 0;
}

/* Récupère une liste de coordonées des déplacements possibles de la pièce en x,y */
listeC* deplaCasesPossibles(liste *l, type t, char couleur, char x, char y){
	listeC *cases = initListeC();
	int sens = (couleur == 'b')? 1 : -1;
	
	if(t == carre || t == crond || t == crrond){
		if(x > 'a' && deplaPossibleSurCase(l, couleur, x-1, y)) addListeC(cases, initCoord(x-1, y));
		if(x < 'h' && deplaPossibleSurCase(l, couleur, x+1, y)) addListeC(cases, initCoord(x+1, y));
		if(deplaPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoord(x, y+sens));
	}
	
	if(t == rond || t == crond || t == ccrond){
		if(x > 'a' && deplaPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoord(x-1, y+sens));
		if(x < 'h' && deplaPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoord(x+1, y+sens));
	}
	
	if(t == ccarre || t == ccrond){
		/*rebond*/
		if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y) == NULL) addListeC(cases, initCoord(x, y));
		/*normal*/
		}else if(x > 'b'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && deplaPossibleSurCase(l, couleur, x-2, y))
				addListeC(cases, initCoord(x-2, y));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL) addListeC(cases, initCoord(x, y));
		/*normal*/
		}else if(x < 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && deplaPossibleSurCase(l, couleur, x+2, y))
				addListeC(cases, initCoord(x+2, y));
		}
		
		/*normal*/
		if(getPieceByCoordListe(l, x, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+2+sens))
			addListeC(cases, initCoord(x, y+2*sens));
	}
	
	if(t == rrond || t == crrond){
		/*rebond*/
		if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+2*sens))
				addListeC(cases, initCoord(x, y+2*sens));
		/*normal*/
		}else if(x > 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x-2, y+2*sens))
				addListeC(cases, initCoord(x-2, y+2*sens));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+2*sens))
				addListeC(cases, initCoord(x, y+2*sens));
		/*normal*/
		}else if(x < 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x+2, y+2*sens))
				addListeC(cases, initCoord(x+2, y+2*sens));
		}
	}
	
	if(t == cccarre){
		/*rebond*/
		if(x == 'c'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && getPieceByCoordListe(l, x-2, y) == NULL)
				addListeC(cases, initCoord(x-1, y));
		/*rebond*/
		}else if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && deplaPossibleSurCase(l, couleur, x+1, y))
				addListeC(cases, initCoord(x+1, y));
		/*normal*/
		}else if(x > 'c'){
			if(getPieceByCoordListe(l, x-1, y) == NULL && getPieceByCoordListe(l, x-2, y) == NULL && deplaPossibleSurCase(l, couleur, x-3, y))
				addListeC(cases, initCoord(x-3, y));
		}
		
		/*rebond*/
		if(x == 'f'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && getPieceByCoordListe(l, x+2, y) == NULL)
				addListeC(cases, initCoord(x+1, y));
		/*rebond*/
		}else if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && deplaPossibleSurCase(l, couleur, x-1, y))
				addListeC(cases, initCoord(x-1, y));
		/*normal*/
		}else if(x < 'g'){
			if(getPieceByCoordListe(l, x+1, y) == NULL && getPieceByCoordListe(l, x+2, y) == NULL && deplaPossibleSurCase(l, couleur, x+3, y))
				addListeC(cases, initCoord(x+3, y));
		}
		
		/*normal*/
		if(getPieceByCoordListe(l, x, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x, y+3+sens)) addListeC(cases, initCoord(x, y+3*sens));
	}
	
	if(t == rrrond){
		/*rebond*/
		if(x == 'c'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x-2, y+sens) == NULL && deplaPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoord(x-1, y+3*sens));
		/*rebond*/
		}else if(x == 'b'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoord(x+1, y+3*sens));
		/*normal*/
		}else if(x > 'c'){
			if(getPieceByCoordListe(l, x-1, y+sens) == NULL && getPieceByCoordListe(l, x-2, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x-3, y+3*sens))
				addListeC(cases, initCoord(x-3, y+3*sens));
		}
		
		/*rebond*/
		if(x == 'f'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x+2, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoord(x+1, y+3*sens));
		/*rebond*/
		}else if(x == 'g'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoord(x-1, y+3*sens));
		/*normal*/
		}else if(x < 'f'){
			if(getPieceByCoordListe(l, x+1, y+sens) == NULL && getPieceByCoordListe(l, x+2, y+2*sens) == NULL && deplaPossibleSurCase(l, couleur, x+3, y+3*sens))
				addListeC(cases, initCoord(x+3, y+3*sens));
		}
	}
	
	return cases;
}

/* Test si un déplacement est possible sur la case x,y */
int deplaPossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || tmp->couleur != couleur || tmp->t == carre || tmp->t == rond || tmp->t == crond || tmp->t == ccarre || tmp->t == rrond;
}

/* Déplace la pièce x,y sur la case a,b */
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

/* Récupère une liste de coordonnées des déploiements possibles de la pièce en x, y */
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
		
		/*normal*/
		if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)) addListeC(cases, initCoords(x, x, y+sens, y+2*sens));
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
			if(x > 'b' && deploPossibleSurCase(l, couleur, x-2, y+sens)) addListeC(cases, initCoords(x-1, x-2, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x-1, x, y, y+sens));
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y)){
			if(x < 'g' && deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x+1, x, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x+2, y+sens)) addListeC(cases, initCoords(x+2, x, y, y+sens));
		}
		
		if(deploPossibleSurCase(l, couleur, x, y+sens)){
			if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x, x-1, y+sens, y+2*sens));
			if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x, x+1, y+sens, y+2*sens));
		}
		
		
		/*ROND*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+sens)){
			if(x > 'b' && deploPossibleSurCase(l, couleur, x-2, y+sens)) addListeC(cases, initCoords(x-1, x-2, y+sens, y+sens));
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x-1, x, y+sens, y+sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoords(x-1, x-1, y+sens, y+2*sens));
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+sens)){
			if(deploPossibleSurCase(l, couleur, x, y+sens)) addListeC(cases, initCoords(x+1, x, y+sens, y+sens));
			if(x < 'g' && deploPossibleSurCase(l, couleur, x+2, y+sens)) addListeC(cases, initCoords(x+1, x+2, y+sens, y+sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoords(x+1, x+1, y+sens, y+2*sens));
		}
	}
	
	if(t == cccarre){
		/*rebond*/
		if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x+1, y)) addListeC(cases, initCoordss(x-1, x, x+1, y, y, y));
		/*rebond*/
		}else if(x == 'c'){
			if(deploDoublePossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y)) addListeC(cases, initCoordss(x-1, x-2, x-1, y, y, y));
		/*normal*/
		}else if(x > 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y) && deploPossibleSurCase(l, couleur, x-3, y))
				addListeC(cases, initCoordss(x-1, x-2, x-3, y, y, y));
		}
		
		/*rebond*/
		if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x-1, y)) addListeC(cases, initCoordss(x+1, x, x-1, y, y, y));
		/*rebond*/
		}else if(x == 'f'){
			if(deploDoublePossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y)) addListeC(cases, initCoordss(x+1, x+2, x+1, y, y, y));
		/*normal*/
		}else if(x < 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y) && deploPossibleSurCase(l, couleur, x+3, y))
				addListeC(cases, initCoordss(x+1, x+2, x+3, y, y, y));
		}
		
		/*normal*/
		if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens) && deploPossibleSurCase(l, couleur, x, y+3*sens))
				addListeC(cases, initCoordss(x, x, x, y+sens, y+2*sens, y+3*sens));
	}
	
	if(t == rrrond){
		/*rebond*/
		if(x == 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens) && deploPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoordss(x-1, x-2, x-1, y+sens, y+2*sens, y+3*sens));
		/*rebond*/
		}else if(x == 'b'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens) && deploPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoordss(x-1, x, x+1, y+sens, y+2*sens, y+3*sens));
		/*normal*/
		}else if(x > 'c'){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens) && deploPossibleSurCase(l, couleur, x-3, y+3*sens))
				addListeC(cases, initCoordss(x-1, x-2, x-3, y+sens, y+2*sens, y+3*sens));
		}
		
		/*rebond*/
		if(x == 'f'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens) && deploPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoordss(x+1, x+2, x+1, y+sens, y+2*sens, y+3*sens));
		/*rebond*/
		}else if(x == 'g'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens) && deploPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoordss(x+1, x, x-1, y+sens, y+2*sens, y+3*sens));
		/*normal*/
		}else if(x < 'f'){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens) && deploPossibleSurCase(l, couleur, x+3, y+3*sens))
				addListeC(cases, initCoordss(x+1, x+2, x+3, y+sens, y+2*sens, y+3*sens));
		}
	}
	
	if(t == ccrond){
		/*CARRE*/
		if(x == 'b' && deploPossibleSurCase(l, couleur, x-1, y)){
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoordss(x-1, x, x-1, y, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoordss(x-1, x, x+1, y, y, y+sens));
		}else if(x > 'b' && deploPossibleSurCase(l, couleur, x-1, y) && deploPossibleSurCase(l, couleur, x-2, y)){
			if(x > 'c' && deploPossibleSurCase(l, couleur, x-3, y+sens)) addListeC(cases, initCoordss(x-1, x-2, x-3, y, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoordss(x-1, x-2, x-1, y, y, y+sens));
		}
		
		if(x == 'g' && deploPossibleSurCase(l, couleur, x+1, y)){
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoordss(x+1, x, x+1, y, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+sens)) addListeC(cases, initCoordss(x+1, x, x-1, y, y, y+sens));
		}else if(x < 'g' && deploPossibleSurCase(l, couleur, x+1, y) && deploPossibleSurCase(l, couleur, x+2, y)){
			if(x < 'f' && deploPossibleSurCase(l, couleur, x+3, y+sens)) addListeC(cases, initCoordss(x+1, x+2, x+3, y, y, y+sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+sens)) addListeC(cases, initCoordss(x+1, x+2, x+1, y, y, y+sens));
		}
		
		if(deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)){
			if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+3*sens)) addListeC(cases, initCoordss(x, x, x-1, y+sens, y+2*sens, y+3*sens));
			if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+3*sens)) addListeC(cases, initCoordss(x, x, x+1, y+sens, y+2*sens, y+3*sens));
		}
		
		/*ROND*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y+sens)){
			if(x == 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploDoublePossibleSurCase(l, couleur, x-1, y+sens)){
				addListeC(cases, initCoordss(x-1, x-2, x-1, y+sens, y+sens, y+sens));
			}else if(x > 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploPossibleSurCase(l, couleur, x-3, y+sens)){
				addListeC(cases, initCoordss(x-1, x-2, x-3, y+sens, y+sens, y+sens));
			}
			
			if(x == 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploDoublePossibleSurCase(l, couleur, x-1, y+sens)){
				addListeC(cases, initCoordss(x-1, x, x-1, y+sens, y+sens, y+sens));
			}else if(x < 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+sens)){
				addListeC(cases, initCoordss(x-1, x, x+1, y+sens, y+sens, y+sens));
			}
			
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens) && deploPossibleSurCase(l, couleur, x-1, y+3*sens))
				addListeC(cases, initCoordss(x-1, x-1, x-1, y+sens, y+2*sens, y+3*sens));
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y+sens)){
			if(x == 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploDoublePossibleSurCase(l, couleur, x+1, y+sens)){
				addListeC(cases, initCoordss(x+1, x, x+1, y+sens, y+sens, y+sens));
			}else if(x > 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+sens)){
				addListeC(cases, initCoordss(x+1, x, x-1, y+sens, y+sens, y+sens));
			}
			
			if(x == 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploDoublePossibleSurCase(l, couleur, x+1, y+sens)){
				addListeC(cases, initCoordss(x+1, x+2, x+1, y+sens, y+sens, y+sens));
			}else if(x < 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploPossibleSurCase(l, couleur, x+3, y+sens)){
				addListeC(cases, initCoordss(x+1, x+2, x+3, y+sens, y+sens, y+sens));
			}
			
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens) && deploPossibleSurCase(l, couleur, x+1, y+3*sens))
				addListeC(cases, initCoordss(x+1, x+1, x+1, y+sens, y+2*sens, y+3*sens));
		}
	}
	
	if(t == crrond){
		/*CARRE*/
		if(x > 'a' && deploPossibleSurCase(l, couleur, x-1, y)){
			if(x == 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+2*sens)){
				addListeC(cases, initCoordss(x-1, x-2, x-1, y, y+sens, y+2*sens));
			}else if (x > 'c' && deploPossibleSurCase(l, couleur, x-2, y+sens) && deploPossibleSurCase(l, couleur, x-3, y+2*sens)){
				addListeC(cases, initCoordss(x-1, x-2, x-3, y, y+sens, y+2*sens));
			}
			
			if(x == 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+2*sens)){
				addListeC(cases, initCoordss(x-1, x, x-1, y, y+sens, y+2*sens));
			}else if(x < 'h' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+2*sens)){
				addListeC(cases, initCoordss(x-1, x, x+1, y, y+sens, y+2*sens));
			}
		}
		
		if(x < 'h' && deploPossibleSurCase(l, couleur, x+1, y)){
			if(x == 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+2*sens)){
				addListeC(cases, initCoordss(x+1, x, x+1, y, y+sens, y+2*sens));
			}else if (x > 'a' && deploPossibleSurCase(l, couleur, x, y+sens) && deploPossibleSurCase(l, couleur, x-1, y+2*sens)){
				addListeC(cases, initCoordss(x+1, x, x-1, y, y+sens, y+2*sens));
			}
			
			if(x == 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploPossibleSurCase(l, couleur, x+1, y+2*sens)){
				addListeC(cases, initCoordss(x+1, x+2, x+1, y, y+sens, y+2*sens));
			}else if(x < 'f' && deploPossibleSurCase(l, couleur, x+2, y+sens) && deploPossibleSurCase(l, couleur, x+3, y+2*sens)){
				addListeC(cases, initCoordss(x+1, x+2, x+3, y, y+sens, y+2*sens));
			}
		}
		
		if(deploPossibleSurCase(l, couleur, x, y+sens)){
			if(x == 'b' && deploPossibleSurCase(l, couleur, x-1, y+2*sens) && deploPossibleSurCase(l, couleur, x, y+3*sens)){
				addListeC(cases, initCoordss(x, x-1, x, y+sens, y+2*sens, y+3*sens));
			}else if(x > 'b' && deploPossibleSurCase(l, couleur, x-1, y+2*sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens)){
				addListeC(cases, initCoordss(x, x-1, x-2, y+sens, y+2*sens, y+3*sens));
			}
			
			if(x == 'g' && deploPossibleSurCase(l, couleur, x+1, y+2*sens) && deploPossibleSurCase(l, couleur, x, y+3*sens)){
				addListeC(cases, initCoordss(x, x+1, x, y+sens, y+2*sens, y+3*sens));
			}else if(x <'g' && deploPossibleSurCase(l, couleur, x+1, y+2*sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens)){
				addListeC(cases, initCoordss(x, x+1, x+2, y+sens, y+2*sens, y+3*sens));
			}
		}
		
		/*ROND*/
		if(x == 'b' && deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)){
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoordss(x-1, x, x-1, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoordss(x-1, x, x+1, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x, y+3*sens)) addListeC(cases, initCoordss(x-1, x, x, y+sens, y+2*sens, y+3*sens));
		}else if(x > 'b' && deploPossibleSurCase(l, couleur, x-1, y+sens) && deploPossibleSurCase(l, couleur, x-2, y+2*sens)){
			if(x > 'c' && deploPossibleSurCase(l, couleur, x-3, y+2*sens)) addListeC(cases, initCoordss(x-1, x-2, x-3, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoordss(x-1, x-2, x-1, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x-2, y+3*sens)) addListeC(cases, initCoordss(x-1, x-2, x-2, y+sens, y+2*sens, y+3*sens));
		}
		
		if(x == 'g' && deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x, y+2*sens)){
			if(deploPossibleSurCase(l, couleur, x-1, y+2*sens)) addListeC(cases, initCoordss(x+1, x, x-1, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoordss(x+1, x, x+1, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x, y+3*sens)) addListeC(cases, initCoordss(x+1, x, x, y+sens, y+2*sens, y+3*sens));
		}else if(x < 'g' && deploPossibleSurCase(l, couleur, x+1, y+sens) && deploPossibleSurCase(l, couleur, x+2, y+2*sens)){
			if(deploPossibleSurCase(l, couleur, x+1, y+2*sens)) addListeC(cases, initCoordss(x+1, x+2, x+1, y+sens, y+2*sens, y+2*sens));
			if(x < 'f' && deploPossibleSurCase(l, couleur, x+3, y+2*sens)) addListeC(cases, initCoordss(x+1, x+2, x+3, y+sens, y+2*sens, y+2*sens));
			if(deploPossibleSurCase(l, couleur, x+2, y+3*sens)) addListeC(cases, initCoordss(x+1, x+2, x+2, y+sens, y+2*sens, y+3*sens));
		}
	}
	
	return cases;
}

/* Test si le déploiement est valide */
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
		if(tmp->c->x1 == a1 && tmp->c->y1 == b1 && tmp->c->x == a && tmp->c->y == b){
			if(y == tmp->c->y1 || x == tmp->c->x1) return commencePar == '+';
			else return commencePar == '*';
		}
		tmp = tmp->next;
	}
	
	return 0;
}

/* Déploie la pièce double x,y en a,b en passant par a1,b1 */
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

/* Déploie la pièce triple x,y en a,b en passant par a1,b1 et a2,b2 */
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

/* Déploie le type donnée sur la case x,y */
void deploSurCase(liste *l, char couleur, char x, char y, type t){
	piece *arrivee = getPieceByCoordListe(l, x, y);
	if(arrivee == NULL) addListe(l, initPiece(x, y, couleur, t));
	else empilementUnique(arrivee, t);
}

/* Test si un déploiement est possible sur la case x,y */
int deploPossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || (tmp->couleur == couleur && (tmp->t == carre || tmp->t == rond || tmp->t == ccarre || tmp->t == rrond || tmp->t == crond));
}

/* Test si un déploiement double est possible sur la case x,y */
int deploDoublePossibleSurCase(liste *l, char couleur, char x, char y){
	piece *tmp = getPieceByCoordListe(l, x, y);
	return tmp == NULL || (tmp->couleur == couleur && (tmp->t == carre || tmp->t == rond));
}
