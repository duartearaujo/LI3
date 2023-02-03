#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/datas.h"

#define DIA 9
#define MES 10
#define ANO 2022

/* Função que compara duas datas.
return value == 1 se a primeira é mais recente que a segunda.
return value == 0 se a primeira é mais antiga que a segunda.
return value == 2 se as datas são iguais.
*/
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

/* Função que calcula a diferença de dias entre a data de referência(09/10/2022) e uma data dada como argumento.*/
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

/* Verifica que idade tem o user/driver(usando a data de referência dada no enunciado "09/10/2022").*/
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