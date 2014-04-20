#ifndef H_LOGIC
#define H_LOGIC
#include "liste.h"

int deplaValide(liste*, char, char, char, char, char);
liste* deplaCasesPossibles(liste*, type, char, char, char);
int deplaPossibleSurCase(liste*, char, char, char);
int deplaPiece(liste*, char, char, char, char);

listeC *deploCasesPossibles(liste*, type, char, char, char);
int deploPossibleSurCase(liste*, char, char, char);
int deploDoublePossibleSurCase(liste*, char, char, char);
void deploSurCase(liste*, char, char, char, type);
int deploValide(liste*, char, char, char, char, char, char, char, char);
int deploPieceDouble(liste*, char, char, char, char, char, char, char, char);
int deploPieceTriple(liste*, char, char, char, char, char, char, char, char, char, char);

#endif
