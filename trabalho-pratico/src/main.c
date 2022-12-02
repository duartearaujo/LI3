#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"

/*função main do projeto*/
int main(int argc, char **argv){  
    FILE *fp = NULL;
    if(argc < 2){
        fp = stdin;
    }
    else{
        iniciaHashUsers (argv[1]);
        iniciaHashDrivers (argv[1]);
        iniciaHashRides (argv[1]);
    }
    /*parse das queries*/
    fp = fopen (argv[2], "r");  /*abre o ficheiro com os testes(queries)*/
    parsequerie (fp);  /*parse das queries*/

    /*free das hashes e mais*/
    fclose (fp);
    g_hash_table_destroy (users);
    g_hash_table_destroy (drivers);
    g_hash_table_destroy (rides);
    return 0;
}
