#ifndef parse
#define parse

#include <glib.h>
#include "users.h"

void parser (FILE* fp,GHashTable* table, int h );

void separa (char *str, void *data, int s);

#endif