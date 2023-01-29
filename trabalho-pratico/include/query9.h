#ifndef query9
#define query9

#include "../include/interactive.h"

typedef struct Q9_aux Q9_aux;

int desempate_Q9(const void *p1, const void* p2);

void Q9Print(FILE *res, int t1, int t2, int modo, int *informacoespaginas, char (*paginas)[][linhas_por_pagina]);

void query9Exe(FILE *res, int modo, char **argv, int *informacoespaginas, char (*paginas)[][linhas_por_pagina]);

#endif