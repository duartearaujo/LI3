#ifndef queries
#define queries

#include <ncurses.h>
#include "../include/interactive.h"
#include "../include/parse.h"

int querieIdentifier(char **argv, int n_querie, int i, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

int identifyArgument(char *str);

int tempo_De_Vida(char *str);

int calculaIdade(char *str);

int compareDates(char *str, char *string);

#endif