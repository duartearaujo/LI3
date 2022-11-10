#ifndef rides
#define rides

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct RIDES RIDES;

void assignsData(RIDES* new_ride ,int pos ,char* token);

void newElement(GHashTable* hashRides, char *line);

void lookupRide(GHashTable* hashRides);

#endif
