#ifndef query3
#define query3

#include "users.h"

typedef struct ARRAY_USERS ARRAY_USERS;

void createArrayUser();

int arrayOrdenadoU();

void guardaUser(gpointer key, User *user, void *a);

void Q3Print(FILE *res, int N);

int partition(int i, int j);

void QuickSort();

void QSRecursion(int i, int j);

void swap1(int i, int t);

void freeArrayU();

#endif