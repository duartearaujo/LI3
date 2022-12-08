#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/query6.h"

struct Q6{
    char *city;
    char *data1;
    char *data2;
    double total_distance;
    int n_rides;
};

Q6* inicializaQ6 (char *city, char *data1, char *data2){
    Q6 *new = malloc (sizeof (Q6));
    new->city = city;
    new->data1 = data1;
    new->data2 = data2;
    new->total_distance = 0;
    new->n_rides = 0;
    return new;
}

void distancia_media(gpointer key, RIDES *ride, Q6 *q){
    char *city = getcityR(ride);
    char *data = getDateR(ride);
    char *distance = getdistanceR(ride);
    if(!strcmp(q->city, city) && ((compareDates(data, q->data1) == 1 && compareDates(data, q->data2) == 0) || !strcmp(data, q->data1) || !strcmp(data, q->data2))){
        q->n_rides++;
        q->total_distance += strtod(distance, NULL);
    }
    free(city);
    free(data);
    free(distance);
}

void printQ6(Q6 *q, FILE *res){
    double distancia_media = (q->total_distance/q->n_rides);
    fprintf(res, "%.3f\n", distancia_media);
}

void freeQ6(Q6 *q){
    free(q->city);
    free(q->data1);
    free(q->data2);
    free(q);
}

