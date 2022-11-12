#ifndef rides
#define rides

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"

typedef struct RIDES RIDES;

void assignsData(RIDES* new_ride ,int pos ,char* token);

void newElement(GHashTable* hashRides, char *line);

void lookupRide(GHashTable* hashRides);

void calcula_mediasQ1 (gpointer key, RIDES *value, double  *user_data);

#endif
