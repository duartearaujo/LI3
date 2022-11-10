#ifndef drivers
#define drivers

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct DRIVERS DRIVERS;

void atribui_drv(DRIVERS* drv2 ,int pos,char* token);

void novo(GHashTable* HashDrv, char *line);

void procura(GHashTable* HashDrv);

#endif