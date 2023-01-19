#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query4.h"

void exec_Q4 (char *city, FILE *res) {
    double preco_medio [2] = {0};
    foreach_tree_city (city, preco_medio);
    if (preco_medio [1]) 
        preco_medio[0] = preco_medio[0] / preco_medio [1];
    fprintf (res, "%.3f\n", preco_medio[0]);
}