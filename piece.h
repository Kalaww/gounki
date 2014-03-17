#ifndef H_PIECE
#define H_PIECE

typedef enum type{
	vide, carre, rond, ccarre, rrond, cccaree, rrrond, crond, ccrond, crrond
} type;

typedef struct piece{
	char x;
	char y;
	char couleur;
	type t;
} piece;

piece *initPiece(char,char,char,type);
void freePiece(piece*);
int equalsPiece(piece*, piece*);
char* strPiece(piece*);
int deplacementPiece(piece*, char, char);

#endif
