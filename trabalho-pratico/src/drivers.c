#include <stdio.h>
#include <glib.h>
#include <time.h>
#include "../include/parse.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query7.h"

static GHashTable* drivers;

struct avaliacao_por_cidade {
    char *name, *id, *city;
    int n_viagens;
    double avaliacao_total;
    double avaliacao_media;
};

/*struct onde vão ser armazenados os dados do ficheiro drivers.csv*/
struct DRIVERS{   
    char* id;
    char* name;
    char* birth;
    char* gender;
    char* car_class;
    char* city;
    char* ac_cr;
    char* ac_st;
    int count;
    double valor_atual;
    double avaliacao_media;
    char *mostRecentRide;
    double total_auferido;
    GHashTable *avaliacao_cidades;
    int idade_conta;
};

/*struct auxiliar usada para realizar a query 2*/
struct LISTA_DRIVERS{
    int ordenado;
    GList *lista;   /*lista ligada de drivers*/
};

static LISTA_DRIVERS *lista_drivers = NULL;

/*função responsável por dar free dos drivers, é usada para dar free da hashtable(dos drivers)*/
void free_driver (DRIVERS *value) {   
    free (value->id);
    free (value->name);
    free (value->birth);
    free (value->gender);
    free (value->car_class);
    free (value->city);
    free (value->ac_cr);
    free (value->ac_st);
    free (value->mostRecentRide);
    if (value->avaliacao_cidades) g_hash_table_destroy (value->avaliacao_cidades);
    free (value);
}

void free_avaliacao_por_cidade (AvC *value) {
    free (value->id);
    free (value->name);
    free (value->city);
    free (value);
}

void iniciaHashDrivers (char *path) {
    FILE *fp = NULL;
    drivers = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify) free_driver);
    char *filename = malloc ((strlen (path) + strlen ("/drivers.csv") +1)*sizeof (char));
    strcpy(filename,path);
    strcat (filename,"/drivers.csv");
    fp = fopen(filename,"r");
    if(!fp){
        perror("Não conseguiu abrir o ficheiro");
        return;
    }
    parser(fp,2);
    free (filename);
    fclose (fp);
}

AvC *iniciaHashAvC (char *name, char *id, char *city, double avaliacao) {
    AvC *new = malloc (sizeof (AvC));
    new->id = id;
    new->name = name;
    new->city = city;
    new-> n_viagens = 1;
    new->avaliacao_total = avaliacao;
    new-> avaliacao_media = 0;
    return new;
}

/*atribui cada token extraído ao respetivo campo da struct DRIVERS*/
void atribui_drv(DRIVERS* drv2 ,int pos,char* token){   
    switch(pos){
        case 1:
            drv2 -> id = strdup(token);
        break;
        case 2:
            drv2 -> name = strdup(token);
        break;
        case 3:
            drv2 -> birth = strdup(token);
        break;
        case 4:
            drv2 -> gender = strdup(token);
        break;
        case 5:
            drv2-> car_class = strdup(token);
        break;
        case 7:
            drv2 -> city = strdup(token);
        break;
        case 8:
            drv2 -> ac_cr = strdup(token);
        break;
        case 9:
            drv2 -> ac_st = strdup(token);
        break;
        default:
            break;
        }
}

/*função que inicializa cada driver*/
void adicionaHashDrivers(char *line){   
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    separa(line,drv2,3);
    drv2->count = 0;
    drv2->valor_atual = 0;
    drv2->idade_conta = tempo_De_Vida(strdup(drv2->ac_cr));
    drv2->mostRecentRide = NULL;
    drv2-> total_auferido = 0;
    drv2 -> avaliacao_cidades = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_avaliacao_por_cidade); 
    g_hash_table_insert(drivers, drv2 -> id, drv2);  /*depois de todos os campos da struct estarem preenchidos insere o driver na hashtable*/
}

/*atribiu um int consoante o tipo de carro do driver*/
int identifie_car_class (DRIVERS *driver) {
    if (!strcmp(driver->car_class,"basic")) return 0;
    else if (!strcmp(driver->car_class,"green")) return 1;
    else return 2;
}

int identifie_car_class_char (char *car_class) {
    if (!strcmp(car_class,"basic")) return 0;
    else if (!strcmp(car_class,"green")) return 1;
    else return 2;
}

/*adiciona a cada driver da hashtable(dos drivers) os valores dos rides que interessam para resolver a query 1, 2 e 7*/
void addToDriver(DRIVERS *driver,char *score_driver, char *date, char *distance, char *tip, char *city){   
    int r = 0;
    if(!driver->mostRecentRide) driver->mostRecentRide = strdup(date);   /*compara as duas datas*/
    else if((r = compareDates(date,driver->mostRecentRide)) != 0){   /*se a primeira data for igual ou mais recente que a segunda*/
        char *temp = driver->mostRecentRide;
        driver->mostRecentRide = strdup (date);
        free (temp);
    }
    driver->count += 1;   /*incrementa o nºtotal de viajens*/
    driver->valor_atual += strtod(score_driver,NULL);   /*incrementa o score_driver à soma total de todos os score_driver(valor_atual)*/
    
    int identifier_car = identifie_car_class (driver); 
    
    switch (identifier_car) /*calcula os valores dependendo do int q identifica o tipo de carro*/
      {
         case 0:
            driver->total_auferido += strtod (tip,NULL) + strtod (distance, NULL) * 0.62 + 3.25;
            break;
         case 1:
            driver->total_auferido += strtod (tip,NULL) + strtod (distance, NULL) * 0.79 + 4;
            break;
         case 2:
            driver->total_auferido  += strtod (tip,NULL) + strtod (distance, NULL) * 0.94 + 5.20;
            break;
         default:
            break;
      }

    if (g_hash_table_contains (driver->avaliacao_cidades, city)) {
        AvC *cidade = g_hash_table_lookup (driver->avaliacao_cidades, city);
        cidade->n_viagens ++;
        cidade->avaliacao_total += strtod (score_driver, NULL);
    }
    else {
        char *key = strdup (city);
        AvC *new = iniciaHashAvC (strdup (driver->name), strdup(driver->id), key ,strtod (score_driver, NULL));
        g_hash_table_insert (driver->avaliacao_cidades, key,new );
    }
}


DRIVERS* GetcontentD(DRIVERS *d) {
    if (d) {
        DRIVERS *copy = malloc (sizeof (DRIVERS));  
        copy-> id = strdup (d->id);
        copy-> name = strdup (d->name);
        copy-> birth = strdup (d->birth);
        copy-> car_class= strdup (d->car_class);
        copy->city= strdup (d->city);
        copy-> ac_cr = strdup (d->ac_cr);
        copy-> ac_st = strdup (d->ac_st);
        copy->gender= strdup (d->gender);
        copy->mostRecentRide= strdup (d->mostRecentRide);
        copy->avaliacao_media = d->avaliacao_media;
        copy->count = d->count;
        copy->valor_atual = d->valor_atual;
        copy->total_auferido = d->total_auferido;
        copy->avaliacao_cidades = NULL;
        return copy;
    }
    return NULL;
}

AvC* getcontentAvC (AvC *a) {
    AvC* copy = malloc (sizeof (AvC));
    copy->id = strdup (a->id); 
    copy->name = strdup (a->name);
    copy->city = strdup (a->city);
    copy->n_viagens = a->n_viagens;
    copy->avaliacao_total = a->avaliacao_total;
    copy->avaliacao_media = a->avaliacao_media;
    return copy;
}

void calcula_avaliacao_media_AvC (AvC *avaliacao) {
    avaliacao->avaliacao_media = avaliacao->avaliacao_total / avaliacao->n_viagens;
}

char *getcarD (DRIVERS *d) {
    return strdup (d->car_class);
}

char *getIdD(DRIVERS *d){
    return strdup (d->id);
}

char *getNameD(DRIVERS *d){
    return strdup (d->name);
}

double getAvaliacaoMediaD(DRIVERS *d){
    return d->avaliacao_media;
}

double getValorAtualD(DRIVERS *d){
    return d->valor_atual;
}

int getCountD(DRIVERS *d){
    return d->count;
}

int get_Idade_Conta_D(DRIVERS *d){
    return d->idade_conta;
}

char *getAccountStatusD(DRIVERS *d){
    return strdup (d->ac_st);
}

char *getMostRecentRideD(DRIVERS *d){
    return strdup (d->mostRecentRide);
}

void calculaAvaliacaoMedia(DRIVERS *d,double avaliacao_media){
    d->avaliacao_media = avaliacao_media;
}

char *getGenderD(DRIVERS *d){
    return strdup (d->gender);
}

char *getBirthD(DRIVERS *d){
    return strdup (d->birth);
}

double getTotalAuferido (DRIVERS *d) {
    return d->total_auferido;
}

double getAvaliacaoMediaAvC (AvC *a) {
    return a->avaliacao_media;
}

char *getIdAvC(AvC* a){
    return strdup (a->id);
}

char* getNameAvC (AvC *a) {
    return strdup (a->name);
}

DRIVERS* lookup_drivers (char* key) {
   return (g_hash_table_lookup (drivers, key));
}

AvC* lookup_AvC (DRIVERS *driver, char *city) {
    return (g_hash_table_lookup (driver->avaliacao_cidades, city));
}

size_t getsizeAvC () {
    return sizeof (AvC*);
}

void foreach_drivers_Q7 (char *city) {
   g_hash_table_foreach (drivers, (GHFunc)avaliacao_media_city, city);
}

void hash_table_destroy_drivers () {
    g_hash_table_destroy (drivers);
}

/*função que inicializa a struct LISTA_DRIVERS*/
void createList(){   
    lista_drivers = malloc(sizeof(LISTA_DRIVERS));
    lista_drivers->ordenado = 0;
    lista_drivers->lista = NULL;
}

int desempate_Q2(DRIVERS *p1,DRIVERS *p2){
    int result = 1;
    double avaliacao_media = p1->avaliacao_media;
    double avaliacao_media2 = p2->avaliacao_media;
    char *mostRecentRide = p1->mostRecentRide ? strdup (p1->mostRecentRide) : NULL;
    char *mostRecentRide2 = p2->mostRecentRide ? strdup(p2->mostRecentRide) : NULL;
    char *id = strdup(p1->id);
    char *id2 = strdup(p2->id);
    if (avaliacao_media > avaliacao_media2) result = -1;
    else if(avaliacao_media == avaliacao_media2){   /*desempate dos drivers(avaliação média =)->verificar as datas*/
        if(compareDates(mostRecentRide,mostRecentRide2) == 1) result = -1;   /*compareDates = 1 -> primeira data é mais recente*/
        else if(compareDates(mostRecentRide,mostRecentRide2) == 2){    /*compareDates = 2 -> as duas datas são iguais*/
            if(atoi(id) > atoi(id2)) result = -1;  /*se as datas forem iguais então compara-se os id*/
        }
    }
    free(mostRecentRide);
    free(mostRecentRide2);
    free(id);
    free(id2);
    return result;
}


/*função que vai ser aplicada a cada membro da hashtable (dos drivers)*/
void calcula_mediasQ2 (gpointer key, DRIVERS* driver, void *a){
    int count = driver->count;
    double valor_atual = driver->valor_atual;
    double avaliacao_media = driver->avaliacao_media;
    avaliacao_media = valor_atual / count;  /*calcula a avaliação média de cada driver*/
    calculaAvaliacaoMedia(driver,avaliacao_media);
    if(!lista_drivers->lista) lista_drivers->lista =  g_list_append(lista_drivers->lista,driver);
    else lista_drivers->lista = g_list_insert_sorted(lista_drivers->lista,driver,(GCompareFunc)desempate_Q2);
}


void foreach_drivers_Q2 () {
   g_hash_table_foreach (drivers,(GHFunc)calcula_mediasQ2, NULL);
}


int listOrdenado(){
    if(!lista_drivers) return 0;
    return lista_drivers->ordenado;
}


DRIVERS* getElement_Q2(int index){
    return GetcontentD(g_list_nth_data(lista_drivers->lista,index));
}

void freeList(){
    g_list_free(lista_drivers->lista);
    free(lista_drivers);
}