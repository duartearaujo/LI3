#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/query2.h"


int desempate_Q2(const void *p1, const void* p2){
    DRIVERS *driver_1 = GetcontentD(*((DRIVERS**) p1));
    DRIVERS *driver_2 = GetcontentD(*((DRIVERS**) p2));
    int result = 1;
    double avaliacao_media = getAvaliacaoMediaD(driver_1);
    double avaliacao_media2 = getAvaliacaoMediaD(driver_2);
    char *mostRecentRide = getMostRecentRideD(driver_1);
    char *mostRecentRide2 = getMostRecentRideD(driver_2);
    char *id = getIdD(driver_1);
    char *id2 = getIdD(driver_2);
    if (avaliacao_media > avaliacao_media2) result = -1;
    else if(avaliacao_media == avaliacao_media2){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
        if(compareDates(mostRecentRide,mostRecentRide2) == 1) result = -1;   /*compareDates = 1 -> primeira data é mais recente*/
        else if(compareDates(mostRecentRide,mostRecentRide2) == 2){    /*compareDates = 2 -> as duas datas são iguais*/
            if(atoi(id) < atoi(id2)) result = -1;  /*se as datas forem iguais então compara-se os id*/
        }
    }
    free(mostRecentRide);
    free(mostRecentRide2);
    free(id);
    free(id2);
    free_driver(driver_1);
    free_driver(driver_2);
    return result;
}


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