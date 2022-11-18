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

void assignsData(RIDES* new_ride ,int pos ,char* token);

void newElement(HASH *hash,char *line);

#endif