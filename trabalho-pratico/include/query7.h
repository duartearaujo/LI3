#ifndef q7
#define q7

typedef struct Q7 Q7;

void inicializaQ7 ();

void avaliacao_media_city (gpointer key, DRIVERS *value, char *city);

int comparaAvC (const void *p1, const void* p2);

void printQ7 (FILE *fp,int N);

#endif