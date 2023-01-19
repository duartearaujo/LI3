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

/*struct onde vão ser armazenados os dados do ficheiro drivers.csv*/
struct DRIVERS{   
    char* id;
    char* name;
    char* birth;
    char* ac_cr;
    char *mostRecentRide;
    double avaliacao_media;
    double total_auferido;
    char ac_st;
    char gender;
    char car_class;
    int valor_atual;
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

/*função responsável por dar free dos drivers, é usada para dar free da hashtable(dos drivers)*/
void free_driver (DRIVERS *value) {   
    free (value->id);
    free (value->name);
    free (value->birth);
    free (value->ac_cr);
    free (value->mostRecentRide);
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
void addToDriver(DRIVERS *driver,int score_driver, char *date, int distance, char *tip){   
    int r = 0;
    if(!driver->mostRecentRide) driver->mostRecentRide = strdup(date);   /*compara as duas datas*/
    else if((r = compareDates(date,driver->mostRecentRide)) != 0){   /*se a primeira data for igual ou mais recente que a segunda*/
        char *temp = driver->mostRecentRide;
        driver->mostRecentRide = strdup (date);
        free (temp);
    }
    driver->count += 1;   /*incrementa o nºtotal de viajens*/
    driver->valor_atual += score_driver;   /*incrementa o score_driver à soma total de todos os score_driver(valor_atual)*/
    
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
        return copy;
    }
    return NULL;
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

int getValorAtualD(DRIVERS *d){
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

char getGenderD(DRIVERS *d){
    return d->gender;
}

char *getBirthD(DRIVERS *d){
    return strdup (d->birth);
}

double getTotalAuferido (DRIVERS *d) {
    return d->total_auferido;
}

DRIVERS* lookup_drivers (char* key) {
   return (g_hash_table_lookup (drivers, key));
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
    int valor_atual = getValorAtualD(driver);
    double avaliacao_media = 0;
    if (count) avaliacao_media = (double)valor_atual / (double)count;  /*calcula a avaliação média de cada driver*/
    driver->avaliacao_media = avaliacao_media;
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