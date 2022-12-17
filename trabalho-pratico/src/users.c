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
    char* data;
    char* account_creation;
    char* last_ride;
    double acc_avaliation;
    double total_gasto;
    int idade_conta;
    int n_viagens;
    int distance;
    char account_status;
    char gender;
};

/*struct auxiliar usada para realizar a query 3*/
struct ARRAY_USERS{
    int ordenado;
    int pos; /*posição na qual queremos inserir a próxima struct user*/
    User **user; /*array de users*/
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
    new->idade_conta = tempo_De_Vida(strdup(new->account_creation));
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
            user->gender = info[0]; 
            break;
        case 4:
            user->data = strdup (info); 
            break;
        case 5:
            user->account_creation = strdup (info); 
            break;
        case 7:
            user->account_status = info[0]; 
            break;
        default:
            break;
        }
}

void addToUser (User *user, int distance, char *tip, int car_class, char *avaliation, char *date) {
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
    user-> acc_avaliation += strtod (avaliation, NULL); /*acumula o valor da avaliação dada ao user*/
    /*acumula a distância viajada e guarda a data da última viagem*/
    if(!user->last_ride) user->last_ride = strdup(date);
    else if(compareDates(date,user->last_ride)){
        char *temp = user->last_ride;
        user->last_ride = strdup(date);
        free(temp);
    } 
    user->distance += distance;
}

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

char *getNameU (User *u) {
    return strdup (u->name);
}

char getGenderU (User *u) {
    return u->gender;
}

char getAccStatusU (User *u) {
    return u->account_status;
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

int get_Idade_Conta_U(User* user){
    return user->idade_conta;
}

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
void guardaUser(gpointer key, User *user, void *a){
    array->pos++;
    array->user = (User**) realloc(array->user,array->pos * sizeof(User*));
    array->user[(array->pos - 1)] = user;
}

void foreach_users_Q3 () {
   g_hash_table_foreach (users,(GHFunc)guardaUser, NULL);
}

int desempate_Q3(const void *p1, const void* p2){
    User *user_1 = *((User**) p1);
    User *user_2 = *((User**) p2);
    int result = 1;
    int Distance = user_1->distance;
    int Pdistance = user_2->distance;
    char *lastRide = user_1->last_ride ? strdup (user_1->last_ride) : NULL;
    char *PLastRide = user_2->last_ride ? strdup(user_2->last_ride) : NULL;
    char *username = strdup(user_1->username);
    char *Pusername = strdup(user_2->username);
    if (Distance > Pdistance) result = -1;
    else if(Distance == Pdistance){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
        if(compareDates(lastRide,PLastRide) == 1) result = -1;   /*compareDates = 1 -> primeira data é mais recente*/
        else if(!strcmp(lastRide,PLastRide)){    /*compareDates = 2 -> as duas datas são iguais*/
            if(strcmp(username,Pusername) < 0) result = -1;  /*se as datas forem iguais então compara-se os id*/
        }
    }
    free(lastRide);
    free(PLastRide);
    free(username);
    free(Pusername);
    return result;
}

void ordena_Q3(){
    qsort (array->user,(size_t)array->pos, sizeof(User*), desempate_Q3);
    array->ordenado = 1;
}

int arrayOrdenadoU(){
    if(!array) return 0;
    return array->ordenado;
}

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

void hash_table_destroy_users () {
    g_hash_table_destroy (users);
}