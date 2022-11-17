#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/main.h"

void parsequerie (FILE *fp, HASH *hash) {  /*faz parse das queries*/
    int i = 0;
    int n_querie = 1;
    char **querie = malloc(2 * sizeof(char *));
    char *line = NULL;
    size_t len;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1){   
        line[read-1] = '\0';
        char *temp = line;
        char *token = strsep(&temp," ");
        while (token) {
            querie[i] = strdup(token);  /*adiciona cada token ao array criado anteriormente*/
            token = strsep(&temp," ");
            i++;
        }
        querieIdentifier(querie, hash, n_querie++); /*chama a função que vai realizar cada querie consoante os valores presentes no array "querie"*/
        for (--i; i>= 0; i--) free (querie[i]);  /*free do array*/
        i = 0;
    } 
    free (querie);
    free (line);
}

void parser(FILE *fp, HASH* hash, int h) {  /*responsável por fazer parse dos 3 ficheiros (users.csv,drivers.csv e rides.csv)*/
    void (*fun_criar)(HASH*,char*) = NULL;  /*function pointer*/
    char* line = NULL;
    size_t len;
    ssize_t read;
    if ((read = getline(&line, &len, fp)) == -1) return ;    
    switch (h) {  //consoante o valor do h, o function pointer vai apontar para a função responsável por criar os membros da hashtable*/
        case 1:
            fun_criar = &criaHashUser;  /*criar membros da hashtable dos users*/
            break;
        case 2:
            fun_criar = &novo;  /*criar membros da hashtable dos drivers*/
            break;
        case 3:
            fun_criar = &newElement;  /*criar membros da hashtable dos rides*/
            break;
    }
    while ((read = getline(&line, &len, fp)) != -1){
            line[read-1] = '\0';
            (*fun_criar)(hash,line);
    } 
    free (line);
}

void separa(char *str, void *data,int s){  /*chama as funções responsáveis por atribuir os tokens recebidos a cada campo do user/driver/ride*/
    int pos= 1;
    char *token = strsep(&str,";");
    while(token){
        switch (s)  /*o s permite distinguir a que struct queremos mandar o token*/
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