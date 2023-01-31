#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"
#include "../include/query3.h"
#include "../include/interactive.h"

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
    if (Distance > Pdistance) result = -1;
    else if(Distance == Pdistance){ 
        int datas = compareDates(lastRide,PLastRide);  
        if(datas == 1) result = -1;   
        else if(datas == 2){    
            if(strcmp(username,Pusername) < 0) result = -1;  
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
int Q3Print(FILE *res, int N, int modo, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    int i = 0, j = 0, p = 0;
    char line[256] = {0};
    while(i < N){ /*Ciclo que limita o print dos elementos com base no input da querie*/
        User *user = getElement_Q3(j);
        char AccSt = getAccStatusU(user);
        char *username = getUsername(user);
        char *name =getNameU(user);
        int distance = getDistance(user);
        if(AccSt == 'a'){ /*Se o status for inativo então o user é ignorado e o print não é executado*/
            if (modo == 0)
                fprintf(res, "%s;%s;%d\n", username, name, distance);
            else{
                mvprintw(informacoespaginas[0], 0, "\t%s;%s;%d", username, name, distance);
                sprintf(line, "\t%s;%s;%d", username, name, distance);
                paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup(line);
                if (informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (informacoespaginas, paginas)) return 0; 
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

int query3Exe(FILE *res,int modo,char* argv, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    int r = 1;
    if (atoi (argv)) {
        if(!arrayOrdenadoU()){
            createArrayUser();
            foreach_users_Q3();
            ordena_Q3();
        }
        r = Q3Print(res, atoi(argv), modo, informacoespaginas, paginas);
    }
    return r;
}