#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/main.h"

#define DIA 9
#define MES 10
#define ANO 2022

int querie1(char *str){  /*verifica se na querie 1, apos o "1" que representa a querie que se pretende responder, se encontra um id ou um username*/
    int id = 0;
    if(str[1] >= 48 && str[1] <= 57) id = 1;
    return id;
}

int compareDates(char *str, char *string){  /*compara duas datas || return value == 1 se a primeira é mais recente que a segunda*/
    char *str_ = strdup(str);                                    /* return value == 0 se a primeira é mais antiga que a segunda*/
    char *str_2 = strdup(string);                                /* reutrn value == 2 se as datas são iguais*/
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
    else if(ano == ano2 && mes == mes2 && dia == dia2) r = 2;
    free(str_);
    free(str_2);
    return r;
}

void querieIdentifier(char **argv, HASH *hash, int n_querie) {  /*função usada para responder às queries, ou chamar as funções que resolvem as queries */
    int q = atoi (argv[0]);
    char filename [28 + n_querie];
    sprintf(filename, "Resultados/command%d_output.txt", n_querie);
    FILE *res = fopen(filename, "a");
    switch (q)  /*q == nº da query que queremos responder*/
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
        freeArray(array);
        break;
    }
    case 3: {
        ARRAY_USERS *array = createArrayUser(100000);
        g_hash_table_foreach(retornaHash(1,hash),(GHFunc)guardaUser, array);
        QuickSort(array, 100000);
        Q2Print(res, array, atoi(argv[1]));
    }
    default:
        break;
    }
    fclose (res);
    return;
}

int calculaIdade(char *str){  /*verifica que idade tem o user/driver(usando a data dada no enunciado "09/10/2022")*/
    int idade = 0;
    int dia = atoi(strsep(&str, "/"));
    int mes = atoi(strsep(&str, "/"));
    int ano = atoi(strsep(&str, "/"));
    if (mes < MES) idade = ANO - ano;
    else if (mes == MES) {
        if (dia <= DIA) idade = ANO - ano;
        else idade = ANO - ano - 1;
    }
    else idade = ANO - ano -1;
    return idade;
}