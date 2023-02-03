#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query9.h"
#include "../include/interactive.h"
#include "../include/datas.h"

/*Função utilizada pelo quicksort para ordenar as rides da forma que se adequa à query 9*/
int desempate_Q9(const void *p1, const void* p2) {
    RIDES *dados_1 = *((RIDES**) p1);
    RIDES *dados_2 = *((RIDES**) p2);
    int result = 1;
    int distance = getdistanceR (dados_1);
    int PDistance = getdistanceR (dados_2);
    if(distance > PDistance) result = -1; /*A troca dos elementos é efetuada (decisão baseada nas distâncias)*/
    if(distance == PDistance){ 
        int Date = getIdadeViagem (dados_1);
        int PDate = getIdadeViagem (dados_2);
        if(Date == PDate){
            char *id = getIdR (dados_1);
            char *Pid = getIdR (dados_2);
            if(strcmp(id, Pid) > 0) result = -1; /*A troca dos elementos é efetuada (desempate com base nos IDs)*/
            free (id);
            free (Pid);
        }
        else if(Date < PDate) result = -1; /*A troca dos elementos é efetuada (desempate com base nas datas)*/
    }
    return result;
}

/*Função que faz o print dos resultados da query 9*/
int Q9Print(FILE *res, int t1, int t2, int modo){
    int t;
    int i = 0;
    int tamanho = getposQ9 (), max = getPosQ5Q6();
    char line[256] = {0};
    if (getTempoDeVida (max-1) > t2 && t1 >= 0) {
        while(i < tamanho){ 
            t = getIdadeViagem_Q9 (i);
            if(t <= t1 && t2 <= t){ /*Verifica se a data da viagem se encontra no intervalo de tempo desejado*/
                char *id = getId_Q9 (i);
                char *date = getDate_Q9 (i);
                int distance = getDistance_Q9 (i);
                char *city = getCity_Q9 (i);
                double tip = getTip_Q9 (i);
                if(modo == 0) /*Modo batch*/
                    fprintf(res, "%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
                else{ /*Modo interativo*/
                    sprintf(line, "\t%s;%s;%d;%s;%.3f", id, date, distance, city, tip);
                    if (!copia (strdup (line))) {
                        free (id);
                        free (date);
                        free (city);
                        return 0;
                    }
                }
                free (id);
                free (date);
                free (city);
            }
            i++;
        }
    }
    return 1;
}

/*Função chamada pela querieIdentifier para executar a query 9*/
int query9Exe(FILE *res, int modo, char **argv){
    int r = 1;
    int t1 = tempo_De_Vida(strdup(argv[1]));
    int t2 = tempo_De_Vida(strdup(argv[2]));
    r = Q9Print(res, t1, t2, modo);
    return r;
}