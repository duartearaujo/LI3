#ifndef rides_
#define rides_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


typedef struct RIDES RIDES;

typedef struct array_RIDES arrayRides;

#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "query8.h"
#include "query9.h"

int iniciaHashRides (char *path);

void inicializaArrays ();

void free_ride (RIDES *value);

int assignsData(RIDES* new_ride ,int pos ,char* token);

void adicionaHashRides(char *line);

char getcarR (RIDES *ride);

char getcarArrays (int pos);

int getdistanceR (RIDES *ride);

int getdistanceArrays (int pos);

char* getcityArrays (int pos);

int getPosQ5Q6 ();

char *getUsernameR (RIDES *ride);

char *getIdDriverR (RIDES *ride);

char *getIdR (RIDES *ride);

char *getDateR (RIDES *ride);

char *getcityR (RIDES *ride);

double getTip (RIDES *ride);

RIDES* lookup_rides (char* key);

char* getId_Q9 (int pos); 

char* getDate_Q9 (int pos);

char* getCity_Q9 (int pos);

int getDistance_Q9 (int pos);

double getTip_Q9 (int pos); 

int getIdadeViagem_Q9 (int pos);

int getposQ9 ();

int getIdadeViagem (RIDES *ride);

int getposQ9 ();

int getIdadeViagem (RIDES *ride);

int getposQ9 ();

void foreach_rides_Q8 ();

void hash_table_destroy_rides ();

void addQ9(RIDES *ride);

void ordena_Q5Q6();

void ordena_Q9();

int getTempoDeVida(int pos);

void freeArrays();

#endif