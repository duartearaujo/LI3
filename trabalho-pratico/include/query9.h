#ifndef query9
#define query9

typedef struct Q9 Q9;

typedef struct ARRAY_Q9 ARRAY_Q9;

Q9* inicializaQ9 ();

void createArrayQ9(char *data1, char *data2);

void guardaQ9(gpointer key, RIDES *ride, void *a);

void swap_Q9(int i, int t);

void QuickSort_Q9();

void QSRecursion_Q9(int i, int j);

int partition_Q9(int i, int j);

void Q9Print(FILE *res);

void free_Q9 (Q9 *q);

void freeArrayQ9();

#endif