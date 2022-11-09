#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"

void parser(FILE *fp, GHashTable* table, int h) {
    void (*fun_criar)(GHashTable*,char*);
    char* line = NULL;
    size_t len;
    ssize_t read;;
    switch (h) {
        case 1:
            fun_criar = &criaHashUser;
            break;
    }
    while ((read = getline(&line, &len, fp)) != -1){
            line[read-1] = '\0';
            (*fun_criar)(table,line);
    } 
}

void separa(char *str, User *user){
    int pos= 1;
    char *token = strsep(&str,";");
    while(token){
        atribui (user, pos++, token);
        token = strsep(&str,";");
    }
}
