#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query1.h"
#include "../include/query2.h"
#include "../include/query3.h"
#include "../include/query4.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"
#include "../include/query8.h"
#include "../include/query9.h"

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
    int r = 0;
    if(str && !string) r = 1;
    else if(!str && string) r = 0;
    else if(!string && !str) r = 2;
    else{
        char *str_ = strdup(str);                                    
        char *str_2 = strdup(string);  
        char *temp = str_;
        char *temp2 = str_2;                         
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
    }
    return r;
}

/*função usada para responder às queries, ou chamar as funções que resolvem as queries */
void querieIdentifier(char **argv, int n_querie, int modo) {  
    FILE *res = NULL;
    int q = atoi (argv[0]);
    if(modo == 0){ // modo Batch
        char filename [29 + n_querie];
        sprintf(filename, "Resultados/command%d_output.txt", n_querie);
        res = fopen(filename, "a");
    }
    else
        printf ("Resultado:\n");
    switch (q)  /*q == nº da query que queremos responder*/
    {
    case 1: {
        clock_t t = clock();
        if(querie1(argv[1])) {
            DRIVERS *d =GetcontentD (lookup_drivers (argv[1])); /*faz lookup na hash dos drivers do Driver pedido*/
            if (d) { 
                printvaloresQ1 (d, res,modo); /*Função que faz print aos valores pretendidos dos drivers*/
                free_driver (d);
            }
            else if (modo == 1) 
                printf ("\tO driver inserido não existe.\n");
        }
        else {
            User *u = GetcontentU( lookup_users (argv[1]) ); /*faz lookup na hash dos users do User pedido*/
            if (u) { 
                printvaloresQ1_2 (u, res,modo); /*Função que faz print aos valores pretendidos dos users*/
                free_user (u);
            }
            else if (modo == 1) 
                printf ("\tO user inserido não existe.\n");
        }
        t = clock () -t;
        if (modo == 0) printf ("Query1: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 2: {
        clock_t t = clock();
        if (atoi (argv[1])) {
            if(!arrayOrdenado()){
                createArray();
                foreach_drivers_Q2 ();
                ordena_Q2();
            }
            printfArray(res,atoi(argv[1]),modo);
        }
        t = clock () -t;
        if (modo == 0) printf ("Query2: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 3: {
        clock_t t = clock();
        if (atoi (argv[1])) {
            if(!arrayOrdenadoU()){
                createArrayUser();
                foreach_users_Q3();
                ordena_Q3();
            }
            Q3Print(res, atoi(argv[1]),modo);
        }
        t = clock () -t;
        if (modo == 0) printf ("Query3: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 4: {
        clock_t t = clock();

        exec_Q4 (argv[1], res, modo);

        t = clock () -t;
        if (modo == 0) printf ("Query4: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 5: {
        clock_t t = clock();

        Q5* query5 = inicializaQ5 (strdup(argv[1]),strdup(argv[2]));
        foreach_rides_Q5(query5);
        printQ5(query5, res, modo);
        freeQ5(query5);
        t = clock () -t;
        if (modo == 0) printf ("Query5: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 6: {
        clock_t t = clock();

        Q6* q = inicializaQ6(strdup(argv[1]), strdup(argv[2]), strdup(argv[3]));
        foreach_rides_Q6(q);
        printQ6(q, res,modo);
        freeQ6(q);
        t = clock () -t;
        if (modo == 0) printf ("Query6: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 7:{
        clock_t t = clock();
        if (atoi (argv[1])) 
            exec_Q7 (argv [2], atoi (argv[1]), res, modo);
        t = clock () -t;
        if (modo == 0) printf ("Query7: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 8: {
        clock_t t = clock();

        inicializa_array_Q8(atoi(argv[2]),argv[1][0]);
        foreach_rides_Q8();
        ordena_Q8();
        printArray_Q8(res, modo);
        freeArray_Q8();
        t = clock () -t;
        if (modo == 0) printf ("Query8: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 9: {
        clock_t t = clock();
        int t1 = tempo_De_Vida(strdup(argv[1]));
        int t2 = tempo_De_Vida(strdup(argv[2]));
        Q9Print(res, t1, t2, modo);
        t = clock () -t;
        if (modo == 0) printf ("Query9: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    default:
        break;
    }
    if (res) fclose (res);
    return;
}

int tempo_De_Vida(char *str){
    int tempo_de_vida;
    char *temp = str;
    if(!temp) tempo_de_vida = -1;
    else{ 
        int dia = atoi(strsep(&str, "/"));
        int mes = atoi(strsep(&str, "/"));
        int ano = atoi(strsep(&str, "/"));
        int tempo_ate_conta = 372 * ano + 31 * (mes-1) + dia;
        int tempo_ate_data = 372 * ANO + 31 * (MES-1) + DIA;
        tempo_de_vida = tempo_ate_data - tempo_ate_conta;
        free(temp);
    }
    return tempo_de_vida;
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
    else if (mes > MES) idade = ANO - ano -1;
    return idade;
}