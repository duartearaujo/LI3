#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/main.h"
#include "../include/queries.h"
#include "../include/query2.h"


/*struct auxiliar usada para realizar a query 2*/
struct ARRAY_DRIVERS{   
   int pos;   /*posição na qual queremos inserir o próximo driver*/
   DRIVERS **driver;   /*array de drivers*/
};


/*função que inicializa a struct ARRAY_DRIVERS*/
ARRAY_DRIVERS* createArray(int N){   
    ARRAY_DRIVERS *array = malloc(sizeof(ARRAY_DRIVERS));
    array->pos = 0;
    array->driver = malloc(sizeof(DRIVERS *) * N);
    return array;
}


/*faz print dos valores da query 2*/
void printfArray(FILE *res,ARRAY_DRIVERS * array,int N){ 
    for(int i = 9999; i > 9999-N ;i--){
        char *id = getIdD(array->driver[i]);
        char *name = getNameD(array->driver[i]);
        double avaliacao_media = getAvaliacaoMediaD(array->driver[i]);
        fprintf(res,"%s;%s;%.3f\n",id,name,avaliacao_media);
        free(id);
        free(name);
   }
}


/*função que vai ser aplicada a cada membro da hashtable (dos drivers)*/
void calcula_mediasQ2 (gpointer key, DRIVERS* driver, ARRAY_DRIVERS* array){
    int count = getCountD(driver);
    double valor_atual = getValorAtualD(driver);
    double avaliacao_media = getAvaliacaoMediaD(driver);
    avaliacao_media = valor_atual / count;  /*calcula a avaliação média de cada driver*/
    calculaAvaliacaoMedia(driver,avaliacao_media);
    array->driver[array->pos] = driver;
    array->pos++;
}

/*função swap utilizada na ordenação do array presente na struct ARRAY_DRIVERS*/
void swap(DRIVERS** array, int a, int b){   
  DRIVERS *t = array[a];
  array[a] = array[b];
  array[b] = t;
}


/*função que ordena o array da struct ARRAY_DRIVERS e faz o desempate dos drivers caso a avaliação média seja a mesma*/
void ordenaArray(ARRAY_DRIVERS* array,int N){   
   int i, j, m,r = 0;
   for (i = 10000; i > 10000-N; i--) {
   m = 0;
   for (j = 0; j < i; j++){
        char *ac_st = getAccountStatusD(array->driver[j]);
        double avaliacao_media = getAvaliacaoMediaD(array->driver[j]);
        double avaliacao_media2 = getAvaliacaoMediaD(array->driver[m]);
        char *mostRecentRide = getMostRecentRideD(array->driver[j]);
        char *mostRecentRide2 = getMostRecentRideD(array->driver[m]);
        char *id = getIdD(array->driver[j]);
        char *id2 = getIdD(array->driver[m]);
        if(strcmp(ac_st,"inactive") != 0){   /*se o driver estiver inactivo então não será ordenado(vai ser ignorado)*/
            if (avaliacao_media > avaliacao_media2) m = j;
            else if(avaliacao_media == avaliacao_media2){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
                if((r = compareDates(mostRecentRide,mostRecentRide2)) == 1) m = j;   /*compareDates = 1 -> primeira data é mais recente*/
                else if((r = compareDates(mostRecentRide,mostRecentRide2)) == 2){    /*compareDates = 2 -> as duas datas são iguais*/
                    if(atoi(id) > atoi(id2)) m = j;  /*se as datas forem iguais então compara-se os id*/
                }
            }
        }
    free(ac_st);
    free(mostRecentRide);
    free(mostRecentRide2);
    free(id);
    free(id2);

   }
    swap(array->driver, i-1, m);
   }
}


/*função que faz free da struct ARRAY_DRIVERS*/
void freeArray(ARRAY_DRIVERS* array){
    free(array->driver);
    free(array);
}