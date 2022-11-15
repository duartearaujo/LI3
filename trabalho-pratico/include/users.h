#ifndef users
#define users

#include <glib.h>

typedef struct user User;

void free_user(User *value);

void criaHashUser (HASH *hash, char *line);

void atribui (User* user, int pos, char *info);

int lookupUser (GHashTable *user, FILE *res, char *name);

#endif