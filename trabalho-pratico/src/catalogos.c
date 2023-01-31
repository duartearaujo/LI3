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
    ordena_Q3();
    ordena_Q9();
    return 1;
}

void freeEstruturas(){
    hash_table_destroy_users ();
    hash_table_destroy_drivers ();
    destroyHashCidades ();
    hash_table_destroy_rides ();
    freeArray();
    freeArrayU();
    freeArrayQ9();
}