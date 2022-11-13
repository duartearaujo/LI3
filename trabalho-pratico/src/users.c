#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"

struct user {    
    char* username;
    char* name;
    char* gender;
    char* data;
    char* account_creation;
    char* pay_method;
    char* account_status;
};

void free_user (User *value) {
    free(value->username);
    free(value->name);
    free(value->gender);
    free(value->data);
    free(value->account_creation);
    free(value->pay_method);
    free(value->account_status);
    free (value);
}

void criaHashUser (GHashTable *user, char *line) {
    User *new = malloc (sizeof (User));
    separa (line,new,1);
    g_hash_table_insert(user,new->username,new);
}

void atribui (User *user, int pos, char *info) {
    switch (pos){
        case 1:
            user->username = strdup (info); 
            break;
        case 2:
            user->name = strdup (info); 
            break;
        case 3:
            user->gender = strdup (info); 
            break;
        case 4:
            user->data = strdup (info); 
            break;
        case 5:
            user->account_creation = strdup (info); 
            break;
        case 6:
            user->pay_method = strdup (info); 
            break;
        case 7:
            user->account_status = strdup (info); 
            break;
    }
}

int lookupUser (GHashTable *user, FILE *res, char *name) {
    User *u = g_hash_table_lookup (user,name);
    if (!strcmp (u->account_status, "inactive")) return 1;
    fprintf (res, "%s;%s;%d;", u->name, u->gender, calculaIdade (u->data));
    return 0;
}