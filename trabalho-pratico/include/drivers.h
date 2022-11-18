#ifndef drivers
#define drivers

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct DRIVERS DRIVERS;

typedef struct ARRAY_DRIVERS ARRAY_DRIVERS;

void free_driver (DRIVERS *value);

void atribui_drv(DRIVERS* drv2 ,int pos,char* token);

void novo(HASH* hash, char *line);

void printvaloresQ1 (DRIVERS *d, FILE *res) ;

int car_lookup (GHashTable *drivers, char *id);

void addToDriver(DRIVERS *driver,char *score_driver, char *date, char *distance, char *tip);

int identifie_car_class (DRIVERS *driver);

void calcula_mediasQ2 (gpointer key, DRIVERS* driver, ARRAY_DRIVERS* array);

ARRAY_DRIVERS* createArray(int N);

void ordenaArray(ARRAY_DRIVERS* array,int tamanho);

void printfArray(FILE *res,ARRAY_DRIVERS * array,int N);

void freeArray(ARRAY_DRIVERS* array);

#endif