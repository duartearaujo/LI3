#ifndef query3
#define query3

#include "../include/interactive.h"

int desempate_Q3(const void *p1, const void* p2);

void Q3Print(FILE *res, int N, int modo, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void query3Exe(FILE *res,int modo,char* argv, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif