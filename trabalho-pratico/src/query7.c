#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query7.h"


void avaliacao_media_city (gpointer key, DRIVERS *value, char *city) {
    AvC *avaliacao_cidade = lookup_AvC (value, city);
    if (avaliacao_cidade) {
        calcula_avaliacao_media_AvC (avaliacao_cidade);
        adicionaArrayQ7 (avaliacao_cidade);
    }
}

int comparaAvC (const void *p1, const void* p2) {
    int r = 1;
    AvC *item1 = *((AvC**) p1);
    AvC *item2 = *((AvC**) p2);
    double avaliacao1 = getAvaliacaoMediaAvC (item1);
    double avaliacao2 = getAvaliacaoMediaAvC (item2);
    if (avaliacao2 > avaliacao1) r = -1;
    else if (avaliacao1 == avaliacao2) {
        char *id1 = getIdAvC (item1);
        char *id2 = getIdAvC (item2);
        r = strcmp(id1, id2);
        free (id1);
        free (id2);
    }
    return r;
}

void printQ7 (FILE *fp,int N) {
    int pos = getPosQ7 ();
    int print = 0;
    for (int i = pos -1; print < N && i>-1; i--) {
        AvC *pos = getarrayQ7pos (i);
        if (isactive (pos)) {
        char *id = getIdAvC (pos);
        char *name = getNameAvC (pos);
        double avaliacao_media = getAvaliacaoMediaAvC (pos);
        fprintf (fp, "%s;%s;%.3f\n",id, name,avaliacao_media);
        free (id);
        free (name);
        print++;
        }
        free_avaliacao_por_cidade (pos);
    }
}