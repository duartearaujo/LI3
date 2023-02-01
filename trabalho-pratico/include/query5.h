#ifndef q5
#define q5

#include "../include/interactive.h"

double preco_medio_Q5(int limite_inferior,int limite_superior);

int printQ5 (FILE *res, int modo,double preco_medio, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

int query5Exe(FILE *res, int modo, char** argv, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif