#ifndef query2
#define query2

typedef struct ARRAY_DRIVERS ARRAY_DRIVERS;

ARRAY_DRIVERS* createArray(int N);

void printfArray(FILE *res,ARRAY_DRIVERS * array,int N);

void calcula_mediasQ2 (gpointer key, DRIVERS* driver, ARRAY_DRIVERS* array);

void ordenaArray(ARRAY_DRIVERS* array,int tamanho);

void freeArray(ARRAY_DRIVERS* array);

#endif