#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <ncurses.h>
#include "../include/queries.h"
#include "../include/cidades.h"
#include "../include/drivers.h"
#include "../include/query7.h"
#include "../include/interactive.h"

gint organiza_arvore (gconstpointer a, gconstpointer b, gpointer c) {
    AvC const* ax = a;
    AvC const* bx = b;
    double am_a = getavaliacaomediaC (ax);
    double am_b = getavaliacaomediaC (bx);
    if (am_a == am_b) {
        char *id_a = getIdC(ax);
        char *id_b = getIdC(bx);
        int compare = strcmp (id_a, id_b);
        free (id_a);
        free (id_b);
        return (0 - compare);
    }
    if (am_a < am_b) return 1;
    return -1;
}

int exec_Q7 (char *city, int N,FILE *res, int modo) {
    int r = 1;
    if (N){
        ordena_arvore_Q7 (city);
        printQ7 (city,N, res, modo);
    }
    return r;
}