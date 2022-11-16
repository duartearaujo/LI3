#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"

struct user {    
    char* username;
    char* name;
    char* gender;
    char* data;
    char* account_creation;
    char* pay_method;
    char* account_status;
    int n_viagens;
    double acc_avaliation;
    double total_gasto;
};

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

void criaHashUser (HASH *hash, char *line) {
    User *new = malloc (sizeof (User));
    separa (line,new,1);
    new->total_gasto = 0;
    new ->n_viagens = 0;
    new ->acc_avaliation = 0;
    g_hash_table_insert(retornaHash(1,hash),new->username,new);
}

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

void addToUser (User *user, char *distance, char *tip, int car_class, char *avaliation) {
    switch (car_class) // calcula os valores dependendo do int q identifica o tipo de carro.
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
    user-> acc_avaliation += strtod (avaliation, NULL);
}

void printvaloresQ1_2 (User *u, FILE *res)  {
    if (!strcmp(u->account_status,"active")) {
        double avaliacao_media = u->acc_avaliation / u->n_viagens;
        fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",u->name, u->gender, calculaIdade(u->data), avaliacao_media, u->n_viagens, u->total_gasto);
    }
}