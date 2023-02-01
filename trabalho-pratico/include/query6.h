#ifndef query6
#define query6

#include "../include/interactive.h"

double distancia_media(int limite_inferior, int limite_superior, char *city);

int printQ6(FILE *res, int modo,double distancia_media ,int *informacoespaginas, char *paginas[][linhas_por_pagina]);

int query6Exe(FILE *res, int modo, char **argumentos, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif 