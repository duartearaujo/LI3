#ifndef q7
#define q7

typedef struct Q7 Q7;

void inicializaQ7 ();

void avaliacao_media_city (gpointer key, DRIVERS *value, char *city);

void ordenaQ7 ();

void printQ7 (FILE *fp,int N);

void free_Q7 ();

#endif