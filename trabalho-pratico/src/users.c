#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"

/*Struct para guardar os valores referentes a cada user */
struct user {    
    char* username;
    char* name;
    char* gender;
    char* data;
    char* account_creation;
    char* pay_method;
    char* account_status;
    char* last_ride;
    int n_viagens;
    double acc_avaliation;
    double total_gasto;
    double distance;
};

struct ARRAY_USERS{
    int pos;
    User **user;
};

/*Função que faz free de todos os campos do user e da sua própria estrutura*/
void free_user (User *value) {
    free(value->username);
    free(value->name);
    free(value->gender);
    free(value->data);
    free(value->account_creation);
    free(value->pay_method);
    free(value->account_status);
    free (value);
}

/*Aloca uma nova estrura User para adicionar à hash dos Users*/
void criaHashUser (HASH *hash, char *line) {
    User *new = malloc (sizeof (User));
    separa (line,new,1);
    new->total_gasto = 0;
    new ->n_viagens = 0;
    new ->acc_avaliation = 0;
    new ->distance = 0;
    g_hash_table_insert(retornaHash(1,hash),new->username,new);
}

/*Atribui a informação recebida do ficheio users.csv ao campo correspondente da struct User*/
void atribui (User *user, int pos, char *info) {
    switch (pos){
        case 1:
            user->username = strdup (info); 
            break;
        case 2:
            user->name = strdup (info); 
            break;
        case 3:
            user->gender = strdup (info); 
            break;
        case 4:
            user->data = strdup (info); 
            break;
        case 5:
            user->account_creation = strdup (info); 
            break;
        case 6:
            user->pay_method = strdup (info); 
            break;
        case 7:
            user->account_status = strdup (info); 
            break;
    }
}

void addToUser (User *user, char *distance, char *tip, int car_class, char *avaliation, char *date) {
    switch (car_class) /*calcula os valores dependendo do int q identifica o tipo de carro.*/ 
      {
         case 0:
            user->total_gasto += strtod (tip,NULL) + strtod (distance, NULL) * 0.62 + 3.25;
            break;
         case 1:
            user->total_gasto += strtod (tip,NULL) + strtod (distance, NULL) * 0.79 + 4;
            break;
         case 2:
            user->total_gasto  += strtod (tip,NULL) + strtod (distance, NULL) * 0.94 + 5.20;
            break;
         default:
            break;
      }
    user->n_viagens ++;
    user-> acc_avaliation += strtod (avaliation, NULL); /*acumula o valor da avaliação dada ao user*/
    /*acumula a distância viajada e guarda a data da última viagem*/
    char *str = strdup(date);
    if(!user->last_ride) user->last_ride = str;
    else if(compareDates(date,str)) user->last_ride = str;
    user->distance += strtod(distance, NULL);
}

/* Função para fazer print dos valores do user pedido na query 1 no ficheiro */
void printvaloresQ1_2 (User *u, FILE *res)  {
    if (!strcmp(u->account_status,"active")) {
        double avaliacao_media = u->acc_avaliation / u->n_viagens;
        fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",u->name, u->gender, calculaIdade(u->data), avaliacao_media, u->n_viagens, u->total_gasto);
    }
}

ARRAY_USERS* createArrayUser(int N){
    ARRAY_USERS *array = malloc(sizeof(ARRAY_USERS));
    array->pos = 0;
    array->user = malloc(sizeof(User) * N);
    return array;
}

void guardaUser(gpointer key, User *user, ARRAY_USERS *array){
    array->user[array->pos] = user;
    array->pos++;
}

void swap1(ARRAY_USERS *array, int i, int t){
    User *u = array->user[i];
    array->user[i] = array->user[t];
    array->user[t] = u;
}

void QSRecursion(ARRAY_USERS *array, int i, int j){
    if(i < j){
        int pivot_i = partition(array, i, j);
        QSRecursion(array, i, pivot_i-1); // Esquerda do pivot
        QSRecursion(array, pivot_i+1, j); // Direita do pivot
    }
}

void QuickSort(ARRAY_USERS *array, int N){
    QSRecursion(array, 0, N-1);
}

int partition(ARRAY_USERS *array, int i, int j){
    User *pivot = array->user[j];
    for(int t = i; t < j; t++){
        if(array->user[t]->distance == pivot->distance){
            if(compareDates(array->user[t]->last_ride, pivot->last_ride) == 2){
                if(strcmp(array->user[t]->username, pivot->username) > 0){
                    swap1(array, i, t);
                    i++;
                }
            }
            else if(compareDates(array->user[t]->last_ride, pivot->last_ride) == 0){
                swap1(array, i, t);
                i++;
            }
        }
        if(array->user[t]->distance < pivot->distance){
            swap1(array, i, t);
            i++;
        }
    }
    swap1(array, i, j);
    return i;
}

void Q2Print(FILE *res, ARRAY_USERS *array, int N){
    int i = 99999;
    int j = 0;
    while(j < N){
        if(!strcmp(array->user[i]->account_status, "active")){
            fprintf(res, "%s;%s;%.3f\n", array->user[i]->username, array->user[i]->name, array->user[i]->distance);
            j++;
        }
        i--;
    }
}