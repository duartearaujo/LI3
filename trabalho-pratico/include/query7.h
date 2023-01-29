#ifndef q7
#define q7

#include <ncurses.h>
#include "../include/interactive.h"

gint organiza_arvore (gconstpointer a, gconstpointer b, gpointer c);

void exec_Q7 (char *city,int N ,FILE *res, int modo, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif