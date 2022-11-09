#ifndef rides
#define rides

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct RIDES RIDES;

void assignsData(char *token,int pos,RIDES* new_ride);

void separateData(char *str,RIDES* new_ride);

void newElement(GHashTable* hashRides, char *line);

void lookupRide(GHashTable* hashRides);

#endif
