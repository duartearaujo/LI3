#include <stdio.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/queries.h"

/*faz parse das queries*/
void parsequerie (FILE *fp) {  
    int i = 0;
    int n_querie = 1;
    char **querie = NULL;
    char *line = NULL;
    size_t len;
    ssize_t read;
    while ((read = getline(&line, &len, fp)) != -1){   
        line[read-1] = '\0';
        char *temp = line;
        char *token = strsep(&temp," ");
        int Nquery = atoi (token);
        if (Nquery == 6) querie = malloc(4 * sizeof(char *));
        else if (Nquery > 4) querie = malloc(3 * sizeof(char *));
        else querie = malloc(2 * sizeof(char *));
        while (token) {
            querie[i] = strdup(token);  /*adiciona cada token ao array criado anteriormente*/
            token = strsep(&temp," ");
            i++;
        }
        queryHandler(querie, n_querie++, 0); /*chama a função que vai realizar cada querie consoante os valores presentes no array "querie"*/
        for (--i; i>= 0; i--) free (querie[i]);  /*free do array*/
        i = 0;
        free (querie);
    } 
    free (line);
}

/*responsável por fazer parse dos 3 ficheiros (users.csv,drivers.csv e rides.csv)*/
void parser(FILE *fp, int h) {  
    void (*fun_criar)(char*) = NULL;  /*function pointer*/
    char* line = NULL;
    size_t len;
    ssize_t read;
    if ((read = getline(&line, &len, fp)) == -1) return ;    
    switch (h) {  //consoante o valor do h, o function pointer vai apontar para a função responsável por criar os membros da hashtable*/
        case 1:
            fun_criar = &adicionaHashUsers;  /*criar membros da hashtable dos users*/
            break;
        case 2:
            fun_criar = &adicionaHashDrivers;  /*criar membros da hashtable dos drivers*/
            break;
        case 3:
            fun_criar = &adicionaEstruturasRides;  /*criar membros da hashtable dos rides*/
            break;
    }
    while ((read = getline(&line, &len, fp)) != -1){
            line[read-1] = '\0';
            (*fun_criar)(line);
    } 
    free (line);
}

/*chama as funções responsáveis por atribuir os tokens recebidos a cada campo do user/driver/ride*/
int separa(char *str, void *data,int s){  
    int pos= 1;
    char *token = strsep(&str,";");
    while(token){
        switch (s)  /*o s permite distinguir a que struct queremos mandar o token*/
        {
        case 1: {
            if (!atribui ((User*)data, pos++, token)) return 0;
            break;
        }
        case 2: {
            if (!assignsData ((RIDES*)data, pos++, token)) return 0;
            break;
        }
        case 3: {
            if(!atribui_drv((DRIVERS*)data, pos++, token)) return 0;
            break;  
        }
        default:
            break;
        }
        token = strsep(&str,";");
    }
    return 1;
}