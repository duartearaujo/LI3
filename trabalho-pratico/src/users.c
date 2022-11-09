#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"

struct user {    
    char* username;
    char* name;
    char* gender;
    char* data;
    char* account_creation;
    char* pay_method;
    char* account_status;
};

void criaHashUser (GHashTable *user, char *line) {
    User *new = malloc (sizeof (User));
    separa (line, new);
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

void lookupUser (GHashTable *user) {
    User *n = g_hash_table_lookup (user,"LuVieira");
    char *s = n->name;
    printf ("%s\n",s);
}