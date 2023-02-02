#ifndef q7
#define q7

#include <ncurses.h>
#include "../include/interactive.h"

typedef struct PrintQ7 PrintQ7;

gint organiza_arvore (gconstpointer a, gconstpointer b, gpointer c);

gboolean printQ7_aux (gpointer key, gpointer value, gpointer user_data);

int printQ7 (char *city,int N, FILE *res, int modo);

int exec_Q7 (char *city,int N ,FILE *res, int modo);

#endif