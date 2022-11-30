#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/main.h"
#include "../include/queries.h"
#include "../include/query3.h"

/*struct auxiliar usada para realizar a query 3*/
struct ARRAY_USERS{
    int pos; /*posição na qual queremos inserir a próxima struct user*/
    User **user; /*array de users*/
};

/*Função que inicializa o ARRAY_USERS*/
ARRAY_USERS* createArrayUser(int N){
    ARRAY_USERS *array = malloc(sizeof(ARRAY_USERS));
    array->pos = 0;
    array->user = malloc(sizeof(User *) * N);
    return array;
}

/*Função que guarda os users no ARRAY_USERS e incrementa o campo pos*/
void guardaUser(gpointer key, User *user, ARRAY_USERS *array){
    array->user[array->pos] = user;
    array->pos++;
}

/*Swap usado no sort do array*/
void swap1(ARRAY_USERS *array, int i, int t){
    User *u = array->user[i];
    array->user[i] = array->user[t];
    array->user[t] = u;
}

/*Chamada recursiva do QuickSort*/
void QSRecursion(ARRAY_USERS *array, int i, int j){
    if(i < j){
        int pivot_i = partition(array, i, j);
        QSRecursion(array, i, pivot_i-1); // Esquerda do pivot
        QSRecursion(array, pivot_i+1, j); // Direita do pivot
    }
}

/*Método de ordenação do array*/
void QuickSort(ARRAY_USERS *array, int N){
    QSRecursion(array, 0, N-1);
}

/*Função que faz a partição do sort, colocando os elementos menores que o pivot à sua esquerda e os maiores à direita. Devolve o índice final do pivot*/
int partition(ARRAY_USERS *array, int i, int j){
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
                    swap1(array, i, t);
                    i++;
                }
            }
            else if(compareDates(lastRide, PlastRide) == 0){ /*compareDates == 0 se a primeira data for mais antiga, logo o swap é realizado*/
                swap1(array, i, t);
                i++;
            }
        }
        if(distance < PDistance){ /*Se a distância for menor que a do elemento pivot então é feito o swap*/
            swap1(array, i, t);
            i++;
        }
        free (lastRide);
        free (PlastRide);
        free (username);
        free (Pusername);
    }
    swap1(array, i, j); /*swap do pivot*/
    return i;
}

/*Função que faz print dos resultados da querie 3*/
void Q3Print(FILE *res, ARRAY_USERS *array, int N){
    int i = 99999;
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

/*Função que faz free do ARRAY_USERS*/
void freeArrayU(ARRAY_USERS *user){
    free(user->user);
    free(user);
}