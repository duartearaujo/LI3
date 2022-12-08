#ifndef rides_
#define rides_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


typedef struct RIDES RIDES;

#include "query4.h"
#include "query5.h"
#include "query6.h"
#include "query8.h"

void iniciaHashRides (char *path);

void free_ride (RIDES *value);

void assignsData(RIDES* new_ride ,int pos ,char* token);

void adicionaHashRides(char *line);

char *getcarR (RIDES *ride);

char *getdistanceR (RIDES *ride);

char *getUsernameR (RIDES *ride);

char *getIdDriverR (RIDES *ride);

char *getIdR (RIDES *ride);

char *getDateR (RIDES *ride);

char *getcityR (RIDES *ride);

RIDES* lookup_rides (char* key);

void foreach_rides_Q4 (Q4 *preco);

void foreach_rides_Q5 (Q5 *preco);

void foreach_rides_Q6 (Q6 *q);

void foreach_rides_Q8 ();

void hash_table_destroy_rides ();

#endif