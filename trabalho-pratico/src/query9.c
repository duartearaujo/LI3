#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query9.h"

struct Q9{
    char *id;
    char *date;
    char *city;
    char *tip;
    int distance;
    int t_vida;
};

void free_Q9 (Q9 *q) {
   free (q->id);
   free (q->date);
   free (q->city);
   free (q->tip);
   free (q);
}

Q9* inicializaQ9 (){
    Q9 *new = malloc (sizeof (Q9));
    new->id = NULL;
    new->date = NULL;
    new->city = NULL;
    new->distance = 0;
    new->t_vida = 0;
    new->tip = NULL;
    return new;
}

struct ARRAY_Q9{
    int pos;
    Q9 **q; 
};

static ARRAY_Q9 *array = NULL;

void createArrayQ9(){
    array = malloc(sizeof(ARRAY_Q9));
    array->pos = 0;
    array->q = NULL;
}

void addQ9(RIDES *ride){
    Q9 *q = inicializaQ9();                     
    array->pos++;
    array->q = (Q9**) realloc(array->q,array->pos * sizeof(Q9*));
    q->id = getIdR(ride);
    q->date = getDateR(ride);
    q->city = getcityR(ride);
    q->distance = getdistanceR(ride);
    q->t_vida = tempo_De_Vida(strdup(q->date));
    q->tip = getTip (ride);
    array->q[(array->pos - 1)] = q;
}

int desempate_Q9(const void *p1, const void* p2){
    Q9 *dados_1 = *((Q9**) p1);
    Q9 *dados_2 = *((Q9**) p2);
    int result = 1;
    int distance = dados_1->distance;
    int PDistance = dados_2->distance;
    int Date = dados_1->t_vida;
    int PDate = dados_2->t_vida;
    char *id = dados_1->id;
    char *Pid = dados_2->id;
    if(distance > PDistance) result = -1;
    if(distance == PDistance){ 
        if(Date == PDate){
            if(strcmp(id, Pid) > 0) result = -1;
        }
        else if(Date < PDate) result = -1;
    }
    return result;
}

void ordena_Q9(){  
    qsort (array->q,(size_t)array->pos, sizeof(Q9*), desempate_Q9);
}

void Q9Print(FILE *res, int t1, int t2, int modo){
    int t;
    int i = 0;
    while(i < array->pos){ 
        t = array->q[i]->t_vida;
        if(t <= t1 && t2 <= t){
            char *id = array->q[i]->id;
            char *date = array->q[i]->date;
            int distance = array->q[i]->distance;
            char *city = array->q[i]->city;
            double tip = strtod(array->q[i]->tip, NULL);
            if(modo == 0) 
                fprintf(res, "%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
            else
                printf("\t%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
        }
        i++;
    }
}

void freeArrayQ9(){
    if(array){
        for(int i = 0; i < array->pos; i++){
            free_Q9(array->q[i]);
        }
        free(array->q);
        free(array);
    }
}

