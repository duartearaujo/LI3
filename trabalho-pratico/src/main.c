#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query2.h"
#include "../include/query9.h"
#include "../include/interactive.h"

/*função main do projeto*/
int main(int argc, char **argv){  
    FILE *fp = NULL;
    if(argc < 2){
        int i = iniciaI();
        if (i) parsequeryI();
    }
    else{
        clock_t t = clock();
        int u = iniciaHashUsers (argv[1]);
        int d = iniciaHashDrivers (argv[1]);
        inicializaQ9();
        iniciaHashCidades ();
        int r = iniciaHashRides (argv[1]);
        if (!(u && d && r)) return 1;

        t = clock () -t;
        printf ("Load Time: %f\n", ((float)t)/CLOCKS_PER_SEC);
         /*parse das queries*/
        fp = fopen (argv[2], "r");  /*abre o ficheiro com os testes(queries)*/
        parsequerie (fp);  /*parse das queries*/

        /*free das hashes e mais*/
        fclose (fp);
    }
    hash_table_destroy_users ();
    hash_table_destroy_drivers ();
    destroyHashCidades ();
    hash_table_destroy_rides ();
    freeArray();
    freeArrayU();
    freeArvoreQ9();
    free_Arrays_Q8();
    return 0;
}
