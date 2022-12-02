#ifndef rides_
#define rides_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"

GHashTable* rides;

typedef struct RIDES RIDES;

void iniciaHashRides (char *path);

void free_ride (RIDES *value);

void assignsData(RIDES* new_ride ,int pos ,char* token);

void adicionaHashRides(char *line);

char *getcarR (RIDES *ride);

char *getdistanceR (RIDES *ride);

char *getcityR (RIDES *ride);

#endif