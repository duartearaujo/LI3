#ifndef parse
#define parse

#include <glib.h>
#include "../include/main.h"

void parsequerie (FILE *fp, HASH *hash);

void parser(FILE *fp, HASH* hash, int h);

void separa (char *str, void *data, int s);

#endif