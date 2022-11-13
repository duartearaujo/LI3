#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/main.h"

void parsequerie (FILE *fp, HASH *hash) {
    int i = 0;
    char **querie = NULL;
    char *line = NULL;
    size_t len;
    ssize_t read;;
    while ((read = getline(&line, &len, fp)) != -1){   
        line[read-1] = '\0';
        querie = malloc(4 * sizeof(char *));
        char *token = strsep(&line," ");
        while (token) {
            querie[i] = strdup(token);
            token = strsep(&line," ");
            i++;
        }
        i = 0;
        querieIdentifier(&(*querie), hash);    
    } 
}

void parser(FILE *fp, GHashTable* table, int h) {
    void (*fun_criar)(GHashTable*,char*) = NULL;
    char* line = NULL;
    size_t len;
    ssize_t read;;
    if ((read = getline(&line, &len, fp)) == -1) return ;    
    switch (h) {
        case 1:
            fun_criar = &criaHashUser;
            break;
        case 2:
            fun_criar = &newElement;
            break;
        case 3:
            fun_criar = &novo;
            break;
    }
    while ((read = getline(&line, &len, fp)) != -1){
            line[read-1] = '\0';
            (*fun_criar)(table,line);
    } 
}

void separa(char *str, void *data,int s){
    int pos= 1;
    char *token = strsep(&str,";");
    while(token){
        switch (s)
        {
        case 1: {
            atribui ((User*)data, pos++, token);
            break;
        }
        case 2: {
            assignsData ((RIDES*)data, pos++, token);
            break;
        }
        case 3: {
            atribui_drv((DRIVERS*)data, pos++, token);
            break;  
        }
        default:
            break;
        }
        token = strsep(&str,";");
    }
}