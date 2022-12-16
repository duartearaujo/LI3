#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/query2.h"


/*faz print dos valores da query 2*/
void printfArray(FILE *res, int N){
    int print = 0, i=0,j=0;
    while (i< N){
        DRIVERS *driver = getElement_Q2(j);
        char ac_st = getAccountStatusD(driver);
        char *id = getIdD(driver);
        char *name = getNameD(driver);
        double avaliacao_media = getAvaliacaoMediaD(driver);
        if(ac_st == 'a'){
            fprintf(res,"%s;%s;%.3f\n",id,name,avaliacao_media);
            print++;
            i++;
        }
        free(id);
        free(name);
        free_driver(driver);
        j++;
   }
}