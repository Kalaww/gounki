#include <stdlib.h>
#include "file.h"

coord *initCoord(char x, char y){
	coord *c = malloc(sizeof(coord));
	c->x = x;
	c->y = y;
	return c;
}

file *initFile(int size){
	file *p = malloc(sizeof(file));
	p->size = size;
	p->position = 0;
	return p;
}

void enfile(file *p, coord *c){
	p->coords[p->position] = c;
	p->position++;
}

coord *defile(file *p){
	p->position--;
	if(p->position < 0) return NULL;
	else return p->coords[p->position];
}

