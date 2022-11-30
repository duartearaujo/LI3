#ifndef query3
#define query3

typedef struct ARRAY_USERS ARRAY_USERS;

ARRAY_USERS* createArrayUser(int N);

void guardaUser(gpointer key, User *user, ARRAY_USERS *array);

void Q3Print(FILE *res, ARRAY_USERS *array, int N);

int partition(ARRAY_USERS *array, int i, int j);

void QuickSort(ARRAY_USERS *array, int N);

void QSRecursion(ARRAY_USERS *array, int i, int j);

void swap1(ARRAY_USERS *array, int i, int t);

void freeArrayU(ARRAY_USERS *user);

#endif