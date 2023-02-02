#ifndef query8
#define query8

#include "../include/interactive.h"

int printArray_Q8(FILE *res, int modo,char gender_enunciado,int idade_conta_enunciado, int *informacoespaginas, char *paginas[][linhas_por_pagina]);


int query8Exe(FILE *res, int modo, char **argv, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif