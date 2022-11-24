#ifndef q4
#define q4

typedef struct Q4 Q4;

Q4* inicializaQ4 (char *city);

void freeQ4 (Q4 *value);

void preco_medio (gpointer key, RIDES *value, Q4 *total);

void printQ4 (Q4 *value, FILE *res);

#endif