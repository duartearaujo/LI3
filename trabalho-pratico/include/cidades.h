#ifndef Cidades
#define Cidades

typedef struct avaliacao_por_cidade AvC;

typedef struct HTree HTree;

void iniciaHashCidades ();

void destroyHashCidades();

AvC* getcontentAvC (AvC *a);

void free_avaliacao_por_cidade (gpointer value);

void addToCidades (char *city,int distance, char type_car, char *driver,char *name ,int avaliacao);

void foreach_tree_city (char *city, double preco_medio []);

void ordena_arvore_Q7 (char *city);

void printQ7 (char *city,int N, FILE *res);

char *getIdC (AvC const* a);

double getavaliacaomediaC (AvC const* a);

#endif