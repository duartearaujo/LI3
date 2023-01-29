#ifndef interactive
#define interactive

#include <ncurses.h>

#define linhas_por_pagina (LINES-2)

//int iniciaI(int *informacoespaginas, char (*paginas)[][LINES - 2]);

int novapagina(int *informacoespaginas, char (*paginas)[][linhas_por_pagina]);

void parsequeryI();

void main_I ();

#endif