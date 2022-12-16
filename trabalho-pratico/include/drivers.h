#ifndef drivers_
#define drivers_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

typedef struct avaliacao_por_cidade AvC;

typedef struct DRIVERS DRIVERS;

typedef struct ARRAY_DRIVERS ARRAY_DRIVERS;

#include "query2.h"

void free_driver (DRIVERS *value);

void iniciaHashDrivers (char *path);

void adicionaHashDrivers(char *line);

void atribui_drv(DRIVERS* drv2 ,int pos,char* token);

int car_lookup (GHashTable *drivers, char *id);

void addToDriver(DRIVERS *driver,char *score_driver, char *date, int distance, char *tip, char *city);

int identifie_car_class (DRIVERS *driver);

int identifie_car_class_char (char car_class);

DRIVERS * GetcontentD(DRIVERS *d); 

AvC* getcontentAvC (AvC *a);

void calcula_avaliacao_media_AvC (AvC *avaliacao);

char getcarD (DRIVERS *d);

char *getIdD(DRIVERS *d);

char *getNameD(DRIVERS *d);

double getAvaliacaoMediaD(DRIVERS *d);

double getValorAtualD(DRIVERS *d);

int getCountD(DRIVERS *d);

int get_Idade_Conta_D(DRIVERS *d);

char getAccountStatusD(DRIVERS *d);

char *getMostRecentRideD(DRIVERS *d);

void calculaAvaliacaoMedia(DRIVERS *d,double avaliacao_media);

char getGenderD(DRIVERS *d);

char *getBirthD(DRIVERS *d);

double getTotalAuferido (DRIVERS *d);

double getAvaliacaoMediaAvC (AvC *a);

char* getIdAvC (AvC *a);

char* getNameAvC (AvC *a);

DRIVERS* lookup_drivers (char* key);

AvC* lookup_AvC (DRIVERS *driver, char *city);

size_t getsizeAvC ();

void foreach_drivers_Q7 ();

void hash_table_destroy_drivers ();

void free_avaliacao_por_cidade (AvC *value);

void createArray();

void calcula_mediasQ2 (gpointer key, DRIVERS* driver, void *a);

void foreach_drivers_Q2 ();

void ordena_Q2();

int arrayOrdenado();

DRIVERS* getElement_Q2(int index);

void freeArray();

void adicionaArrayQ7(AvC *avaliacao_cidade);

void ordenaQ7 ();

void free_Q7 ();

int getPosQ7 ();

AvC *getarrayQ7pos (int i);

int isactive (AvC *driver); 

#endif