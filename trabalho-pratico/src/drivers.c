#include <stdio.h>
#include <glib.h>
#include <time.h>
#include <ctype.h>
#include "../include/parse.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query7.h"
#include "../include/dataverification.h"

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
    char* ac_cr;
    char *mostRecentRide;
    GHashTable *avaliacao_cidades;
    double valor_atual;
    double avaliacao_media;
    double total_auferido;
    char ac_st;
    char gender;
    char car_class;
    int idade_conta;
    int count;
};

/*struct auxiliar usada para realizar a query 2*/
struct ARRAY_DRIVERS{
    int ordenado;
    int pos;   /*posição na qual queremos inserir o próximo driver*/
    DRIVERS **driver;   /*array de drivers*/
};

static ARRAY_DRIVERS *array = NULL;

struct Q7 { 
    AvC **array_avaliacoes;
    int pos;
};

static Q7 *arrayQ7;

void inicializaQ7 () {
    arrayQ7 = malloc (sizeof (Q7));
    arrayQ7->array_avaliacoes = NULL;
    arrayQ7->pos = 0;
}

/*função responsável por dar free dos drivers, é usada para dar free da hashtable(dos drivers)*/
void free_driver (DRIVERS *value) {   
    free (value->id);
    free (value->name);
    free (value->birth);
    free (value->ac_cr);
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
int atribui_drv(DRIVERS* drv2 ,int pos,char* token){   
    switch(pos){
        case 1:
            if (token [0] == '\0') {
                free (drv2);
                return 0;
            }
            drv2 -> id = strdup(token);
        break;
        case 2:
            if (token [0] == '\0') {
                free (drv2->id);
                free (drv2);
                return 0;
            }
            drv2 -> name = strdup(token);
        break;
        case 3:
            if (verificadata (token))
                drv2 -> birth = strdup(token);
            else {
                free (drv2->id);
                free (drv2->name);
                free (drv2);
                return 0;
            }
        break;
        case 4:
            token[0] = toupper (token[0]);
            if ((token [0]== 'M' || token [0]== 'F') && token [1] == '\0')
                drv2 -> gender = token[0];
            else {
                free (drv2->id);
                free (drv2->name);
                free (drv2->birth);
                free (drv2);
                return 0;
            }
        break;
        case 5:
            if (verificacar(token))
                drv2-> car_class = token[0];
            else {
                free (drv2->id);
                free (drv2->name);
                free (drv2->birth);
                free (drv2);      
                return 0;    
            }
        break;
        case 6:
            if (token[0] == '\0') {
                free (drv2->id);
                free (drv2->name);
                free (drv2->birth);
                free (drv2);
                return 0;
            }
        break;
        case 7:
            if (token[0] == '\0') {
                free (drv2->id);
                free (drv2->name);
                free (drv2->birth);
                free (drv2);
                return 0;
            }
        break;
        case 8:
            if (verificadata (token))
                drv2 -> ac_cr = strdup(token);
            else {
                free (drv2->id);
                free (drv2->name);
                free (drv2->birth);
                free (drv2);
                return 0;
            }
        break;
        case 9:
            if (verificastatus (token))
                drv2 -> ac_st = token[0];
            else {
                free (drv2->id);
                free (drv2->name);
                free (drv2->birth);
                free (drv2->ac_cr);
                free (drv2);
                return 0;
            }
        break;
        default:
            break;
        }
    return 1;
}

/*função que inicializa cada driver*/
void adicionaHashDrivers(char *line){   
    DRIVERS *drv2 = malloc(sizeof(DRIVERS));
    if(separa(line,drv2,3)) {
        drv2->count = 0;
        drv2->valor_atual = 0;
        drv2->idade_conta = tempo_De_Vida(strdup(drv2->ac_cr));
        drv2->mostRecentRide = NULL;
        drv2-> total_auferido = 0;
        drv2 -> avaliacao_cidades = g_hash_table_new_full (g_str_hash, g_str_equal, NULL, (GDestroyNotify)free_avaliacao_por_cidade); 
        g_hash_table_insert(drivers, drv2 -> id, drv2);  /*depois de todos os campos da struct estarem preenchidos insere o driver na hashtable*/
    }
}

/*atribiu um int consoante o tipo de carro do driver*/
int identifie_car_class (DRIVERS *driver) {
    if (driver->car_class == 'b') return 0;
    else if (driver->car_class == 'g') return 1;
    else return 2;
}

int identifie_car_class_char (char car_class) {
    if (car_class == 'b') return 0;
    else if (car_class == 'g') return 1;
    else return 2;
}

/*adiciona a cada driver da hashtable(dos drivers) os valores dos rides que interessam para resolver a query 1, 2 e 7*/
void addToDriver(DRIVERS *driver,char *score_driver, char *date, int distance, char *tip, char *city){   
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
            driver->total_auferido += strtod (tip,NULL) + distance * 0.62 + 3.25;
            break;
         case 1:
            driver->total_auferido += strtod (tip,NULL) + distance * 0.79 + 4;
            break;
         case 2:
            driver->total_auferido  += strtod (tip,NULL) + distance * 0.94 + 5.20;
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
        copy-> car_class = d->car_class;
        copy-> ac_cr = strdup (d->ac_cr);
        copy-> ac_st = d->ac_st;
        copy->gender = d->gender;
        copy->mostRecentRide = d->mostRecentRide ? strdup (d->mostRecentRide) : NULL;
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

char getcarD (DRIVERS *d) {
    return d->car_class;
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

char getAccountStatusD(DRIVERS *d){
    return d->ac_st;
}

char *getMostRecentRideD(DRIVERS *d){
    if(d->mostRecentRide) return strdup (d->mostRecentRide);
    else return NULL;
}

void calculaAvaliacaoMedia(DRIVERS *d,double avaliacao_media){
    d->avaliacao_media = avaliacao_media;
}

char getGenderD(DRIVERS *d){
    return d->gender;
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

int exist_AvC (DRIVERS *value, char *city) {
    return (g_hash_table_contains (value -> avaliacao_cidades, city));
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

/*função que inicializa a struct ARRAY_DRIVERS*/
void createArray(){   
    array = malloc(sizeof(ARRAY_DRIVERS));
    array->pos = 0;
    array->ordenado = 0;
    array->driver = NULL;
}


/*função que vai ser aplicada a cada membro da hashtable (dos drivers)*/
void calcula_mediasQ2 (gpointer key, DRIVERS* driver, void *a){
    int count = getCountD(driver);
    double valor_atual = getValorAtualD(driver);
    double avaliacao_media = getAvaliacaoMediaD(driver);
    avaliacao_media = valor_atual / count;  /*calcula a avaliação média de cada driver*/
    calculaAvaliacaoMedia(driver,avaliacao_media);
    array->pos++;
    array->driver = (DRIVERS**) realloc(array->driver,array->pos * sizeof(DRIVERS*));
    array->driver[array->pos-1] = driver;
}



void foreach_drivers_Q2 () {
   g_hash_table_foreach (drivers,(GHFunc)calcula_mediasQ2, NULL);
}

void ordena_Q2(){
    qsort (array->driver,(size_t)array->pos, sizeof(DRIVERS*), desempate_Q2);
    array->ordenado = 1;
}


int arrayOrdenado(){
    if(!array) return 0;
    return array->ordenado;
}


DRIVERS* getElement_Q2(int index){
    return GetcontentD(array->driver[index]);
}

/*função que faz free da struct ARRAY_DRIVERS*/
void freeArray(){
    if(array){
        free(array->driver);
        free(array);
    }
}

void adicionaArrayQ7 (DRIVERS *value, char *city) {
    AvC *avaliacao_cidade =  g_hash_table_lookup (value->avaliacao_cidades, city);
    avaliacao_cidade-> avaliacao_media = avaliacao_cidade -> avaliacao_total / avaliacao_cidade ->n_viagens;
    arrayQ7->pos++;
    arrayQ7->array_avaliacoes = (AvC**) realloc (arrayQ7->array_avaliacoes, arrayQ7->pos * sizeof (AvC *));
    arrayQ7->array_avaliacoes[arrayQ7->pos-1] = avaliacao_cidade;
}

void ordenaQ7 () {
    qsort (arrayQ7->array_avaliacoes,(size_t)arrayQ7->pos, getsizeAvC(), comparaAvC);
}

void free_Q7 () {
    free (arrayQ7->array_avaliacoes);
    free (arrayQ7);
}

int getPosQ7 () {
    return (arrayQ7->pos);
}

AvC *getarrayQ7pos (int i) {
    return (getcontentAvC( arrayQ7->array_avaliacoes[i]));
}

int isactive (AvC *driver) {
    return ('a' ==((DRIVERS*) (g_hash_table_lookup (drivers, driver->id)))->ac_st);
}