#ifndef users_
#define users_

#include <glib.h>

typedef struct user User;

#include "query3.h"

void free_user(User *value);

void iniciaHashUsers (char *path);

void adicionaHashUsers (char *line);

void atribui (User* user, int pos, char *info);

int lookupUser (GHashTable *user, FILE *res, char *name);

void addToUser (User *user, char *distance, char *tip, int car_class , char *avaliation, char *date);

User* GetcontentU(User *u);

char *getNameU (User *u);

char *getGenderU (User *u);

int get_Idade_Conta_U(User* user);

char *getAccStatusU (User *u);

char *getDataU (User *u);

int getNViagensU (User *u);

double getTotalGastoU (User *u);

double getAccAvaliationU (User *u);

char *getUsername(User* user);

char *getLastRide(User* user);

int getDistance(User* user);

char *getAccSt(User* user);

User* lookup_users (char* key);

void foreach_users_Q3 ();

void hash_table_destroy_users ();



#endif