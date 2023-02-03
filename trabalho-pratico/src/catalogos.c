#include <stdio.h>
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query2.h"
#include "../include/query9.h"

/* Função usada para chamar todas aquelas que são reponsáveis por inicializar as estruturas que serão utilizadas ao longo do projeto e, em alguns casos,
organizar as mesmas.*/
int iniciaHashTables(char *argv){
    int u = iniciaHashUsers (argv);
    int d = iniciaHashDrivers (argv);
    inicializaArrays();
    iniciaHashCidades();
    int r = iniciaEstruturasRides (argv);
    if (!(u && d && r)) return 0;
    ordena_Q3();
    ordena_Q5Q6();
    ordena_Q8();
    ordena_Q9();
    return 1;
}

/* Função encarregada de chamar todas aquelas que têm como objetivo destruir(fazer free) as estruturas criadas para a execução do projeto.*/
void freeEstruturas(){
    hash_table_destroy_users ();
    hash_table_destroy_drivers ();
    destroyHashCidades ();
    freeArray();
    freeArrayU();
    freeArrays();
}