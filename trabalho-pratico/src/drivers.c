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

/*atribiu um int consoante o tipo de carro do driver*/
int identifie_car_class (DRIVERS *driver) {
    if (!strcmp(driver->car_class,"basic")) return 0;
    else if (!strcmp(driver->car_class,"green")) return 1;
    else return 2;
}

int identifie_car_class_char (char *car_class) {
    if (!strcmp(car_class,"basic")) return 0;
    else if (!strcmp(car_class,"green")) return 1;
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

char *getcarD (DRIVERS *d) {
    return strdup (d->car_class);
}

char *getIdD(DRIVERS *d){
    return strdup (d->id);
}

char *getNameD(DRIVERS *d){
    return strdup (d->name);
}

double getAvaliacaoMediaD(DRIVERS *d){
    return d->avaliacao_media;
}

double getValorAtualD(DRIVERS *d){
    return d->valor_atual;
}

int getCountD(DRIVERS *d){
    return d->count;
}

char *getAccountStatusD(DRIVERS *d){
    return strdup (d->ac_st);
}

char *getMostRecentRideD(DRIVERS *d){
    return strdup (d->mostRecentRide);
}

void calculaAvaliacaoMedia(DRIVERS *d,double avaliacao_media){
    d->avaliacao_media = avaliacao_media;
}

char *getGenderD(DRIVERS *d){
    return strdup (d->gender);
}

char *getBirthD(DRIVERS *d){
    return strdup (d->birth);
}

double getTotalAuferido (DRIVERS *d) {
    return d->total_auferido;
}