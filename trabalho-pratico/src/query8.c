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
    int ordenado;
    int idade_enunciado;
    char *genero_enunciado;
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

void inicializa_array_Q8(int idade_enunciado,char *gender_enunciado){
    array = malloc(sizeof(array_Q8));
    array->pos = 0;
    array->ordenado = 0;
    array->idade_enunciado = idade_enunciado * 365;
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
    char *id_viagem = getIdR(ride);
    char *genero_user = getGenderU(lookup_users(username));
    char *genero_driver = getGenderD(lookup_drivers(id));
    int idade_conta_user = get_Idade_Conta_U(lookup_users(username));
    int idade_conta_driver = get_Idade_Conta_D(lookup_drivers(id));
    if(!strcmp(genero_user,array->genero_enunciado) && !strcmp(genero_driver,array->genero_enunciado)){
        if(idade_conta_driver >= array->idade_enunciado && idade_conta_user >= array->idade_enunciado){
            array->pos++;
            array->lista = (dados_Q8**) realloc(array->lista,array->pos * sizeof(dados_Q8*));
            array->lista[array->pos-1] = inicializa_dados_Q8();
            char *nome_driver = getNameD(lookup_drivers(id));
            char *nome_user = getNameU(lookup_users(username));
            passa_Para_Struct(nome_driver,nome_user,id,id_viagem,username,idade_conta_driver,idade_conta_user,array->pos-1);
            free(nome_driver);
            free(nome_user);

        }
    }
    free(username);
    free(id);
    free(id_viagem);
    free(genero_user);
    free(genero_driver);
}

void swap_Q8(dados_Q8** array, int a, int b){   
  dados_Q8 *t = array[a];
  array[a] = array[b];
  array[b] = t;
}

void ordena_Array_Q8(){   
   int i, j, m;
   for (i = array->pos; i > 0; i--) {
   m = 0;
   for (j = 0; j < i; j++){
        if (array->lista[j]->idade_conta_driver > array->lista[m]->idade_conta_driver) m = j;
        else if(array->lista[j]->idade_conta_driver == array->lista[m]->idade_conta_driver){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
            if(array->lista[j]->idade_conta_user > array->lista[m]->idade_conta_user) m = j;   /*compareDates = 1 -> primeira data é mais recente*/
            else if(array->lista[j]->idade_conta_user == array->lista[m]->idade_conta_user){    /*compareDates = 2 -> as duas datas são iguais*/
                if(atoi(array->lista[j]->id_viagem) > atoi(array->lista[m]->id_viagem)) m = j;  /*se as datas forem iguais então compara-se os id*/
            }
        }
   }
    swap_Q8(array->lista, i-1, m);
   }
   array->ordenado = 1;
}

void printArray_Q8(FILE *res){
    for(int i = array->pos-1; i >= 0;i--){
        char *account_status_driver = getAccountStatusD(lookup_drivers(array->lista[i]->id_driver));
        char *account_status_user = getAccStatusU(lookup_users(array->lista[i]->username_user));
        if(strcmp(account_status_driver,"inactive") && strcmp(account_status_user,"inactive"))
            fprintf(res,"%s;%s;%s;%s\n",array->lista[i]->id_driver,array->lista[i]->nome_driver,array->lista[i]->username_user,array->lista[i]->nome_user);  
        free(account_status_driver);
        free(account_status_user);
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