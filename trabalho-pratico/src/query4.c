#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query4.h"
#include "../include/interactive.h"

int exec_Q4 (char *city, FILE *res, int modo, int *informacoespaginas, char *paginas[][linhas_por_pagina]) {
    double preco_medio [2] = {0};
    char line[256] = {0};
    foreach_tree_city (city, preco_medio);
    if (preco_medio [1]) {
        preco_medio[0] = preco_medio[0] / preco_medio [1];
        if (modo == 0)
            fprintf (res, "%.3f\n", preco_medio[0]);
        else{
            mvprintw (informacoespaginas[0], 0, "\t%.3f", preco_medio[0]);
            sprintf(line, "\t%.3f", preco_medio[0]);
            paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup(line);
            if (informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (informacoespaginas, paginas)) return 0;
        }
    }
    return 1;
}