#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"
#include "../include/query3.h"

/*struct auxiliar usada para realizar a query 3*/
struct ARRAY_USERS{
    int ordenado;
    int pos; /*posição na qual queremos inserir a próxima struct user*/
    User **user; /*array de users*/
};

static ARRAY_USERS *array = NULL;

/*Função que inicializa o ARRAY_USERS*/
void createArrayUser(){
    array = malloc(sizeof(ARRAY_USERS));
    array->pos = 0;
    array->ordenado = 0;
    array->user = NULL;
}

/*Função que guarda os users no ARRAY_USERS e incrementa o campo pos*/
void guardaUser(gpointer key, User *user, void *a){
    array->pos++;
    array->user = (User**) realloc(array->user,array->pos * sizeof(User*));
    array->user[(array->pos - 1)] = GetcontentU(user);
}

/*Swap usado no sort do array*/
void swap1(int i, int t){
    User *u = array->user[i];
    array->user[i] = array->user[t];
    array->user[t] = u;
}

/*Chamada recursiva do QuickSort*/
void QSRecursion(int i, int j){
    if(i < j){
        int pivot_i = partition(i, j);
        QSRecursion(i, pivot_i-1); // Esquerda do pivot
        QSRecursion(pivot_i+1, j); // Direita do pivot
    }
}

/*Método de ordenação do array*/
void QuickSort(){
    int N = array->pos;
    QSRecursion(0, N-1);
    array->ordenado = 1;
}

/*Função que faz a partição do sort, colocando os elementos menores que o pivot à sua esquerda e os maiores à direita. Devolve o índice final do pivot*/
int partition(int i, int j){
    User *pivot = array->user[j];
    for(int t = i; t < j; t++){
        int distance = getDistance(array->user[t]);
        int PDistance = getDistance(pivot);
        char *lastRide = getLastRide(array->user[t]);
        char *PlastRide = getLastRide(pivot);
        char *username = getUsername(array->user[t]);
        char *Pusername = getUsername(pivot);
        if(distance == PDistance){ /*Caso a distância seja igual entramos no desempate*/
            if(compareDates(lastRide, PlastRide) == 2){ /*Se compareDates == 2, então as datas são iguais e será necessário novo desempate*/
                if(strcmp(username, Pusername) > 0){ /*Se strcmp > 0 então o primeiro username terá prioridade e será apresentado primeiro*/      
                    swap1(i, t);
                    i++;
                }
            }
            else if(compareDates(lastRide, PlastRide) == 0){ /*compareDates == 0 se a primeira data for mais antiga, logo o swap é realizado*/
                swap1(i, t);
                i++;
            }
        }
        if(distance < PDistance){ /*Se a distância for menor que a do elemento pivot então é feito o swap*/
            swap1(i, t);
            i++;
        }
        free (lastRide);
        free (PlastRide);
        free (username);
        free (Pusername);
    }
    swap1(i, j); /*swap do pivot*/
    return i;
}

/*Função que faz print dos resultados da querie 3*/
void Q3Print(FILE *res, int N){
    int i = (array->pos - 1);
    int j = 0;
    while(j < N){ /*Ciclo que limita o print dos elementos com base no input da querie*/
        char *AccSt = getAccSt(array->user[i]);
        char *username = getUsername(array->user[i]);
        char *name =getNameU(array->user[i]);
        int distance = getDistance(array->user[i]);
        if(!strcmp(AccSt, "active")){ /*Se o status for inativo então o user é ignorado e o print não é executado*/
            fprintf(res, "%s;%s;%d\n", username, name, distance);
            j++;
        }
        i--; /*O print é feito do maior elemento para o menor*/
        free(AccSt);
        free(username);
        free(name);
    }
}

int arrayOrdenadoU(){
    if(!array) return 0;
    return array->ordenado;
}

/*Função que faz free do ARRAY_USERS*/
void freeArrayU(){
    if(array){
        for(int i = 0; i < array->pos; i++){
            free_user(array->user[i]);
        }
        free(array->user);
        free(array);
    }
}