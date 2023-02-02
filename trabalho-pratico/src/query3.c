#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"
#include "../include/query3.h"
#include "../include/interactive.h"
#include "../include/datas.h"

/*Função utilizada pelo quicksort para ordenar os users da forma correta para a query 3*/
int desempate_Q3(const void *p1, const void* p2){
    User *user_1 = GetcontentU(*((User**) p1));
    User *user_2 = GetcontentU(*((User**) p2));
    int result = 1;
    int Distance = getDistance(user_1);
    int Pdistance = getDistance(user_2);
    char *lastRide = getLastRide(user_1);
    char *PLastRide = getLastRide(user_2);
    char *username = getUsername(user_1);
    char *Pusername = getUsername(user_2);
    if (Distance > Pdistance) result = -1; /*A troca dos elementos é efetuada (decisão baseada nas distâncias)*/
    else if(Distance == Pdistance){ 
        int datas = compareDates(lastRide,PLastRide);  
        if(datas == 1) result = -1; /*A troca dos elementos é efetuada (desempate com base nas datas)*/
        else if(datas == 2){    
            if(strcmp(username,Pusername) < 0) result = -1; /*A troca dos elementos é efetuada (desempate com base nos usernames)*/
        }
    }
    free(lastRide);
    free(PLastRide);
    free(username);
    free(Pusername);
    free_user(user_1);
    free_user(user_2);
    return result;
}

/*Função que faz print dos resultados da querie 3*/
int Q3Print(FILE *res, int N, int modo){
    int i = 0, j = 0, p = 0;
    char line[256] = {0};
    while(i < N){ /*Ciclo que limita o print dos elementos com base no input da querie*/
        User *user = getElement_Q3(j);
        char AccSt = getAccStatusU(user);
        char *username = getUsername(user);
        char *name =getNameU(user);
        int distance = getDistance(user);
        if(AccSt == 'a'){ /*Se o status for inativo então o user é ignorado e o print não é executado*/
            if (modo == 0) /*Modo batch*/
                fprintf(res, "%s;%s;%d\n", username, name, distance);
            else{ /*Modo interativo*/
                sprintf(line, "\t%s;%s;%d", username, name, distance);
                if (!copia (strdup (line))) {
                    free (name);
                    free (username);
                    return 0;
                }
            }
            i++;
            p++;
        }
        j++;
        free(username);
        free(name);
        free_user(user);
    }
    return 1;
}

/*Função chamada pela querieIdentifier para executar a query 3*/
int query3Exe(FILE *res,int modo,char* argv){
    int r = 1;
    if (atoi (argv)){
        r = Q3Print(res, atoi(argv), modo);
    }
    return r;
}