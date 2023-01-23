#ifndef query9
#define query9

typedef struct Q9 Q9;

typedef struct ARRAY_Q9 ARRAY_Q9;

Q9* inicializaQ9 ();

void createArrayQ9();

void addQ9(RIDES *ride);

int desempate_Q9(const void *p1, const void* p2);

void ordena_Q9();

void Q9Print(FILE *res, int t1, int t2, int modo);

void free_Q9 (Q9 *q);

void freeArrayQ9();

#endif