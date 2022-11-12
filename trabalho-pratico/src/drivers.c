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
} DRIVERS;

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

void novo(GHashTable *HashDrv, char *line){
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    separa(line,drv2,3);
    g_hash_table_insert(HashDrv, drv2 -> id, drv2);
}

char *procuraQ1(GHashTable* HashDrv, char *id, FILE *res){
    DRIVERS *d = g_hash_table_lookup(HashDrv, id);
    char *name = d->name;
    char *gender = d->gender;
    printf ("%s;%s;%d;",name, gender, calculaIdade(d->birth));
    return d->car_class;
}