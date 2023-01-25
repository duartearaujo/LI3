#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query9.h"


int desempate_Q9(const void *p1, const void* p2){
    RIDES *dados_1 = *((RIDES**) p1);
    RIDES *dados_2 = *((RIDES**) p2);
    int result = 1;
    int distance = getdistanceR (dados_1);
    int PDistance = getdistanceR (dados_2);
    if(distance > PDistance) result = -1;
    if(distance == PDistance){ 
        int Date = getIdadeViagem (dados_1);
        int PDate = getIdadeViagem (dados_2);
        if(Date == PDate){
            char *id = getIdR (dados_1);
            char *Pid = getIdR (dados_2);
            if(strcmp(id, Pid) > 0) result = -1;
            free (id);
            free (Pid);
        }
        else if(Date < PDate) result = -1;
    }
    return result;
}

void Q9Print(FILE *res, int t1, int t2, int modo){
    int t;
    int i = 0;
    int tamanho = getposQ9 ();
    while(i < tamanho){ 
        t = getIdadeViagem_Q9 (i);
        if(t <= t1 && t2 <= t){
            char *id = getId_Q9 (i);
            char *date = getDate_Q9 (i);
            int distance = getDistance_Q9 (i);
            char *city = getCity_Q9 (i);
            double tip = getTip_Q9 (i);
            if(modo == 0) 
                fprintf(res, "%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
            else
                printf("\t%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
            free (id);
            free (date);
            free (city);
        }
        i++;
    }
}
