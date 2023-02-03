#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/cidades.h"
#include "../include/query7.h"
#include "../include/drivers.h"

/* Hash Table para guardar informações de drivers respetivamente a cada cidade*/
static GHashTable *cidades;

/* Struct para guardar informacões úteis às queries 4 e 7*/
struct avaliacao_por_cidade {
    char *name, *id; /**< Campos para guardar o nome e id do driver*/
    int n_viagens; /**< Campo para guardar o número total de viagens na cidade do driver*/
    int avaliacao_total; /**< Campo para guardar o total de todas as avaliacoes na cidade do driver*/
    double avaliacao_media; /**< Campo para guardar a avaliação média do driver na cidade do driver*/
    double preco_total; /**< Campo para guardar o preco total de todas as viagens na cidade do driver*/
};

/* Struct para colocar na Hash Table cidades. Contém uma árvore de AvC* e um int para indicar se a árvore está ordenada de acordo com as exigências da query 7*/
struct HTree{
    GTree *t;
    int ordenado;
};

/* Função para dar free à estrutura HTree*/
void free_cidade (gpointer cidades) {
    HTree *cidade = cidades;
    g_tree_destroy (cidade->t);
    free (cidade);
}

/* Função para dar free à estrutura AvC*/
void free_avaliacao_por_cidade (gpointer value) {
    AvC *avc = value;
    free (avc->id);
    free (avc->name);
    free (avc);
}

/* Função para inicializar a hash table das cidades*/
void iniciaHashCidades () {
    cidades = g_hash_table_new_full (g_str_hash, g_str_equal, free, free_cidade);
}

/* Função para destruir a hash table das cidades*/
void destroyHashCidades() {
    g_hash_table_destroy (cidades);
}

/* Função para criar uma cópia de uma AvC*/
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

/* Função de comparação para inserir pela primeira vez as structs AvC's nas árvores. Apenas ordena pelo Id com a função strcmp*/
gint compare_id (gconstpointer a, gconstpointer b, gpointer c) {
    return (strcmp (a, b));
}

/* Função para adicionar informações à hash table cidades. */
void addToCidades (char *city,int distance, char type_car, char *driver,char* name ,int avaliacao) {
    double preco = 0;
    switch (identifie_car_class_char(type_car)) /* Calcular o preço da viagem*/
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

    if (g_hash_table_contains (cidades, city)) { /* Verifica se já foi adicionado alguma viagem à cidade recebida*/
        HTree *ct = g_hash_table_lookup (cidades, city);
        AvC* nodo = g_tree_lookup (ct->t, driver);
        if (nodo) {  /*Verifica se o driver já existe na árvore da cidade e, se existir, incrementa as informações necessárias, se não, cria um novo nodo e dá insert na cidade*/
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
    else { /* Se não exitir uma árvore para a cidade recebida é criada uma nova junto com o seu primeiro nodo e é dado insert da árvore na hash table*/
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

/* Função auxiliar da query 4. Incrementa o número de viagens e o preco total na cidade no array de double recebido.*/
gboolean inc_preco_Q4 (gpointer key, gpointer value, gpointer user_data) {
    AvC *driver = value;
    double* total_a = user_data;
    total_a[1] += driver->n_viagens;
    total_a[0] += driver->preco_total;
    return FALSE;
}

/* Função auxiliar da query 4. Verifica se exite a cidade pedida e, se existir, realiza uma travessia ordenada na árvore com a função inc_preco_Q4 para calcular os preços.*/
void foreach_tree_city (char *city, double preco_medio []) {
    HTree *ct = g_hash_table_lookup (cidades, city);
    if (ct) {
        g_tree_foreach (ct->t,(GTraverseFunc) inc_preco_Q4, preco_medio);
    }
}

/* Função para ordenar a árvore adequadamente à query 7. A cada AvC é calculado a avaliação média e dado insert na nova árvore.*/
gboolean ordena_arvore_Q7_aux (gpointer key, gpointer value, gpointer user_data) {
    AvC *driver = value;
    if (driver->n_viagens) 
        driver->avaliacao_media = (double) driver->avaliacao_total /(double) driver->n_viagens;
    AvC *copia = getcontentAvC (driver);
    g_tree_insert (user_data, copia,copia);
    return FALSE;
}

/* Função de ordenação das árvores. Se a árvore da cidade pedida existir e não tiver sido ordenada é criado uma nova árvore q vai ser preenchida com a função ordena_arvore_Q7_aux.
No final é destruido a árvore original e é inserido a nova que se encontra ordenada.*/
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

/* Função auxiliar da query 7. Realiza uma travessia ordenada na árvore correspondente.*/
void tree_foreach_city (char *city, PrintQ7 *p) {
    HTree *c = g_hash_table_lookup(cidades, city);
    if (c) {
        g_tree_foreach (c->t,printQ7_aux,p);
    }
}

/* Devolve o Id de um AvC const*.*/
char *getIdC (AvC const* a) {
    return strdup (a->id);
}

/* Devolve a avaliacao média de um AvC const*.*/
double getavaliacaomediaC (AvC const* a) {
    return a->avaliacao_media;
}

/* Devolve o Id de um AvC*.*/
char *getIdAvC (AvC *a) {
    return strdup (a->id);
}

/* Devolve o nome de um AvC*.*/
char *getNameAvC (AvC *a) {
    return strdup (a->name);
}

/* Devolve a avaliacao media de um AvC*.*/
double getAvaliacaoMediaAvC (AvC *a) {
    return a->avaliacao_media;
}

/* Verifica se existe a cidade recebida*/
int existscity (char *city) {
    HTree *c = g_hash_table_lookup (cidades,city);
    if (c) return 1;
    return 0;
}