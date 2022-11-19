#include <stdio.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/queries.h"
#include "../include/drivers.h"

/*struct onde vão ser armazenados os dados do ficheiro drivers.csv*/
typedef struct DRIVERS{   
    char* id;
    char* name;
    char* birth;
    char* gender;
    char* car_class;
    char* plate;
    char* city;
    char* ac_cr;
    char* ac_st;
    int count;
    double valor_atual;
    double avaliacao_media;
    char *mostRecentRide;
    double total_auferido;
} DRIVERS;

/*struct auxiliar usada para realizar a query 2*/
struct ARRAY_DRIVERS{   
   int pos;   /*posição na qual queremos inserir o próximo driver*/
   DRIVERS **driver;   /*array de drivers*/
};

/*função responsável por dar free dos drivers, é usada para dar free da hashtable(dos drivers)*/
void free_driver (DRIVERS *value) {   
    free (value->id);
    free (value->name);
    free (value->birth);
    free (value->gender);
    free (value->car_class);
    free (value->plate);
    free (value->city);
    free (value->ac_cr);
    free (value->ac_st);
    free (value->mostRecentRide);
    free (value);
}

/*atribui cada token extraído ao respetivo campo da struct DRIVERS*/
void atribui_drv(DRIVERS* drv2 ,int pos,char* token){   
    char *str = strdup(token);
    switch(pos){
        case 1:
            drv2 -> id = str;
        break;
        case 2:
            drv2 -> name = str;
        break;
        case 3:
            drv2 -> birth = str;
        break;
        case 4:
            drv2 -> gender = str;
        break;
        case 5:
            drv2-> car_class = str;
        break;
        case 6:
            drv2 -> plate = str;
        break;
        case 7:
            drv2 -> city = str;
        break;
        case 8:
            drv2 -> ac_cr = str;
        break;
        case 9:
            drv2 -> ac_st = str;
        break;
    }
}

/*função que inicializa a struct ARRAY_DRIVERS*/
ARRAY_DRIVERS* createArray(int N){   
    ARRAY_DRIVERS *array = malloc(sizeof(ARRAY_DRIVERS));
    array->pos = 0;
    array->driver = malloc(sizeof(DRIVERS *) * N);
    return array;
}

/*função que inicializa cada driver*/
void novo(HASH* hash, char *line){   
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    separa(line,drv2,3);
    drv2->count = 0;
    drv2->valor_atual = 0;
    drv2->mostRecentRide = NULL;
    drv2-> total_auferido = 0;
    g_hash_table_insert(retornaHash(3,hash), drv2 -> id, drv2);  /*depois de todos os campos da struct estarem preenchidos insere o driver na hashtable*/
}

/* Função para fazer print dos valores do driver pedido na query 1 no ficheiro */
void printvaloresQ1 (DRIVERS *d, FILE *res) {  
    if (!strcmp (d->ac_st, "active")) {
    double avaliacao_media = d->valor_atual / d->count;   /*é calculada a avaliação média de cada driver*/
    fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",d->name, d->gender, calculaIdade(d->birth), avaliacao_media, d->count, d->total_auferido);
    }
}

/*atribiu um int consoante o tipo de carro do driver*/
int identifie_car_class (DRIVERS *driver) {
    if (!strcmp(driver->car_class,"basic")) return 0;
    else if (!strcmp(driver->car_class,"green")) return 1;
    else return 2;
}

/*adiciona a cada driver da hashtable(dos drivers) os valores dos rides que interessam para resolver a query 1 e 2*/
void addToDriver(DRIVERS *driver,char *score_driver, char *date, char *distance, char *tip){   
    int r = 0;
    if(!driver->mostRecentRide) driver->mostRecentRide = strdup(date);   /*compara as duas datas*/
    else if((r = compareDates(date,driver->mostRecentRide)) != 0){   /*se a primeira data for igual ou mais recente que a segunda*/
        char *temp = driver->mostRecentRide;
        driver->mostRecentRide = strdup (date);
        free (temp);
    }
    driver->count += 1;   /*incrementa o nºtotal de viajens*/
    driver->valor_atual += strtod(score_driver,NULL);   /*incrementa o score_driver à soma total de todos os score_driver(valor_atual)*/
    
    int identifier_car = identifie_car_class (driver); 
    
    switch (identifier_car) /*calcula os valores dependendo do int q identifica o tipo de carro*/
      {
         case 0:
            driver->total_auferido += strtod (tip,NULL) + strtod (distance, NULL) * 0.62 + 3.25;
            break;
         case 1:
            driver->total_auferido += strtod (tip,NULL) + strtod (distance, NULL) * 0.79 + 4;
            break;
         case 2:
            driver->total_auferido  += strtod (tip,NULL) + strtod (distance, NULL) * 0.94 + 5.20;
            break;
         default:
            break;
      }
}

/*faz print dos valores da query 2*/
void printfArray(FILE *res,ARRAY_DRIVERS * array,int N){  
    for(int i = 9999; i > 9999-N ;i--){
        fprintf(res,"%s;%s;%.3f\n",array->driver[i]->id,array->driver[i]->name,array->driver[i]->avaliacao_media);
   }
}

/*função que vai ser aplicada a cada membro da hashtable (dos drivers)*/
void calcula_mediasQ2 (gpointer key, DRIVERS* driver, ARRAY_DRIVERS* array){   
    driver->avaliacao_media = driver->valor_atual / driver->count;   /*calcula a avaliação média de cada driver*/
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
    if(strcmp(array->driver[j]->ac_st,"inactive") != 0){   /*se o driver estiver inactivo então não será ordenado(vai ser ignorado)*/
   if (array->driver[j]->avaliacao_media > array->driver[m]->avaliacao_media) m = j;
   else if(array->driver[j]->avaliacao_media == array->driver[m]->avaliacao_media){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
    if((r = compareDates(array->driver[j]->mostRecentRide,array->driver[m]->mostRecentRide)) == 1) m = j;   /*compareDates = 1 -> primeira data é mais recente*/
    else if((r = compareDates(array->driver[j]->mostRecentRide,array->driver[m]->mostRecentRide)) == 2){    /*compareDates = 2 -> as duas datas são iguais*/
        if(atoi(array->driver[j]->id) > atoi(array->driver[m]->id)) m = j;  /*se as datas forem iguais então compara-se os id*/
    }
   }
    }
   }
    swap(array->driver, i-1, m);
   }
}

/*função que faz free da struct ARRAY_DRIVERS*/
void freeArray(ARRAY_DRIVERS* array){
    free(array->driver);
    free(array);
}

DRIVERS* GetcontentD(DRIVERS *d) {
    DRIVERS *copy = malloc (sizeof (DRIVERS));  
    for (int pos = 1; pos <= 10; pos++) {
        switch (pos) {
            case 1:
                copy-> id = strdup (d->id);
                break;
            case 2:
                copy-> name = strdup (d->name);
                break;
            case 3:
                copy-> birth = strdup (d->birth);
                break;
            case 4:
                copy-> car_class= strdup (d->car_class);
                break;
            case 5:
                copy-> plate = strdup (d->plate);
                break;
            case 6:
                copy->city= strdup (d->city);
                break;
            case 7:
                copy-> ac_cr = strdup (d->ac_cr);
                break;
            case 8:
                copy-> ac_st = strdup (d->ac_st);
                break;
            case 9:
                copy->gender= strdup (d->gender);
                break;
            case 10:
                copy->mostRecentRide= strdup (d->mostRecentRide);
                break;
        }
    }

    copy->avaliacao_media = d->avaliacao_media;
    copy->count = d->count;
    copy->valor_atual = d->valor_atual;
    copy->total_auferido = d->total_auferido;
    return copy;
}