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
    char **querie = malloc(2 * sizeof(char *));
    char *line = NULL;
    size_t len;
    ssize_t read;;
    while ((read = getline(&line, &len, fp)) != -1){   
        line[read-1] = '\0';
        char *temp = line;
        char *token = strsep(&temp," ");
        while (token) {
            querie[i] = strdup(token);
            token = strsep(&temp," ");
            i++;
        }
        querieIdentifier(querie, hash);  
        for (--i; i>= 0; i--) free (querie[i]);
        i = 0;
    } 
    free (querie);
    free (line);
}

void parser(FILE *fp, HASH* hash, int h) {
    void (*fun_criar)(HASH*,char*) = NULL;
    char* line = NULL;
    size_t len;
    ssize_t read;;
    if ((read = getline(&line, &len, fp)) == -1) return ;    
    switch (h) {
        case 1:
            fun_criar = &criaHashUser;
            break;
        case 2:
            fun_criar = &novo;
            break;
        case 3:
            fun_criar = &newElement;
            break;
    }
    while ((read = getline(&line, &len, fp)) != -1){
            line[read-1] = '\0';
            (*fun_criar)(hash,line);
    } 
    free (line);
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