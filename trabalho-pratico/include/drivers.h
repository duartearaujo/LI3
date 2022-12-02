#ifndef drivers_
#define drivers_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>

GHashTable* drivers;

typedef struct DRIVERS DRIVERS;

void free_driver (DRIVERS *value);

void iniciaHashDrivers (char *path);

void adicionaHashDrivers(char *line);

void atribui_drv(DRIVERS* drv2 ,int pos,char* token);

int car_lookup (GHashTable *drivers, char *id);

void addToDriver(DRIVERS *driver,char *score_driver, char *date, char *distance, char *tip);

int identifie_car_class (DRIVERS *driver);

int identifie_car_class_char (char *car_class);

DRIVERS * GetcontentD(DRIVERS *d); 

char *getcarD (DRIVERS *d);

char *getIdD(DRIVERS *d);

char *getNameD(DRIVERS *d);

double getAvaliacaoMediaD(DRIVERS *d);

double getValorAtualD(DRIVERS *d);

int getCountD(DRIVERS *d);

char *getAccountStatusD(DRIVERS *d);

char *getMostRecentRideD(DRIVERS *d);

void calculaAvaliacaoMedia(DRIVERS *d,double avaliacao_media);

char *getGenderD(DRIVERS *d);

char *getBirthD(DRIVERS *d);

double getTotalAuferido (DRIVERS *d);

#endif