#ifndef parse
#define parse

#include <glib.h>
#include "users.h"

void parser (FILE* fp,GHashTable* table, int h );

void separa (char *str, User *user);

#endif