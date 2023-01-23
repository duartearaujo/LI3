#ifndef drivers_
#define drivers_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct DRIVERS DRIVERS;

typedef struct ARRAY_DRIVERS ARRAY_DRIVERS;

#include "query2.h"

void free_driver (DRIVERS *value);

int iniciaHashDrivers (char *path);

void adicionaHashDrivers(char *line);

int atribui_drv(DRIVERS* drv2 ,int pos,char* token);

void addToDriver(DRIVERS *driver,int score_driver, char *date, int distance, char *tip);

int identifie_car_class (DRIVERS *driver);

int identifie_car_class_char (char car_class);

DRIVERS * GetcontentD(DRIVERS *d); 

char getcarD (DRIVERS *d);

char *getIdD(DRIVERS *d);

char *getNameD(DRIVERS *d);

double getAvaliacaoMediaD(DRIVERS *d);

int getValorAtualD(DRIVERS *d);

int getCountD(DRIVERS *d);

int get_Idade_Conta_D(DRIVERS *d);

char getAccountStatusD(DRIVERS *d);

char *getMostRecentRideD(DRIVERS *d);

char getGenderD(DRIVERS *d);

char *getBirthD(DRIVERS *d);

double getTotalAuferido (DRIVERS *d);

DRIVERS* lookup_drivers (char* key);

void hash_table_destroy_drivers ();

void createArray();

void calcula_mediasQ2 (gpointer key, DRIVERS* driver, void *a);

void foreach_drivers_Q2 ();

void ordena_Q2();

int arrayOrdenado();

DRIVERS* getElement_Q2(int index);

void freeArray();

int verifica_ativo (char *id);

#endif