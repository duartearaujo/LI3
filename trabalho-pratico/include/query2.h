#ifndef query2
#define query2

#include "../include/interactive.h"

int desempate_Q2(const void *p1, const void* p2);

void printfArray(FILE *res,int N, int modo, int *informacoespaginas, char (*paginas)[][linhas_por_pagina]);

void query2Exe(FILE *res, int modo, char* argv, int *informacoespaginas, char (*paginas)[][linhas_por_pagina]);

#endif