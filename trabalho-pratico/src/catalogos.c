#include <stdio.h>
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query2.h"
#include "../include/query9.h"

int iniciaHashTables(char *argv){
    int u = iniciaHashUsers (argv);
    int d = iniciaHashDrivers (argv);
    inicializaQ9();
    iniciaHashCidades();
    int r = iniciaHashRides (argv);
    if (!(u && d && r)) return 0;
    ordena_Q9();
    return 1;
}