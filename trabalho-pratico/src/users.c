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
    int distance;
    double acc_avaliation;
    double total_gasto;
};

/*struct auxiliar usada para realizar a query 3*/
struct ARRAY_USERS{
    int pos; /*posição na qual queremos inserir a próxima struct user*/
    User **user; /*array de users*/
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
    free(value->last_ride);
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
    new ->last_ride = NULL;
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
    if(!user->last_ride) user->last_ride = strdup(date);
    else if(compareDates(date,user->last_ride)){
        char *temp = user->last_ride;
        user->last_ride = strdup(date);
        free(temp);
    } 
    user->distance += atoi(distance);
}

/* Função para fazer print dos valores do user pedido na query 1 no ficheiro */
void printvaloresQ1_2 (User *u, FILE *res)  {
    if (!strcmp(u->account_status,"active")) {
        double avaliacao_media = u->acc_avaliation / u->n_viagens;
        fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",u->name, u->gender, calculaIdade(u->data), avaliacao_media, u->n_viagens, u->total_gasto);
    }
}

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
        if(array->user[t]->distance == pivot->distance){ /*Caso a distância seja igual entramos no desempate*/
            if(compareDates(array->user[t]->last_ride, pivot->last_ride) == 2){ /*Se compareDates == 2, então as datas são iguais e será necessário novo desempate*/
                if(strcmp(array->user[t]->username, pivot->username) > 0){ /*Se strcmp > 0 então o primeiro username terá prioridade e será apresentado primeiro*/      
                    swap1(array, i, t);
                    i++;
                }
            }
            else if(compareDates(array->user[t]->last_ride, pivot->last_ride) == 0){ /*compareDates == 0 se a primeira data for mais antiga, logo o swap é realizado*/
                swap1(array, i, t);
                i++;
            }
        }
        if(array->user[t]->distance < pivot->distance){ /*Se a distância for menor que a do elemento pivot então é feito o swap*/
            swap1(array, i, t);
            i++;
        }
    }
    swap1(array, i, j); /*swap do pivot*/
    return i;
}

/*Função que faz print dos resultados da querie 3*/
void Q3Print(FILE *res, ARRAY_USERS *array, int N){
    int i = 99999;
    int j = 0;
    while(j < N){ /*Ciclo que limita o print dos elementos com base no input da querie*/
        if(!strcmp(array->user[i]->account_status, "active")){ /*Se o status for inativo então o user é ignorado e o print não é executado*/
            fprintf(res, "%s;%s;%d\n", array->user[i]->username, array->user[i]->name, array->user[i]->distance);
            j++;
        }
        i--; /*O print é feito do maior elemento para o menor*/
    }
}

/*Função que faz free do ARRAY_USERS*/
void freeArrayU(ARRAY_USERS *user){
    free(user->user);
    free(user);
}