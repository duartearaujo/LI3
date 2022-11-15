#ifndef rides
#define rides

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/main.h"

typedef struct RIDES RIDES;

typedef struct Q1USER Q1USER;

typedef struct RIDES_AM RIDES_AM;

typedef struct ARRAYS_RIDES ARRAYS_RIDES;

void free_ride (RIDES *value);

Q1USER *inicializaQ1 (HASH *hash, char *argv);

void free_struct_Q1 (Q1USER *valores);

void assignsData(RIDES* new_ride ,int pos ,char* token);

void newElement(HASH *hash,char *line);

void lookupRide(GHashTable* hashRides);

void calcula_mediasQ1 (gpointer key, RIDES *value, double  *user_data);

void calcula_mediasQ1_2 (gpointer key, RIDES *value, Q1USER *user_data); 

void printQ1 (Q1USER *valores, FILE *res);

ARRAYS_RIDES* createArray(int N);

void calcula_mediasQ2 (gpointer key, RIDES *value, ARRAYS_RIDES *user_data);

int calculaMinimo(ARRAYS_RIDES *user_data);

void ordenaArray(ARRAYS_RIDES* array,int tamanho);

void printfArray(FILE *res, ARRAYS_RIDES *array,GHashTable* driver,int N);

RIDES_AM* createNewElement(RIDES *value);

void calculaAm(ARRAYS_RIDES *array);

#endif