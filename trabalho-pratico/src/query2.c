#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/interactive.h"
#include "../include/datas.h"

/* Função reponsável pelo desempate(método de ordenação) do array da query 2. O método de ordenação utilizado é o que se encontra definido no enunciado do
projeto.
*/
int desempate_Q2(const void *p1, const void* p2){
    DRIVERS *driver_1 = GetcontentD(*((DRIVERS**) p1));
    DRIVERS *driver_2 = GetcontentD(*((DRIVERS**) p2));
    int result = 1;
    double avaliacao_media = getAvaliacaoMediaD(driver_1);
    double avaliacao_media2 = getAvaliacaoMediaD(driver_2);
    char *mostRecentRide = getMostRecentRideD(driver_1);
    char *mostRecentRide2 = getMostRecentRideD(driver_2);
    int verificacao = compareDates(mostRecentRide,mostRecentRide2);
    char *id = getIdD(driver_1);
    char *id2 = getIdD(driver_2);
    if (avaliacao_media > avaliacao_media2) result = -1;
    else if(avaliacao_media == avaliacao_media2){   /*desempate dos drivers(se a avaliação média for igual) -> verificar as datas*/
        if(verificacao == 1) result = -1;   /*compareDates = 1 -> primeira data é mais recente*/
        else if(verificacao == 2){    /*compareDates = 2 -> as duas datas são iguais*/
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

/* Função que percorre o array criado durante a query(o array só é criado na primeira vez que a query 2 é chamada, todas as queries 2 seguintes utilizam o 
mesmo array) e faz print dos valores pretendidos(o print tem a seguinte forma: id_driver,nome_driver,avaliacao_media). Tal como se verifica em todas as que-
ries o local onde o print é realizado depende do modo em que o utilizador se encontra,modo interativo -> terminal || modo batch -> ficheiro da pasta Resul-
tados.
*/
int printfArray(FILE *res, int N, int modo){
    int print = 0, i=0,j=0;
    char line[256] = {0};
    while (i< N){
        DRIVERS *driver = getElement_Q2(j);
        char ac_st = getAccountStatusD(driver);
        char *id = getIdD(driver);
        char *name = getNameD(driver);
        double avaliacao_media = getAvaliacaoMediaD(driver);
        if(ac_st == 'a'){  /*Verifica se o driver está ativo ou inativo, se tiver inativo não se faz print dos valores do driver.*/
            if (modo == 0)
                fprintf(res,"%s;%s;%.3f\n",id,name,avaliacao_media);  /*Modo Batch.*/
            else{
                sprintf(line, "\t%s;%s;%.3f",id,name,avaliacao_media);  /*Modo Interativo.*/
                if (!copia (strdup (line))) {
                    free (name);
                    free (id);
                    return 0;
                }
            }
            print++;
            i++;
        }
        free(id);
        free(name);
        free_driver(driver);
        j++;
   }
   return 1;
}

/* Responsável por chamar todas as funções que permitem a execução da query 2.*/
int query2Exe(FILE *res,int modo, char *argv){
    int r = 1;
    if (atoi (argv)) {
        if(!arrayOrdenado()){
            createArray();
            foreach_drivers_Q2 ();
            ordena_Q2();
        }
        r = printfArray(res,atoi(argv),modo);
    }
    return r;
}