#ifndef interactive
#define interactive

#include <ncurses.h>

typedef struct paginas_interativo paginas_interativo; 

int copia (char *line);

int novapagina();

int parsequeryI();

void main_I ();

#endif