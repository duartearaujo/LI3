#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query8.h"
#include "../include/interactive.h"

struct dados_Q8{
    char *nome_driver;
    char *nome_user;
    char *id_driver;
    char *id_viagem;
    char *username_user;
    int idade_conta_driver;
    int idade_conta_user;
};

struct array_Q8{
    int pos;
    int idade_enunciado;
    char genero_enunciado;
    dados_Q8** lista;
};

static dados_Q8 *dados = NULL;
static array_Q8 *array = NULL;

dados_Q8* inicializa_dados_Q8(){
    dados = malloc(sizeof(dados_Q8));
    dados->nome_driver = NULL;
    dados->nome_user = NULL;
    dados->id_driver = NULL;
    dados->id_viagem = NULL;
    dados->username_user = NULL;
    dados->idade_conta_driver = 0;
    dados->idade_conta_user = 0;
    return dados;
}

void inicializa_array_Q8(int idade_enunciado,char gender_enunciado){
    array = malloc(sizeof(array_Q8));
    array->pos = 0;
    array->idade_enunciado = idade_enunciado * 372;
    array-> genero_enunciado = gender_enunciado;
    array->lista = NULL;
}

void passa_Para_Struct(char *nome_driver,char *nome_user,char *id,char *id_viagem,char *username,int idade_conta_driver,int idade_conta_user,int pos){
    array->lista[pos]->nome_driver = strdup(nome_driver);
    array->lista[pos]->nome_user = strdup(nome_user);
    array->lista[pos]->id_driver = strdup(id);
    array->lista[pos]->id_viagem = strdup(id_viagem);
    array->lista[pos]->username_user = strdup(username);
    array->lista[pos]->idade_conta_driver = idade_conta_driver;
    array->lista[pos]->idade_conta_user = idade_conta_user;
}


void verifica_dados_Q8 (gpointer key, RIDES* ride, void *a){
    char *username = getUsernameR(ride);
    char *id = getIdDriverR(ride);
    char genero_user = getGenderU(lookup_users(username));
    char genero_driver = getGenderD(lookup_drivers(id));
    if( genero_user == array->genero_enunciado && genero_driver == array->genero_enunciado){
        int idade_conta_user = get_Idade_Conta_U(lookup_users(username));
        int idade_conta_driver = get_Idade_Conta_D(lookup_drivers(id));
        if(idade_conta_driver >= array->idade_enunciado && idade_conta_user >= array->idade_enunciado){
            char *id_viagem = getIdR(ride);
            array->pos++;
            array->lista = (dados_Q8**) realloc(array->lista,array->pos * sizeof(dados_Q8*));
            array->lista[array->pos-1] = inicializa_dados_Q8();
            char *nome_driver = getNameD(lookup_drivers(id));
            char *nome_user = getNameU(lookup_users(username));
            passa_Para_Struct(nome_driver,nome_user,id,id_viagem,username,idade_conta_driver,idade_conta_user,array->pos-1);
            free(id_viagem);
            free(nome_driver);
            free(nome_user);
        }
    }
    free(username);
    free(id);
}

int desempate_Q8(const void *p1, const void* p2){
    dados_Q8 *dados_1 = *((dados_Q8**) p1);
    dados_Q8 *dados_2 = *((dados_Q8**) p2);
    int result = 1;
    int idade_conta_driver = dados_1->idade_conta_driver;
    int idade_conta_driver2 = dados_2->idade_conta_driver;
    int idade_conta_user = dados_1->idade_conta_user;
    int idade_conta_user2 = dados_2->idade_conta_user;
    char *id = strdup(dados_1->id_viagem );
    char *id2 = strdup(dados_2->id_viagem);
    if (idade_conta_driver > idade_conta_driver2) result = -1;
    else if(idade_conta_driver== idade_conta_driver2){
        if(idade_conta_user > idade_conta_user2) result = -1;
        else if(idade_conta_user == idade_conta_user2){
            if(atoi(id) < atoi(id2)) result = -1;
        }
    }
    free(id);
    free(id2);
    return result;
}

void ordena_Q8(){  
    qsort (array->lista,(size_t)array->pos, sizeof(dados_Q8*), desempate_Q8);
}

void printArray_Q8(FILE *res, int modo, int *informacoespaginas, char (*paginas)[][linhas_por_pagina]){
    for(int i = 0; i < array->pos;i++){
        char account_status_driver = getAccountStatusD(lookup_drivers(array->lista[i]->id_driver));
        char account_status_user = getAccStatusU(lookup_users(array->lista[i]->username_user));
        if(account_status_driver == 'a' && account_status_user == 'a') {
            if (modo == 0)
                fprintf(res,"%s;%s;%s;%s\n",array->lista[i]->id_driver,array->lista[i]->nome_driver,array->lista[i]->username_user,array->lista[i]->nome_user);
            else{
                mvprintw(informacoespaginas[0]++, 0, "\t%s;%s;%s;%s",array->lista[i]->id_driver,array->lista[i]->nome_driver,array->lista[i]->username_user,array->lista[i]->nome_user);
                if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
            }
        }  
    }
}

void freeDados_Q8(dados_Q8* data){
    free(data->nome_driver);
    free(data->nome_user);
    free(data->id_driver);
    free(data->id_viagem);
    free(data->username_user);
    free(data);
}

void freeArray_Q8(){
    if(array){
        for(int i = 0; i < array->pos;i++){
            freeDados_Q8(array->lista[i]);
        }
        free(array->lista);
        free(array);
    }
}

void query8Exe(FILE *res, int modo, char **argv, int *informacoespaginas, char (*paginas)[][linhas_por_pagina]){
    inicializa_array_Q8(atoi(argv[2]),argv[1][0]);
    foreach_rides_Q8();
    ordena_Q8();
    printArray_Q8(res, modo, informacoespaginas, paginas);
    freeArray_Q8();
}