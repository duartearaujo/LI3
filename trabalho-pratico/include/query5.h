#ifndef q5
#define q5

typedef struct Q5 Q5;

Q5* inicializaQ5(char *data_inferior, char *data_superior);

void freeQ5 (Q5 *query5);

void preco_medio_Q5(gpointer key, RIDES *value, Q5 *query5);

void printQ5 (Q5 *query5, FILE *res);

#endif