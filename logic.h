#ifndef H_LOGIC
#define H_LOGIC
#include "liste.h"
#include "file.h"

int deplaValide(liste*, char, char, char, char, char);
liste* deplaCasesPossibles(liste*, type, char, char, char);
int deplaPossibleSurCase(liste*, char, char, char);
int deplaPiece(liste*, char, char, char, char);

liste *deploCasesPossibles(liste*, type, char, char, char);
int deploPossibleSurCase(liste*, char, char, char);
int deploDoublePossibleSurCase(liste*, char, char, char);

char chars(char, char, char);

#endif
