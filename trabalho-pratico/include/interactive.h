#ifndef interactive
#define interactive

#include <ncurses.h>

#define linhas_por_pagina (LINES-2)

void copia (int *informacoespaginas, char *paginas[][linhas_por_pagina], char line[]);

int novapagina(int *informacoespaginas, char *paginas[][linhas_por_pagina]);

int parsequeryI(int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void main_I ();

#endif