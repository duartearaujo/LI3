#include <stdio.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/parse.h"
#include "../include/queries.h"
#include "../include/query9.h"
#include "../include/dataverification.h"
#include "../include/cidades.h"

static GHashTable* rides;

/*struct onde vão ser armazenados os dados do ficheiro rides.csv*/
struct RIDES{ 
   char *id;
   char *date;
   char *driver;
   char *user;
   char *city;
   char *tip;
   int score_user;
   int score_driver;
   int distance;
   int idade_viagem;
   char type_car;
};

struct array_Q9 {
   RIDES **array;
   int pos;
};

static array_Q9 *array_q9 = NULL;

void free_ride (RIDES *value) {
   free (value->id);
   free (value->date);
   free (value->driver);
   free (value->user);
   free (value->city);
   free (value->tip);
   free (value);
}

void inicializaQ9 (){
   array_q9 = malloc (sizeof (array_Q9));
   array_q9->pos = 0;
   array_q9->array = NULL;
}


int iniciaHashRides (char *path) {
   FILE *fp = NULL;
   rides = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,(GDestroyNotify) free_ride);
   char *filename = malloc ((strlen (path) + strlen ("/rides.csv") + 1)*sizeof (char));
   strcpy(filename,path);
   strcat (filename,"/rides.csv");
   fp = fopen(filename,"r");
   if(!fp){
      perror("Não conseguiu abrir o ficheiro");
      return 0;
   }
   parser(fp, 3);
   free (filename);
   fclose (fp);
   return 1;
}

int assignsData(RIDES* new_ride ,int pos ,char* token){
   switch(pos){
      case 1:
         if (token[0] == '\0') {
            free (new_ride);
            return 0;
         }         
         new_ride->id = strdup(token);
      break;
      case 2:
         if (verificadata (token))
            new_ride->date = strdup(token);
         else {
            free (new_ride->id);
            free (new_ride);
            return 0;
         }
      break;
      case 3:
         if (token[0] == '\0') {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride);
            return 0;
         }
         new_ride->driver = strdup(token);
      break;
      case 4:
         if (token[0] == '\0') {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride->driver);
            free (new_ride);
            return 0;
         }
         new_ride->user = strdup(token);
      break;
      case 5:
         if (token[0] == '\0') {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride->driver);
            free (new_ride->user);
            free (new_ride);
            return 0;
         }
         new_ride->city = strdup(token);
      break;
      case 6:
         if (verificadistancia (token))
            new_ride->distance = atoi(token);
         else {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride->driver);
            free (new_ride->user);
            free (new_ride->city);
            free (new_ride);
            return 0;
         }
      break;
      case 7:
         if (verificaavaliacao (token))
            new_ride->score_user = atoi(token);
         else {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride->driver);
            free (new_ride->user);
            free (new_ride->city);
            free (new_ride);
            return 0;
         }
      break;
      case 8:
         if (verificaavaliacao (token))
            new_ride->score_driver = atoi(token);
         else {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride->driver);
            free (new_ride->user);
            free (new_ride->city);
            free (new_ride);
            return 0;
         }
      break;
      case 9:
         if (verificatip (token))
            new_ride->tip = strdup(token);
         else {
            free (new_ride->id);
            free (new_ride->date);
            free (new_ride->driver);
            free (new_ride->user);
            free (new_ride->city);
            free (new_ride);
            return 0;
         }
      break;
      default:
         break;
   }
   return 1;
}

RIDES* GetcontentR(RIDES *ride){
   if (ride) {
      RIDES *copy = malloc(sizeof(RIDES));
      copy->id = strdup(ride->id);
      copy->date = strdup(ride->date);
      copy->driver = strdup(ride->driver);
      copy->user = strdup(ride->user);
      copy->city = strdup(ride->city);
      copy->distance = ride->distance;
      copy->score_user = ride->score_user;
      copy->score_driver = ride->score_driver;
      copy->tip = strdup(ride->tip);
      copy->type_car = ride->type_car;
      return copy;
   }
   return NULL;
}


void adicionaHashRides(char *line){
   RIDES *new_ride = malloc(sizeof(RIDES));
   if (separa(line,new_ride,2)) {
      g_hash_table_insert(rides,new_ride->id,new_ride);
      new_ride ->idade_viagem = tempo_De_Vida (strdup(new_ride->date));

      RIDES *copy = GetcontentR(new_ride);
      DRIVERS *driver = lookup_drivers(copy->driver);
      addToDriver(driver, copy->score_driver,copy->date,copy->distance, copy->tip);
      
      new_ride->type_car = getcarD (driver);
      
      User *user = lookup_users (copy->user);
      int car_class = identifie_car_class (driver);
      addToUser (user,copy->distance, copy->tip, car_class, copy->score_user,copy->date);
      
      addToCidades (copy->city,copy->distance, getcarD (driver), copy->driver, getNameD(driver), copy->score_driver);

      if (strtod(new_ride->tip, NULL)) addQ9 (new_ride);

      free_ride(copy);
   }
}

char *getcityR (RIDES *ride) {
   return strdup(ride->city);
}

char getcarR (RIDES *ride) {
   return ride->type_car;
}

int getdistanceR (RIDES *ride) {
   return ride->distance;
}

char *getUsernameR (RIDES *ride) {
   return strdup (ride->user);
}

char *getIdDriverR (RIDES *ride) {
   return strdup (ride->driver);
}

char *getIdR (RIDES *ride) {
   return strdup (ride->id);
}

char *getDateR (RIDES *ride) {
   return strdup (ride->date);
}

double getTip (RIDES *ride) {
   return strtod(ride->tip,NULL);
}

RIDES* lookup_rides (char* key) {
    return (g_hash_table_lookup (rides, key));
}

int getIdadeViagem (RIDES *ride) {
   return ride->idade_viagem;
}

char* getId_Q9 (int pos) {
   return (strdup(array_q9->array[pos]->id));
}

char* getDate_Q9 (int pos) {
   return (strdup(array_q9->array[pos]->date));
}

char* getCity_Q9 (int pos) {
   return (strdup(array_q9->array[pos]->city));
}

int getDistance_Q9 (int pos) {
   return (array_q9->array[pos]->distance);
}

double getTip_Q9 (int pos) {
   return (strtod (array_q9->array[pos]->tip, NULL));
}

int getIdadeViagem_Q9 (int pos) {
   return array_q9->array[pos]->idade_viagem;
}

int getposQ9 () {
   return array_q9->pos;
}

void foreach_rides_Q5 (Q5 *query5) {
   g_hash_table_foreach (rides,(GHFunc)preco_medio_Q5,query5);
}

void foreach_rides_Q6 (Q6 *q) {
   g_hash_table_foreach (rides, (GHFunc)distancia_media, q);
}

void foreach_rides_Q8 () {
   g_hash_table_foreach(rides,(GHFunc)verifica_dados_Q8, NULL);
}

void hash_table_destroy_rides () {
   g_hash_table_destroy (rides);
}

void addQ9(RIDES *ride){                  
    array_q9->pos++;
    array_q9->array = (RIDES**) realloc(array_q9->array,array_q9->pos * sizeof(RIDES*));
    array_q9->array[(array_q9->pos - 1)] = ride;
}

void ordena_Q9(){  
    qsort (array_q9->array,(size_t)array_q9->pos, sizeof(RIDES*), desempate_Q9);
}

void freeArrayQ9(){
    if(array_q9){
        free(array_q9->array);
        free(array_q9);
    }
}