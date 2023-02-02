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

struct PrintQ7 {
    FILE *res;
    int N;
    int modo;
};

gboolean printQ7_aux (gpointer key, gpointer value, gpointer user_data) {
    PrintQ7 *ficheiro = user_data;
    AvC* driver = value;
    char *id = getIdAvC (driver);
    char line[256] = {0};
    if (verifica_ativo(id)) {
        char *name = getNameAvC(driver);
        double avaliacao_media = getAvaliacaoMediaAvC (driver);
        if (ficheiro->modo == 0)
            fprintf (ficheiro->res,"%s;%s;%.3f\n",id,name,avaliacao_media);
        else{
            sprintf(line, "\t%s;%s;%.3f",id,name,avaliacao_media);
                if (!copia (strdup (line))) {
                    free (name);
                    free (id);
                    return FALSE;
                }
            }
        free (name);
        ficheiro->N--;
    }
    free (id);
    if (ficheiro->N)
        return FALSE;
    return TRUE;
}

int printQ7 (char *city,int N, FILE *res, int modo) {
    int r = 1;
    PrintQ7 *p = malloc(sizeof (PrintQ7));
    p->N = N;
    p->res = res;
    p->modo = modo;
    tree_foreach_city (city,p);
    if (p->N) r = 0; 
    free (p);
    return r;
}

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
        r = printQ7 (city,N, res, modo) ;
    }
    return r;
}