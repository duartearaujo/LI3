#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include <time.h>
#include <curses.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query2.h"
#include "../include/query9.h"
#include "../include/interactive.h"
#include "../include/catalogos.h"

/*função main do projeto*/
int main(int argc, char **argv){  
    FILE *fp = NULL;
    if(argc < 2){
        main_I();
    }
    else{
        clock_t t = clock();
        if(!iniciaHashTables(argv[1])) return 1;
        t = clock () -t;
        printf ("Load Time: %f\n", ((float)t)/CLOCKS_PER_SEC);
         /*parse das queries*/
        fp = fopen (argv[2], "r");  /*abre o ficheiro com os testes(queries)*/
        parsequerie (fp);  /*parse das queries*/

        /*free das hashes e mais*/
        fclose (fp);
        freeEstruturas();
    }
    return 0;
}
