#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/query2.h"


/*struct auxiliar usada para realizar a query 2*/
struct ARRAY_DRIVERS{
    int ordenado;
    int pos;   /*posição na qual queremos inserir o próximo driver*/
    DRIVERS **driver;   /*array de drivers*/
};

static ARRAY_DRIVERS *array = NULL;

/*função que inicializa a struct ARRAY_DRIVERS*/
void createArray(){   
    array = malloc(sizeof(ARRAY_DRIVERS));
    array->pos = 0;
    array->ordenado = 0;
    array->driver = NULL;
}


/*faz print dos valores da query 2*/
void printfArray(FILE *res,int N){
    int print = 0;
    for(int i = array->pos-1; i >= 0 && print < N ;i--){
        char *ac_st = getAccountStatusD(array->driver[i]);
        char *id = getIdD(array->driver[i]);
        char *name = getNameD(array->driver[i]);
        double avaliacao_media = getAvaliacaoMediaD(array->driver[i]);
        if(strcmp(ac_st,"inactive") != 0){
            fprintf(res,"%s;%s;%.3f\n",id,name,avaliacao_media);
            print++;
        }
        free(id);
        free(name);
        free(ac_st);
   }
}


/*função que vai ser aplicada a cada membro da hashtable (dos drivers)*/
void calcula_mediasQ2 (gpointer key, DRIVERS* driver, void *a){
    int count = getCountD(driver);
    double valor_atual = getValorAtualD(driver);
    double avaliacao_media = getAvaliacaoMediaD(driver);
    avaliacao_media = valor_atual / count;  /*calcula a avaliação média de cada driver*/
    calculaAvaliacaoMedia(driver,avaliacao_media);
    array->pos++;
    array->driver = (DRIVERS**) realloc(array->driver,array->pos * sizeof(DRIVERS*));
    array->driver[array->pos-1] = GetcontentD(driver);
}

/*função swap utilizada na ordenação do array presente na struct ARRAY_DRIVERS*/
void swap(DRIVERS** array, int a, int b){   
  DRIVERS *t = array[a];
  array[a] = array[b];
  array[b] = t;
}


/*função que ordena o array da struct ARRAY_DRIVERS e faz o desempate dos drivers caso a avaliação média seja a mesma*/
void ordenaArray(){   
   int i, j, m,r = 0;
   for (i = array->pos; i > 0; i--) {
   m = 0;
   for (j = 0; j < i; j++){
        double avaliacao_media = getAvaliacaoMediaD(array->driver[j]);
        double avaliacao_media2 = getAvaliacaoMediaD(array->driver[m]);
        char *mostRecentRide = getMostRecentRideD(array->driver[j]);
        char *mostRecentRide2 = getMostRecentRideD(array->driver[m]);
        char *id = getIdD(array->driver[j]);
        char *id2 = getIdD(array->driver[m]);
        if (avaliacao_media > avaliacao_media2) m = j;
        else if(avaliacao_media == avaliacao_media2){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
            if((r = compareDates(mostRecentRide,mostRecentRide2)) == 1) m = j;   /*compareDates = 1 -> primeira data é mais recente*/
            else if((r = compareDates(mostRecentRide,mostRecentRide2)) == 2){    /*compareDates = 2 -> as duas datas são iguais*/
                if(atoi(id) > atoi(id2)) m = j;  /*se as datas forem iguais então compara-se os id*/
            }
        }
    free(mostRecentRide);
    free(mostRecentRide2);
    free(id);
    free(id2);

   }
    swap(array->driver, i-1, m);
   }
   array->ordenado = 1;
}

int arrayOrdenado(){
    if(!array) return 0;
    return array->ordenado;
}

/*função que faz free da struct ARRAY_DRIVERS*/
void freeArray(){
    if(array){
        for(int i = 0; i < array->pos; i++){
            free_driver(array->driver[i]);
        }
        free(array->driver);
        free(array);
    }
}