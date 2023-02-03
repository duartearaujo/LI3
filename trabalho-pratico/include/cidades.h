#ifndef Cidades
#define Cidades

#include <ncurses.h>
#include "../include/interactive.h"
#include "../include/query7.h"

typedef struct avaliacao_por_cidade AvC;

typedef struct HTree HTree;

void iniciaHashCidades ();

void destroyHashCidades();

AvC* getcontentAvC (AvC *a);

void free_avaliacao_por_cidade (gpointer value);

void addToCidades (char *city,int distance, char type_car, char *driver,char *name ,int avaliacao);

void foreach_tree_city (char *city, double preco_medio []);

void ordena_arvore_Q7 (char *city);

char *getIdC (AvC const* a);

double getavaliacaomediaC (AvC const* a);

char *getIdAvC (AvC *a);

char *getNameAvC (AvC *a);

double getAvaliacaoMediaAvC (AvC *a);

void tree_foreach_city (char *city, PrintQ7 *p);

int existscity (char *city);

#endif