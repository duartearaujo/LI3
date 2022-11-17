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

void printvaloresQ1_2 (User *d, FILE *res) ;

void Q2Print(FILE *res, ARRAY_USERS *array, int N);

int partition(ARRAY_USERS *array, int i, int j);

void QuickSort(ARRAY_USERS *array, int N);

void QSRecursion(ARRAY_USERS *array, int i, int j);

void swap1(ARRAY_USERS *array, int i, int t);

#endif