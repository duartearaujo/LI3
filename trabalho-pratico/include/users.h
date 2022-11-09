#ifndef users
#define users

#include <glib.h>

typedef struct user User;

void criaHashUser (GHashTable *user, char *line);

void atribui (User* user, int pos, char *info);

void lookupUser (GHashTable *user);

#endif