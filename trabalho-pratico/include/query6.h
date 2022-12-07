#ifndef query6
#define query6

typedef struct Q6 Q6;

Q6* inicializaQ6 (char *city, char *data1, char *data2);

void distancia_media(gpointer key, RIDES *ride, Q6 *q);

void printQ6(Q6 *q, FILE *res);

void freeQ6(Q6 *q);

#endif 