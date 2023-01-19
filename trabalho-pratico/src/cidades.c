#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/query7.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/cidades.h"

static GHashTable *cidades;

struct avaliacao_por_cidade {
    char *name, *id;
    int n_viagens;
    int avaliacao_total;
    double avaliacao_media;
    double preco_total;
};
struct HTree{
    GTree *t;
    int ordenado;
};

void free_cidade (gpointer cidades) {
    HTree *cidade = cidades;
    g_tree_destroy (cidade->t);
    free (cidade);
}

void free_avaliacao_por_cidade (gpointer value) {
    AvC *avc = value;
    free (avc->id);
    free (avc->name);
    free (avc);
}

void iniciaHashCidades () {
    cidades = g_hash_table_new_full (g_str_hash, g_str_equal, free, free_cidade);
}

void destroyHashCidades() {
    g_hash_table_destroy (cidades);
}

AvC* getcontentAvC (AvC *a) {
    AvC* copy = malloc (sizeof (AvC));
    copy->id = strdup (a->id); 
    copy->name = strdup (a->name);
    copy->n_viagens = a->n_viagens;
    copy->avaliacao_total = a->avaliacao_total;
    copy->avaliacao_media = a->avaliacao_media;
    copy->preco_total = a->preco_total;
    return copy;
}

gint compare_id (gconstpointer a, gconstpointer b, gpointer c) {
    return (strcmp (a, b));
}

void addToCidades (char *city,int distance, char type_car, char *driver,char* name ,int avaliacao) {
    double preco = 0;
    switch (identifie_car_class_char(type_car))
        {
        case 0:
            preco += distance * 0.62 + 3.25;
            break;
        case 1:
            preco += distance * 0.79 + 4;
            break;
        case 2:
            preco  += distance * 0.94 + 5.20;
            break;
        default:
            break;
        }

    if (g_hash_table_contains (cidades, city)) {
        HTree *ct = g_hash_table_lookup (cidades, city);
        AvC* nodo = g_tree_lookup (ct->t, driver);
        if (nodo) {
            nodo->n_viagens ++;
            nodo->avaliacao_total += avaliacao;
            nodo->preco_total += preco;
            free(name);
        }
        else {
            nodo = malloc (sizeof (AvC));
            nodo -> id = strdup (driver);
            nodo->name = name;
            nodo->preco_total = preco;
            nodo->avaliacao_total = avaliacao;
            nodo->avaliacao_media = 0;
            nodo->n_viagens = 1;
            g_tree_insert (ct->t,nodo->id, nodo);
        }
    }
    else {
        HTree *c = malloc (sizeof (HTree));
        GTree *ct = g_tree_new_full (compare_id,NULL,NULL, free_avaliacao_por_cidade);
        AvC *nodo = malloc (sizeof (AvC));
        nodo -> id = strdup (driver);
        nodo->name = name;
        nodo->preco_total = preco;
        nodo->avaliacao_total = avaliacao;
        nodo->avaliacao_media = 0;
        nodo->n_viagens = 1;
        g_tree_insert (ct,nodo->id, nodo);
        c->t = ct;
        c->ordenado = 0;
        char *key = strdup (city);
        g_hash_table_insert (cidades, key, c);   
    }
}

gboolean inc_preco_Q4 (gpointer key, gpointer value, gpointer user_data) {
    AvC *driver = value;
    double* total_a = user_data;
    total_a[1] += driver->n_viagens;
    total_a[0] += driver->preco_total;
    return FALSE;
}


void foreach_tree_city (char *city, double preco_medio []) {
    HTree *ct = g_hash_table_lookup (cidades, city);
    if (ct) {
        g_tree_foreach (ct->t,(GTraverseFunc) inc_preco_Q4, preco_medio);
    }
}

gboolean ordena_arvore_Q7_aux (gpointer key, gpointer value, gpointer user_data) {
    AvC *driver = value;
    if (driver->n_viagens) 
        driver->avaliacao_media = (double) driver->avaliacao_total /(double) driver->n_viagens;
    AvC *copia = getcontentAvC (driver);
    g_tree_insert (user_data, copia,copia);
    return FALSE;
}

void ordena_arvore_Q7 (char *city) {
    HTree* c = g_hash_table_lookup (cidades, city);
    if (c) {
        if (!c->ordenado) {
            GTree *new = g_tree_new_full (organiza_arvore,NULL,NULL,free_avaliacao_por_cidade); 
            g_tree_foreach (c->t, ordena_arvore_Q7_aux, new);
            g_tree_destroy (c->t);
            c->t = new;
        }
    }
}

typedef struct PrintQ7 {
    FILE *res;
    int N;
} PrintQ7;

gboolean printQ7_aux (gpointer key, gpointer value, gpointer user_data) {
    PrintQ7 *ficheiro = user_data;
    AvC* driver = value;
    fprintf (ficheiro->res,"%s;%s;%.3f\n",driver->id, driver->name, driver->avaliacao_media);
    ficheiro->N--;
    if (ficheiro->N)
        return FALSE;
    return TRUE;
}

void printQ7 (char *city,int N, FILE *res) {
    HTree *c= g_hash_table_lookup (cidades,city);
    if (c) {
        PrintQ7 *p = malloc(sizeof (PrintQ7));
        p->N = N;
        p->res = res;
        g_tree_foreach (c->t, printQ7_aux, p);
        free (p);
    }
}

char *getIdC (AvC const* a) {
    return strdup (a->id);
}

double getavaliacaomediaC (AvC const* a) {
    return a->avaliacao_media;
}