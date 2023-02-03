#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include <ctype.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"
#include "../include/dataverification.h"
#include "../include/datas.h"

static GHashTable *users;

/*Struct para guardar os valores referentes a cada user */
struct user {    
    char* username; /**<Campo que indica o username do user*/
    char* name; /**<Campo que indica o nome do user*/
    char* data; /**<Campo que indica a data de nascimento do user*/
    char* account_creation; /**<Campo que indica a data de criação da conta*/
    char* last_ride; /**<Campo que indica a data da última viagem do user*/
    double total_gasto; /**<Campo que indica o total gasto do user*/
    int acc_avaliation; /**<Campo que indica a avaliação total do user*/
    int idade_conta; /**<Campo que indica a idade da conta*/
    int n_viagens; /**<Campo que indica o número de viagens do user*/
    int distance; /**<Campo que indica a distância percorrida pelo user*/
    char account_status; /**<Campo que indica o status da conta*/
    char gender; /**<Campo que indica o género do user*/
};

/*struct auxiliar usada para realizar a query 3*/
struct ARRAY_USERS{
    int ordenado; /**<Indica se o array está ordenado ou não*/
    int pos; /**<Posição na qual queremos inserir a próxima struct user*/
    User **user; /**<Array de users*/
};

static ARRAY_USERS *array = NULL;

/*Função que faz free de todos os campos do user e da sua própria estrutura*/
void free_user (User *value) {
    free(value->username);
    free(value->name);
    free(value->data);
    free(value->account_creation);
    free(value->last_ride);
    free (value);
}


int iniciaHashUsers (char *path) {
    FILE *fp = NULL;
    users = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, (GDestroyNotify)free_user); /*cria a hashtable dos users*/
    createArrayUser();  
    char *filename = malloc ((strlen (path) + strlen ("/users.csv") + 1)*sizeof (char));  /*alloca espaço para o input(path dos ficheiros) + o nome do ficheiro que se pretende ler*/
    strcpy(filename,path);
    strcat (filename,"/users.csv");  /*concat do path dos ficheiros mais o nome do ficheiro que se vai ler neste case*/
    fp = fopen(filename,"r");  /*abre o ficheiro*/
    if(!fp){
        perror("Não conseguiu abrir o ficheiro");
        return 0;
    }
    parser (fp,1);  /*faz o parse do ficheiro*/
    free (filename);  /*free do path*/
    fclose (fp);  /*fecha o ficheiro*/
    return 1;
}

/*Aloca uma nova estrura User para adicionar à hash dos Users*/
void adicionaHashUsers (char *line) {
    User *new = malloc (sizeof (User));
    if (separa (line,new,1)) {
        new ->total_gasto = 0;
        new ->n_viagens = 0;
        new ->acc_avaliation = 0;
        new ->distance = 0;
        new ->idade_conta = tempo_De_Vida(strdup(new->account_creation));
        new ->last_ride = NULL;
        g_hash_table_insert(users,new->username,new);
        guardaUser(new);
    }
}

/*Atribui a informação recebida do ficheio users.csv ao campo correspondente da struct User*/
int atribui (User *user, int pos, char *info) {
    switch (pos){
        case 1:
            if (info[0] == '\0') {
                free (user);
                return 0;
            }
            user->username = strdup (info); 
            break;
        case 2:
            if (info[0] == '\0') {
                free (user->username);
                free (user);
                return 0;
            }
            user->name = strdup (info); 
            break;
        case 3:
            info[0] = toupper (info [0]);
            if ((info [0] == 'M' || info[0] == 'F') && info [1] == '\0')
                user->gender = info[0]; 
            else {
                free (user->username);
                free (user->name);
                free (user);
                return 0;
            }
            break;
        case 4:
            if (verificadata (info)) 
                user->data = strdup (info);
            else {
                free (user->username);
                free (user->name);
                free (user);                
                return 0;
            } 
            break;
        case 5:
            if (verificadata (info)) 
                user->account_creation = strdup (info);
            else {
                free (user->username);
                free (user->name);
                free (user->data);
                free (user);                
                return 0;
            } 
            break;
        case 6:
            if (info[0] == '\0') {
                free (user->username);
                free (user->name);
                free (user->data);
                free (user->account_creation);
                free (user); 
                return 0;
            }
            break;
        case 7:
            if (verificastatus (info))
                user->account_status = info[0]; 
            else {
                free (user->username);
                free (user->name);
                free (user->data);
                free (user->account_creation);
                free (user); 
                return 0;
            }
            break;
        default:
            break;
        }
    return 1;
}

/*Função que trata das estatísticas do user, adicionando os dados das viagens do mesmo*/
void addToUser (User *user, int distance, char *tip, int car_class, int avaliation, char *date) {
    switch (car_class) /*calcula os valores dependendo do int q identifica o tipo de carro.*/ 
      {
         case 0:
            user->total_gasto += strtod (tip,NULL) + distance * 0.62 + 3.25;
            break;
         case 1:
            user->total_gasto += strtod (tip,NULL) + distance * 0.79 + 4;
            break;
         case 2:
            user->total_gasto  += strtod (tip,NULL) + distance * 0.94 + 5.20;
            break;
         default:
            break;
      }
    user->n_viagens ++;
    user-> acc_avaliation += avaliation; /*acumula o valor da avaliação dada ao user*/
    /*acumula a distância viajada e guarda a data da última viagem*/
    if(!user->last_ride) user->last_ride = strdup(date);
    else if(compareDates(date,user->last_ride)){
        char *temp = user->last_ride;
        user->last_ride = strdup(date);
        free(temp);
    } 
    user->distance += distance;
}

/*Retorna uma cópia da estrutura user*/
User* GetcontentU(User *u) {
    if (u) {
        User *copy = malloc (sizeof (User));  
        copy-> username = strdup (u->username);
        copy-> name = strdup (u->name);
        copy-> data = strdup (u->data);
        copy->gender = u->gender;
        copy-> account_creation = strdup (u->account_creation);
        copy->account_status = u->account_status;
        copy->last_ride = u->last_ride ? strdup (u->last_ride) : NULL;
        copy->distance = u->distance;
        copy->n_viagens = u->n_viagens;
        copy->total_gasto = u->total_gasto;
        copy->acc_avaliation = u->acc_avaliation;
        return copy;
    }
    return NULL;
}

/*Retorna o nome do user*/
char *getNameU (User *u) {
    return strdup (u->name);
}

/*Retorna o género do user*/
char getGenderU (User *u) {
    return u->gender;
}

/*Retorna o status da conta do user*/
char getAccStatusU (User *u) {
    return u->account_status;
}

/*Retorna a data de nascimento do user*/
char *getDataU (User *u) {
    return strdup (u->data);
}

/*Retorna o número de viagens correspondente ao user*/
int getNViagensU (User *u) {
    return u->n_viagens;
}

/*Retorna o total gasto do user*/
double getTotalGastoU (User *u) {
    return u->total_gasto;
}

/*Retorna a avaliação do user*/
int getAccAvaliationU (User *u) {
    return u->acc_avaliation;
}

/*Retorna o username do user*/
char *getUsername(User* user){
    return strdup(user -> username);
}

/*Retorna a data da última viagem do user*/
char *getLastRide(User* user){
    return (user->last_ride ? strdup(user -> last_ride) : NULL);
}

/*Retorna o campo da distância do user*/
int getDistance(User* user){
    return user -> distance;
}

/*Retorna a idade da conta do user*/
int get_Idade_Conta_U(User* user){
    return user->idade_conta;
}

/*Retorna o user correspondente à key recebida como argumento*/
User* lookup_users (char* key) {
    return (g_hash_table_lookup (users, key));
}

/*Função que inicializa o ARRAY_USERS*/
void createArrayUser(){
    array = malloc(sizeof(ARRAY_USERS));
    array->pos = 0;
    array->ordenado = 0;
    array->user = NULL;
}

/*Função que guarda os users no ARRAY_USERS e incrementa o campo pos*/
void guardaUser(User *user){
    array->pos++;
    array->user = (User**) realloc(array->user,array->pos * sizeof(User*));
    array->user[(array->pos - 1)] = user;
}

/*Função que faz o quicksort do array dos users*/
void ordena_Q3(){
    qsort (array->user,(size_t)array->pos, sizeof(User*), desempate_Q3);
    array->ordenado = 1;
}

/*Função que verifica se o array está ordenado ou não*/
int arrayOrdenadoU(){
    if(!array) return 0;
    return array->ordenado;
}

/*Retorna o conteúdo da estrutura user*/
User* getElement_Q3(int i){
    return GetcontentU(array->user[i]);
}

/*Função que faz free do ARRAY_USERS*/
void freeArrayU(){
    if(array){
        free(array->user);
        free(array);
    }
}

/*Faz free da hashtable dos users*/
void hash_table_destroy_users () {
    g_hash_table_destroy (users);
}