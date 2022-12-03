#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"

static GHashTable *users;

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

void iniciaHashUsers (char *path) {
    FILE *fp = NULL;
    users = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, (GDestroyNotify)free_user);  /*cria a hashtable dos users*/
    char *filename = malloc ((strlen (path) + strlen ("/users.csv") + 1)*sizeof (char));  /*alloca espaço para o input(path dos ficheiros) + o nome do ficheiro que se pretende ler*/
    strcpy(filename,path);
    strcat (filename,"/users.csv");  /*concat do path dos ficheiros mais o nome do ficheiro que se vai ler neste case*/
    fp = fopen(filename,"r");  /*abre o ficheiro*/
    if(!fp){
        perror("Não conseguiu abrir o ficheiro");
        return;
    }
    parser (fp,1);  /*faz o parse do ficheiro*/
    free (filename);  /*free do path*/
    fclose (fp);  /*fecha o ficheiro*/
}

/*Aloca uma nova estrura User para adicionar à hash dos Users*/
void adicionaHashUsers (char *line) {
    User *new = malloc (sizeof (User));
    separa (line,new,1);
    new->total_gasto = 0;
    new ->n_viagens = 0;
    new ->acc_avaliation = 0;
    new ->distance = 0;
    new ->last_ride = NULL;
    g_hash_table_insert(users,new->username,new);
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

User* GetcontentU(User *u) {
    User *copy = malloc (sizeof (User));  
    for (int pos = 1; pos <= 8; pos++) {
        switch (pos) {
            case 1:
                copy-> username = strdup (u->username);
                break;
            case 2:
                copy-> name = strdup (u->name);
                break;
            case 3:
                copy-> data= strdup (u->data);
                break;
            case 4:
                copy->gender= strdup (u->gender);
                break;
            case 5:
                copy-> account_creation = strdup (u->account_creation);
                break;
            case 6:
                copy->pay_method= strdup (u->pay_method);
                break;
            case 7:
                copy->account_status = strdup (u->account_status);
                break;
            case 8:
                copy-> last_ride = strdup (u->last_ride);
                break;
        }
    }

    copy->distance = u->distance;
    copy->n_viagens = u->n_viagens;
    copy->total_gasto = u->total_gasto;
    copy->acc_avaliation = u->acc_avaliation;
    return copy;
}

char *getNameU (User *u) {
    return strdup (u->name);
}

char *getGenderU (User *u) {
    return strdup (u->gender);
}

char *getAccStatusU (User *u) {
    return strdup (u->account_status);
}

char *getDataU (User *u) {
    return strdup (u->data);
}

int getNViagensU (User *u) {
    return u->n_viagens;
}

double getTotalGastoU (User *u) {
    return u->total_gasto;
}

double getAccAvaliationU (User *u) {
    return u->acc_avaliation;
}

char *getUsername(User* user){
    return strdup(user -> username);
}

char *getLastRide(User* user){
    return (user->last_ride ? strdup(user -> last_ride) : NULL);
}

int getDistance(User* user){
    return user -> distance;
}

char *getAccSt(User* user){
    return strdup(user -> account_status);
}

User* lookup_users (char* key) {
    return (g_hash_table_lookup (users, key));
}

void foreach_users_Q3 (ARRAY_USERS *array) {
   g_hash_table_foreach (users,(GHFunc)guardaUser, array);
}

void hash_table_destroy_users () {
    g_hash_table_destroy (users);
}