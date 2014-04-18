#ifndef H_LOGIC
#define H_LOGIC
#include "liste.h"
#include "file.h"

int deplacementValide(liste*, char, char, char, char, char);
liste* deplacementCasesValides(liste*, type, char, char, char);
int deplacementPossible(liste*, char, char, char);
int deplacementPiece(liste*, char, char, char, char);

#endif
