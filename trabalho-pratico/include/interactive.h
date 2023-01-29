#ifndef interactive
#define interactive

#include <ncurses.h>

#define linhas_por_pagina (LINES-2)

int novapagina(int *informacoespaginas, char *paginas[][linhas_por_pagina]);

void parsequeryI(int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void main_I ();

#endif