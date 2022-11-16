#ifndef rides
#define rides

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/main.h"

typedef struct RIDES RIDES;

typedef struct Q1USER Q1USER;

void free_ride (RIDES *value);

Q1USER *inicializaQ1 (HASH *hash, char *argv);

void free_struct_Q1 (Q1USER *valores);

void assignsData(RIDES* new_ride ,int pos ,char* token);

void newElement(HASH *hash,char *line);

void lookupRide(GHashTable* hashRides);

void calcula_mediasQ1 (gpointer key, RIDES *value, double  *user_data);

void calcula_mediasQ1_2 (gpointer key, RIDES *value, Q1USER *user_data); 

void printQ1 (Q1USER *valores, FILE *res);

#endif