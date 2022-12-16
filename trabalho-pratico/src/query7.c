#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query7.h"

struct Q7 { 
    AvC **array_avaliacoes;
    int pos;
};

static Q7 *array;

void inicializaQ7 () {
    array = malloc (sizeof (Q7));
    array->array_avaliacoes = NULL;
    array->pos = 0;
}

void avaliacao_media_city (gpointer key, DRIVERS *value, char *city) {
    AvC *avaliacao_cidade = lookup_AvC (value, city);
    if (avaliacao_cidade) {
        calcula_avaliacao_media_AvC (avaliacao_cidade);
        array->pos++;
        array->array_avaliacoes = (AvC**) realloc (array->array_avaliacoes, array->pos * sizeof (AvC *));
        array->array_avaliacoes[array->pos-1] = getcontentAvC (avaliacao_cidade);
    }
}

void swapAvC (AvC **array, int min_idx, int i) {
    AvC *temp = array[min_idx];
    array[min_idx] = array[i];
    array[i] = temp;
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

void ordenaQ7 () {
    qsort (array->array_avaliacoes,(size_t)array->pos, getsizeAvC(), comparaAvC);
}

void printQ7 (FILE *fp,int N) {
    for (int i = array->pos -1; i > array->pos-N-1 && i > -1; i--) {
        AvC *pos = array->array_avaliacoes[i];
        char *id = getIdAvC (pos);
        char *name = getNameAvC (pos);
        double avaliacao_media = getAvaliacaoMediaAvC (pos);
        fprintf (fp, "%s;%s;%.3f\n",id, name,avaliacao_media);
        free (id);
        free (name);
    }
}

void free_Q7 () {
    for (int i = 0; i < array->pos; i++) free_avaliacao_por_cidade (array->array_avaliacoes[i]);
    free (array->array_avaliacoes);
    free (array);
}