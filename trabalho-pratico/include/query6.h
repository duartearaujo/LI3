#ifndef query6
#define query6

#include "../include/interactive.h"

typedef struct Q6 Q6;

Q6* inicializaQ6 (char *city, char *data1, char *data2);

void distancia_media(gpointer key, RIDES *ride, Q6 *q);

int printQ6(Q6 *q, FILE *res, int modo, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void freeQ6(Q6 *q);

int query6Exe(FILE *res, int modo, char **argv, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif 