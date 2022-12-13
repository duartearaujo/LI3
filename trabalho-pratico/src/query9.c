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
    char *distance;
    char *tip;
};

void free_Q9 (Q9 *q) {
   free (q->id);
   free (q->date);
   free (q->city);
   free (q->distance);
   free (q->tip);
   free (q);
}

Q9* inicializaQ9 (){
    Q9 *new = malloc (sizeof (Q9));
    new->id = NULL;
    new->date = NULL;
    new->city = NULL;
    new->distance = NULL;
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
    Q9 *q = inicializaQ9();
    char *data = getDateR(ride);
    char *tip = getTip (ride);
    if(tip && ((compareDates(data, array->data1) == 1 && compareDates(data, array->data2) == 0) || !strcmp(data, array->data1) || !strcmp(data, array->data2))){
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

void swap_Q9(int i, int t){
    Q9 *r = array->q[i];
    array->q[i] = array->q[t];
    array->q[t] = r;
}


void QSRecursion_Q9(int i, int j){
    if(i < j){
        int pivot_i = partition_Q9(i, j);
        QSRecursion_Q9(i, pivot_i-1); 
        QSRecursion_Q9(pivot_i+1, j); 
    }
}

void QuickSort_Q9(){
    int N = array->pos;
    QSRecursion_Q9(0, N-1);
}

int partition_Q9(int i, int j){
    Q9 *pivot = array->q[j];
    for(int t = i; t < j; t++){
        int distance = atoi(array->q[t]->distance);
        int PDistance = atoi(pivot->distance);
        char *Date = array->q[t]->date;
        char *PDate = pivot->date;
        char *id = array->q[t]->id;
        char *Pid = pivot->id;
        if(distance == PDistance){ 
            if(compareDates(Date, PDate) == 2){ 
                if(strcmp(id, Pid) < 0){  
                    swap_Q9(i, t);
                    i++;
                }
            }
            else if(compareDates(Date, PDate) == 0){ 
                swap_Q9(i, t);
                i++;
            }
        }
        if(distance < PDistance){ 
            swap_Q9(i, t);
            i++;
        }
    }
    swap_Q9(i, j); 
    return i;
}

void Q9Print(FILE *res){
    int i = (array->pos - 1);
    while(i >= 0){ 
        char *id = array->q[i]->id;
        char *date = array->q[i]->date;
        char *distance = array->q[i]->distance;
        char *city = array->q[i]->city;
        double tip = strtod(array->q[i]->tip, NULL);
        fprintf(res, "%s;%s;%s;%s;%.3f\n", id, date, distance, city, tip);
        i--; 
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