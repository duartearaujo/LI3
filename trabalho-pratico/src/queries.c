#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/main.h"


int querie1(char *str){
    int id = 0;
    if(str[1] >= 48 && str[1] <= 57) id = 1;
    return id;
}

int compareDates(char *str, char *string){
    char *str_ = strdup(str);
    char *str_2 = strdup(string);
    int r = 0;
    int dia = atoi(strsep(&str_,"/"));
    int mes = atoi(strsep(&str_,"/"));
    int ano = atoi(strsep(&str_,"/"));
    int dia2 = atoi(strsep(&str_2,"/"));
    int mes2 = atoi(strsep(&str_2,"/"));
    int ano2 = atoi(strsep(&str_2,"/"));
    if(ano > ano2) r = 1;
    else if(ano == ano2 && mes > mes2) r = 1;
    else if(ano == ano2 && mes == mes2 && dia > dia2) r = 1;
    free(str_);
    free(str_2);
    return r;
}

void querieIdentifier(char **argv, HASH *hash) {
    int q = atoi (argv[0]);
    FILE *res = fopen ("Resultados/commandoutput1.txt","a");
    switch (q)
    {
    case 1: {
        if(querie1(argv[1])) {
            DRIVERS *d = g_hash_table_lookup (retornaHash (3,hash), argv[1]);
            printvaloresQ1 (d, res);
        }
        else {
            User *u = g_hash_table_lookup (retornaHash (1,hash), argv[1]);
            printvaloresQ1_2 (u, res);
        }
        break;
    }
    case 2: {
        ARRAY_DRIVERS *array = createArray(10000);
        g_hash_table_foreach(retornaHash(3,hash),(GHFunc)calcula_mediasQ2,array);
        ordenaArray(array,10000-atoi(argv[1]));
        printfArray(res,array,atoi(argv[1]));
        break;
    }
    default:
        break;
    }
    fclose (res);
    return;
}

int calculaIdade(char *str){
    int idade = 0;
    int dia = atoi(strsep(&str, "/"));
    int mes = atoi(strsep(&str, "/"));
    int ano = atoi(strsep(&str, "/"));
    if (mes < 10) idade = 2022 - ano;
    else if (mes == 10) {
        if (dia <= 9) idade = 2022 - ano;
        else idade = 2022 - ano - 1;
    }
    else idade = 2022 - ano -1;
    return idade;
}