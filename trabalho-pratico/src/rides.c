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
   char type_car;
   int score_user;
   int score_driver;
   int distance;
};

struct arrays_Q8{
   RIDES **array_female;
   RIDES **array_male;
   int pos_female;
   int pos_male;
};

static arrays_Q8 *arrays_query8 = NULL;

void free_ride (RIDES *value) {
   free (value->id);
   free (value->date);
   free (value->driver);
   free (value->user);
   free (value->city);
   free (value->tip);
   free (value);
}

void inicializaArrays_Q8(){
   arrays_query8 = malloc(sizeof(arrays_Q8));
   arrays_query8->pos_male = 0;
   arrays_query8->pos_female = 0;
   arrays_query8->array_male = NULL;
   arrays_query8->array_female = NULL;
}

int iniciaHashRides (char *path) {
   FILE *fp = NULL;
   inicializaArrays_Q8();
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
      RIDES *copy = GetcontentR(new_ride);
      DRIVERS *driver = lookup_drivers(copy->driver);
      char gender_Driver = getGenderD(lookup_drivers(copy->driver));
      char gender_User = getGenderU(lookup_users(copy->user));
      if(gender_Driver == 'M' && gender_User == 'M'){
            arrays_query8->pos_male++;
            arrays_query8->array_male = (RIDES**) realloc(arrays_query8->array_male,arrays_query8->pos_male * sizeof(RIDES*));
            arrays_query8->array_male[arrays_query8->pos_male-1] = GetcontentR(new_ride);
      }
      else if(gender_Driver == 'F' && gender_User == 'F'){
            arrays_query8->pos_female++;
            arrays_query8->array_female = (RIDES**) realloc(arrays_query8->array_female,arrays_query8->pos_female * sizeof(RIDES*));
            arrays_query8->array_female[arrays_query8->pos_female-1] = GetcontentR(new_ride);
      }
      addToDriver(driver, copy->score_driver,copy->date,copy->distance, copy->tip);
      
      new_ride->type_car = getcarD (driver);
      
      User *user = lookup_users (copy->user);
      int car_class = identifie_car_class (driver);
      addToUser (user,copy->distance, copy->tip, car_class, copy->score_user,copy->date);
      
      addToCidades (copy->city,copy->distance, new_ride->type_car, copy->driver, getNameD(driver), copy->score_driver);
      
      // Array para a query 9
      if(strtod(new_ride->tip, NULL)) addQ9(new_ride);

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

char *getTip (RIDES *ride) {
   return strdup(ride->tip);
}

RIDES* lookup_rides (char* key) {
    return (g_hash_table_lookup (rides, key));
}

void foreach_rides_Q5 (Q5 *query5) {
   g_hash_table_foreach (rides,(GHFunc)preco_medio_Q5,query5);
}

void foreach_rides_Q6 (Q6 *q) {
   g_hash_table_foreach (rides, (GHFunc)distancia_media, q);
}

void foreach_rides_Q8_male () {
   int i;
   for(i = 0; i < arrays_query8->pos_male; i++){
      verifica_dados_Q8(arrays_query8->array_male[i]);
   }
}

void foreach_rides_Q8_female () {
   int i;
   for(i = 0; i < arrays_query8->pos_female; i++){
      verifica_dados_Q8(arrays_query8->array_female[i]);
   }
}

void free_Arrays_Q8(){
   int i,j;
   for(i = 0; i < arrays_query8->pos_female; i++){
      free_ride(arrays_query8->array_female[i]);
   }
   for(j = 0; j < arrays_query8->pos_male; j++){
      free_ride(arrays_query8->array_male[j]);
   }
   free(arrays_query8->array_female);
   free(arrays_query8->array_male);
   free(arrays_query8);
}

void hash_table_destroy_rides () {
   g_hash_table_destroy (rides);
}