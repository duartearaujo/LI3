#ifndef users_
#define users_

#include <glib.h>

typedef struct user User;

typedef struct ARRAY_USERS ARRAY_USERS;

#include "query3.h"

void free_user(User *value);

int iniciaHashUsers (char *path);

void adicionaHashUsers (char *line);

int atribui (User* user, int pos, char *info);

int lookupUser (GHashTable *user, FILE *res, char *name);

void addToUser (User *user, int distance, char *tip, int car_class , int avaliation, char *date);

User* GetcontentU(User *u);

char *getNameU (User *u);

char getGenderU (User *u);

int get_Idade_Conta_U(User* user);

char getAccStatusU (User *u);

char *getDataU (User *u);

int getNViagensU (User *u);

double getTotalGastoU (User *u);

int getAccAvaliationU (User *u);

char *getUsername(User* user);

char *getLastRide(User* user);

int getDistance(User* user);

User* lookup_users (char* key);

void createArrayUser();

int arrayOrdenadoU();

void guardaUser(User *user);

void ordena_Q3();

User* getElement_Q3(int i);

void freeArrayU();

void hash_table_destroy_users ();



#endif