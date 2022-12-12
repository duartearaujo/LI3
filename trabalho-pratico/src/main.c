#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/query2.h"

/*função main do projeto*/
int main(int argc, char **argv){  
    FILE *fp = NULL;
    if(argc < 2){
        fp = stdin;
    }
    else{
        clock_t t = clock();
        iniciaHashUsers (argv[1]);
        iniciaHashDrivers (argv[1]);
        iniciaHashRides (argv[1]);
        t = clock () -t;
        printf ("Load Time: %f\n", ((float)t)/CLOCKS_PER_SEC);
    }
    /*parse das queries*/
    fp = fopen (argv[2], "r");  /*abre o ficheiro com os testes(queries)*/
    parsequerie (fp);  /*parse das queries*/

    /*free das hashes e mais*/
    fclose (fp);
    hash_table_destroy_users ();
    hash_table_destroy_drivers ();
    hash_table_destroy_rides ();
    freeArray();
    freeArrayU();
    freeArrayQ9();
    return 0;
}
