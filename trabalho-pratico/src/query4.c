#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/cidades.h"
#include "../include/query4.h"
#include "../include/interactive.h"

/* Função de execução da query 4. Chama a função foreach_tree_city que calcula o preço e número de viagens totais recorrendo a um array de double com duas posições.
    preco_medio[0]: preco total;
    preco_medio[1]: número de viagens;
*/
int exec_Q4 (char *city, FILE *res, int modo) {
    double preco_medio [2] = {0};
    char line[256] = {0};
    foreach_tree_city (city, preco_medio);
    if (preco_medio [1]) {
        preco_medio[0] = preco_medio[0] / preco_medio [1];
        if (modo == 0) /*Modo batch*/
            fprintf (res, "%.3f\n", preco_medio[0]);
        else{ /*Modo interativo*/
            sprintf(line, "\t%.3f", preco_medio[0]);
            if (!copia (strdup (line))) return 0;
        }
    }
    return 1;
}