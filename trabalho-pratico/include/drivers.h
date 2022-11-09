#ifndef drivers
#define drivers

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct DRIVERS DRIVERS;

void atribui_drv(char *token, int pos, DRIVERS* drv2);

void separa_drv(char *str, DRIVERS* drv2);

void novo(GHashTable* HashDrv, char *line);

void procura(GHashTable* HashDrv);

#endif