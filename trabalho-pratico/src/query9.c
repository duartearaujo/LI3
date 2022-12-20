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
    new->tip = NULL;
    return new;
}

struct ARRAY_Q9{
    int pos;
    char *data1;
    char *data2; 
    Q9 **q; 
};

static ARRAY_Q9 *array = NULL;

void createArrayQ9(char *data1, char *data2){
    array = malloc(sizeof(ARRAY_Q9));
    array->pos = 0;
    array->data1 = data1;
    array->data2 = data2;
    array->q = NULL;
}

void guardaQ9(gpointer key, RIDES *ride, void *a){
    Q9 *q = inicializaQ9();                                // ver a inicialização
    char *data = getDateR(ride);
    char *tip = getTip (ride);
    int datas_1 = compareDates(data, array->data1);
    int datas_2 = compareDates(data, array->data2);
    if(tip && ((datas_1 && (datas_2 == 2 || !datas_2)) || !strcmp(data, array->data1) || !strcmp(data, array->data2))){
        array->pos++;
        array->q = (Q9**) realloc(array->q,array->pos * sizeof(Q9*));
        q->id = getIdR(ride);
        q->date = data;
        q->city = getcityR(ride);
        q->distance = getdistanceR(ride);
        q->tip = tip;
        array->q[(array->pos - 1)] = q;
    }
    else {
        free (data);
        free_Q9 (q);
        free (tip);
    }
}

int desempate_Q9(const void *p1, const void* p2){
    Q9 *dados_1 = *((Q9**) p1);
    Q9 *dados_2 = *((Q9**) p2);
    int result = 1;
    int distance = dados_1->distance;
    int PDistance = dados_2->distance;
    char *Date = dados_1->date;
    char *PDate = dados_2->date;
    char *id = dados_1->id;
    char *Pid = dados_2->id;
    if(distance > PDistance) result = -1;
    if(distance == PDistance){ 
        int datas = compareDates(Date, PDate);
        if(datas == 2){
            if(strcmp(id, Pid) > 0) result = -1;
        }
        else if(datas == 1) result = -1;
    }
    return result;
}

void ordena_Q9(){  
    qsort (array->q,(size_t)array->pos, sizeof(Q9*), desempate_Q9);
}

void Q9Print(FILE *res){
    int i = 0;
    while(i < array->pos){ 
        char *id = array->q[i]->id;
        char *date = array->q[i]->date;
        int distance = array->q[i]->distance;
        char *city = array->q[i]->city;
        double tip = strtod(array->q[i]->tip, NULL);
        fprintf(res, "%s;%s;%d;%s;%.3f\n", id, date, distance, city, tip);
        i++; 
    }
}

void freeArrayQ9(){
    if(array){
        for(int i = 0; i < array->pos; i++){
            free_Q9(array->q[i]);
        }
        free(array->q);
        free(array->data1);
        free(array->data2);
        free(array);
    }
}

