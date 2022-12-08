#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query2.h"
#include "../include/query3.h"
#include "../include/query4.h"
#include "../include/query1.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"

#define DIA 9
#define MES 10
#define ANO 2022

/*Função para identificar se o input recebido da query 1 é um id(driver) ou um username (user)*/
int querie1(char *str){  
    int id = 0;
    if(str[1] >= 48 && str[1] <= 57) id = 1;
    return id;
}

/*compara duas datas || return value == 1 se a primeira é mais recente que a segunda
return value == 0 se a primeira é mais antiga que a segunda
return value == 2 se as datas são iguais */
int compareDates(char *str, char *string){  
    char *str_ = strdup(str);                                    
    char *str_2 = strdup(string);  
    char *temp = str_;
    char *temp2 = str_2;                         
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
    free(temp);
    free(temp2);
    return r;
}

/*função usada para responder às queries, ou chamar as funções que resolvem as queries */
void querieIdentifier(char **argv, int n_querie) {  
    int q = atoi (argv[0]);
    char filename [29 + n_querie];
    sprintf(filename, "Resultados/command%d_output.txt", n_querie);
    FILE *res = fopen(filename, "a");
    switch (q)  /*q == nº da query que queremos responder*/
    {
    case 1: {
        if(querie1(argv[1])) {
            DRIVERS *d =GetcontentD (lookup_drivers (argv[1])); /*faz lookup na hash dos drivers do Driver pedido*/
            printvaloresQ1 (d, res); /*Função que faz print aos valores pretendidos dos drivers*/
            free_driver (d);
        }
        else {
            User *u = GetcontentU( lookup_users (argv[1]) ); /*faz lookup na hash dos users do User pedido*/
            printvaloresQ1_2 (u, res); /*Função que faz print aos valores pretendidos dos users*/
            free_user (u);
        }
        break;
    }
    case 2: {
        if(!arrayOrdenado()){
            createArray();
            foreach_drivers_Q2 ();
            ordenaArray();
        }
        printfArray(res,atoi(argv[1]));
        break;
    }
    case 3: {
        if(!arrayOrdenadoU()){
            createArrayUser();
            foreach_users_Q3();
            QuickSort();
        }
        Q3Print(res, atoi(argv[1]));
        break;
    }
    case 4: {
        Q4* value = inicializaQ4 (strdup (argv[1]));
        foreach_rides_Q4(value);
        printQ4 (value, res);
        freeQ4 (value);
        break;
    }
    case 5: {
        Q5* query5 = inicializaQ5 (strdup(argv[1]),strdup(argv[2]));
        foreach_rides_Q5(query5);
        printQ5(query5, res);
        freeQ5(query5);
        break;
    }
    case 6: {
        Q6* q = inicializaQ6(strdup(argv[1]), strdup(argv[2]), strdup(argv[3]));
        foreach_rides_Q6(q);
        printQ6(q, res);
        freeQ6(q);
        break;
    }
    case 7:{
        inicializaQ7();
        foreach_drivers_Q7(argv[2]);
        ordenaQ7();
        printQ7(res,atoi (argv[1]));
        free_Q7();
    }
    default:
        break;
    }
    fclose (res);
    return;
}

/*verifica que idade tem o user/driver(usando a data dada no enunciado "09/10/2022")*/
int calculaIdade(char *str){  
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