#ifndef drivers
#define drivers

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct DRIVERS DRIVERS;

void free_driver (DRIVERS *value);

void atribui_drv(DRIVERS* drv2 ,int pos,char* token);

void novo(GHashTable* HashDrv, char *line);

char *procuraQ1(GHashTable* HashDrv, char *id, FILE *res);

int car_lookup (GHashTable *drivers, char *id);

char * lookupName(GHashTable* driver,char *str);

#endif