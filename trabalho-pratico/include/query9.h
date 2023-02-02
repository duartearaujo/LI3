#ifndef query9
#define query9

#include "../include/interactive.h"

typedef struct Q9_aux Q9_aux;

int desempate_Q9(const void *p1, const void* p2);

int Q9Print(FILE *res, int t1, int t2, int modo);

int query9Exe(FILE *res, int modo, char **argv);

#endif