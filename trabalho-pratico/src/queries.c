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
int identifyArgument(char *str){  
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
int querieIdentifier(char **argv, int n_querie, int modo, int *informacoespaginas, char *paginas[][linhas_por_pagina]) {  
    FILE *res = NULL;
    int q = atoi (argv[0]);
    int r = 1; 
    if(modo == 0){ // modo Batch
        char filename [29 + n_querie];
        sprintf(filename, "Resultados/command%d_output.txt", n_querie);
        res = fopen(filename, "a");
    }
    else {
        mvprintw (informacoespaginas[0],0,"Resultado:");
        paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup ("Resultado:");
        if (informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (informacoespaginas, paginas)) return 0;
    }
    switch (q)  /*q == nº da query que queremos responder*/
    {
    case 1: {
        clock_t t = clock();
        r= query1Exe(res,modo,argv[1],informacoespaginas,paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query1: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 2: {
        clock_t t = clock();
        r = query2Exe(res,modo,argv[1],informacoespaginas,paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query2: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 3: {
        clock_t t = clock();
        r = query3Exe(res,modo,argv[1],informacoespaginas,paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query3: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 4: {
        clock_t t = clock();
        r = exec_Q4 (argv[1], res, modo, informacoespaginas, paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query4: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 5: {
        clock_t t = clock();
        r = query5Exe(res,modo,argv, informacoespaginas, paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query5: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 6: {
        clock_t t = clock();
        r = query6Exe(res,modo,argv,informacoespaginas,paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query6: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 7:{
        clock_t t = clock();
        r = exec_Q7 (argv [2], atoi (argv[1]), res, modo, informacoespaginas, paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query7: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 8: {
        clock_t t = clock();
        r = query8Exe(res,modo,argv,informacoespaginas,paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query8: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    case 9: {
        clock_t t = clock();
        r = query9Exe(res,modo,argv,informacoespaginas,paginas);
        t = clock () -t;
        if (modo == 0) printf ("Query9: %f\n", ((float)t)/CLOCKS_PER_SEC);
        break;
    }
    default:
        break;
    }
    if (res) fclose (res);
    return r;
}

int tempo_De_Vida(char *str){
    int tempo_de_vida;
    char *temp = str;
    if(!temp) tempo_de_vida = -1;
    else{ 
        int dia = atoi(strsep(&str, "/"));
        int mes = atoi(strsep(&str, "/"));
        int ano = atoi(strsep(&str, "/"));
        int tempo_ate_conta = 10000 * ano + 100 * mes + dia;
        int tempo_ate_data = 10000 * ANO + 100 * MES + DIA;
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