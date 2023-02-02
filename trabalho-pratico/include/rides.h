#ifndef rides_
#define rides_

#include <stdio.h>
#include <stdlib.h>
#include <glib.h>


typedef struct RIDES RIDES;

typedef struct q8 q8;

typedef struct array_RIDES arrayRides;

q8* inicializa_dados_Q8();

void inicializaArrays ();

int iniciaEstruturasRides (char *path);

int assignsData(RIDES* new_ride ,int pos ,char* token);

void adicionaEstruturasRides(char *line);

char *getcityR (RIDES *ride);

char* getcityArrays (int pos);

char getcarR (RIDES *ride);

char getcarArrays (int pos);

int getdistanceR (RIDES *ride);

int getdistanceArrays (int pos);

int getPosQ8 (char gender);

int get_Idade_Conta_DriverQ8(int pos,char gender);

int get_Idade_Conta_UserQ8(int pos,char gender);

char *getUsernameQ8(int pos,char gender);

char *getIdDriverQ8(int pos,char gender);

char *getNomeDriverQ8(int pos,char gender);

char *getNomeUserQ8(int pos,char gender);

int getPosQ5Q6 ();

int getTempoDeVida(int pos);

char *getUsernameR (RIDES *ride);

char *getIdDriverR (RIDES *ride);

char *getIdR (RIDES *ride);

char *getDateR (RIDES *ride);

double getTip (RIDES *ride);

int getIdadeViagem (RIDES *ride);

char* getId_Q9 (int pos); 

char* getDate_Q9 (int pos);

char* getCity_Q9 (int pos);

int getDistance_Q9 (int pos);

double getTip_Q9 (int pos); 

int getIdadeViagem_Q9 (int pos);

int getposQ9 ();

int getposQ9 ();

int getposQ9 ();

void addQ9(RIDES *ride);

int ordenaQ5Q6(const void *p1, const void* p2);

void ordena_Q5Q6();

int desempate_Q8(const void *p1, const void* p2);

void ordena_Q8();

void ordena_Q9();

void free_ride (RIDES *value);

void freeQ8(q8* dados);

void freeArrays();

#endif