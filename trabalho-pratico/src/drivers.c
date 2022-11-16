#include <stdio.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/queries.h"
#include "../include/drivers.h"

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

struct ARRAY_DRIVERS{
   int pos;
   DRIVERS **driver;
};

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

ARRAY_DRIVERS* createArray(int N){
    ARRAY_DRIVERS *array = malloc(sizeof(ARRAY_DRIVERS));
    array->pos = 0;
    array->driver = malloc(sizeof(DRIVERS) * N);
    return array;
}

void novo(HASH* hash, char *line){
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    separa(line,drv2,3);
    drv2->count = 0;
    drv2->valor_atual = 0;
    drv2->mostRecentRide = NULL;
    drv2-> total_auferido = 0;
    g_hash_table_insert(retornaHash(3,hash), drv2 -> id, drv2);
}

void printvaloresQ1 (DRIVERS *d, FILE *res) {
    if (!strcmp (d->ac_st, "active")) {
    double avaliacao_media = d->valor_atual / d->count;
    fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",d->name, d->gender, calculaIdade(d->birth), avaliacao_media, d->count, d->total_auferido);
    }
}

char * lookupName(GHashTable* driver,char *str){
    DRIVERS* drive = g_hash_table_lookup(driver,str);
    char *nome = drive->name;
    return nome;
}

int identifie_car_class (DRIVERS *driver) {
    if (!strcmp(driver->car_class,"basic")) return 0;     // atribiu um int consoante o tipo de carro do driver
    else if (!strcmp(driver->car_class,"green")) return 1;
    else return 2;
}

void addToDriver(DRIVERS *driver,char *score_driver, char *date, char *distance, char *tip){
    char *str = strdup(date);
    if(!driver->mostRecentRide) driver->mostRecentRide = str;
    else if(compareDates(date,str)) driver->mostRecentRide = str;
    driver->count += 1;
    driver->valor_atual += strtod(score_driver,NULL);
    
    int identifier_car = identifie_car_class (driver); 
    
    switch (identifier_car) // calcula os valores dependendo do int q identifica o tipo de carro.
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

void printfArray(FILE *res,ARRAY_DRIVERS * array,int N){
    for(int i = 9999; i > 9999-N ;i--){
        fprintf(res,"%s;%s;%.3f\n",array->driver[i]->id,array->driver[i]->name,array->driver[i]->avaliacao_media);
   }
}

void calcula_mediasQ2 (gpointer key, DRIVERS* driver, ARRAY_DRIVERS* array){
    driver->avaliacao_media = driver->valor_atual / driver->count;
    array->driver[array->pos] = driver;
    array->pos++;
}

void swap(DRIVERS** array, int a, int b){
  DRIVERS *t = array[a];
  array[a] = array[b];
  array[b] = t;
}

void ordenaArray(ARRAY_DRIVERS* array,int N){
   int i, j, m;
   for (i = 10000; i > N; i--) {
   m = 0;
   for (j = 0; j < i; j++)
   if (array->driver[j]->avaliacao_media > array->driver[m]->avaliacao_media) m = j;
      swap(array->driver, i-1, m);
   }
}