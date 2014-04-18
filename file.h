#ifndef H_FILE
#define H_FILE
#include "liste.h"

typedef struct coord{
	char x;
	char y;
} coord;

typedef struct file{
	int size;
	int position;
	coord *coords[3];
} file;

coord *initCoord(char, char);
file *initFile(int);
void enfile(file*, coord*);
coord *defile(file*);

#endif
