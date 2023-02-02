#ifndef q1
#define q1

#include <stdio.h>
#include "../include/drivers.h"
#include "../include/users.h"

int printvaloresQ1 (DRIVERS *d, FILE *res, int modo);

int printvaloresQ1_2 (User *u, FILE *res, int modo);

int query1Exe(FILE *res, int modo, char* argv);

#endif