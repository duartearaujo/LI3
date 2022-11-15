#include <stdio.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/queries.h"

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
} DRIVERS;

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

void novo(HASH* hash, char *line){
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    separa(line,drv2,3);
    drv2->count = 0;
    drv2->valor_atual = 0;
    drv2->mostRecentRide = NULL;
    g_hash_table_insert(retornaHash(3,hash), drv2 -> id, drv2);
}

char *procuraQ1(GHashTable* HashDrv, char *id, FILE *res){
    DRIVERS *d = g_hash_table_lookup(HashDrv, id);
    if ( !strcmp (d->ac_st, "inactive") ) return NULL;
    char *name = d->name;
    char *gender = d->gender;
    fprintf (res,"%s;%s;%d;",name, gender, calculaIdade(d->birth));
    return d->car_class;
}

int car_lookup (GHashTable *drivers, char *id) {
    DRIVERS *d = g_hash_table_lookup (drivers, id);
    if (!strcmp(d->car_class,"basic")) return 0;     // atribiu um int consoante o tipo de carro do driver
    else if (!strcmp(d->car_class,"green")) return 1;
    else return 2;
}

char * lookupName(GHashTable* driver,char *str){
    DRIVERS* drive = g_hash_table_lookup(driver,str);
    char *nome = drive->name;
    return nome;
}

void addToDriver(DRIVERS *driver,char *score_driver, char *date){
    char *str = strdup(date);
    if(!driver->mostRecentRide) driver->mostRecentRide = str;
    else if(compareDates(date,str)) driver->mostRecentRide = str;
    driver->count += 1;
    driver->valor_atual += strtod(score_driver,NULL);
}