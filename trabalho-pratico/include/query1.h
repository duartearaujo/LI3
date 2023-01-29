#ifndef q1
#define q1

#include <stdio.h>
#include "../include/drivers.h"
#include "../include/users.h"

void printvaloresQ1 (DRIVERS *d, FILE *res, int modo, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void printvaloresQ1_2 (User *u, FILE *res, int modo, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void query1Exe(FILE *res, int modo, char* argv, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif