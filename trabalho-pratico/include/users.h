#ifndef users
#define users

#include <glib.h>

typedef struct user User;

typedef struct ARRAY_USERS ARRAY_USERS;

void free_user(User *value);

void criaHashUser (HASH *hash, char *line);

void atribui (User* user, int pos, char *info);

int lookupUser (GHashTable *user, FILE *res, char *name);

ARRAY_USERS* createArrayUser(int N);

void addToUser (User *user, char *distance, char *tip, int car_class , char *avaliation, char *date);

void guardaUser(gpointer key, User *user, ARRAY_USERS *array);

void Q3Print(FILE *res, ARRAY_USERS *array, int N);

int partition(ARRAY_USERS *array, int i, int j);

void QuickSort(ARRAY_USERS *array, int N);

void QSRecursion(ARRAY_USERS *array, int i, int j);

void swap1(ARRAY_USERS *array, int i, int t);

void freeArrayU(ARRAY_USERS *user);

User* GetcontentU(User *u);

char *getNameU (User *u);

char *getGenderU (User *u);

char *getAccStatusU (User *u);

char *getDataU (User *u);

int getNViagensU (User *u);

double getTotalGastoU (User *u);

double getAccAvaliationU (User *u);

#endif