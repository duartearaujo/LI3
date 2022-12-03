#ifndef query2
#define query2

typedef struct ARRAY_DRIVERS ARRAY_DRIVERS;

void createArray();

void printfArray(FILE *res,int N);

void calcula_mediasQ2 (gpointer key, DRIVERS* driver, void* a);

void ordenaArray();

int arrayOrdenado();

void freeArray();

#endif