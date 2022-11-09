#include <stdio.h>
#include <glib.h>

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

void atribui_drv(char *token, int pos, DRIVERS* drv2){
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
        break;
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

void separa_drv(char *str, DRIVERS* drv2){
    int pos = 1;
    char *token = strsep(&str, ";");
    while(token){
        atribui_drv(token, pos++, drv2);
        token = strsep(&str, ";");
    }
}

void novo(GHashTable *HashDrv, char *line){
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    separa_drv(line, drv2);
    g_hash_table_insert(HashDrv, drv2 -> id, drv2);
}

void procura(GHashTable* HashDrv){
    DRIVERS *d = g_hash_table_lookup(HashDrv, "000000000022");
    char *key = d -> name;
    printf("%s\n", key);
}