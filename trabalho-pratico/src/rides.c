#include <stdio.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/parse.h"
#include "../include/queries.h"

static GHashTable* rides;

/*struct onde vão ser armazenados os dados do ficheiro rides.csv*/
struct RIDES{ 
   char *id;
   char *date;
   char *driver;
   char *user;
   char *city;
   char *distance;
   char *score_user;
   char *score_driver;
   char *tip;
   char *type_car;
};

void free_ride (RIDES *value) {
   free (value->id);
   free (value->date);
   free (value->driver);
   free (value->user);
   free (value->city);
   free (value->distance);
   free (value->score_user);
   free (value->score_driver);
   free (value->tip);
   if (value->type_car) free (value->type_car);
   free (value);
}

void iniciaHashRides (char *path) {
   FILE *fp = NULL;
   rides = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,(GDestroyNotify) free_ride);
   char *filename = malloc ((strlen (path) + strlen ("/rides.csv") + 1)*sizeof (char));
   strcpy(filename,path);
   strcat (filename,"/rides.csv");
   fp = fopen(filename,"r");
   if(!fp){
      perror("Não conseguiu abrir o ficheiro");
      return;
   }
   parser(fp, 3);
   free (filename);
   fclose (fp);
}

void assignsData(RIDES* new_ride ,int pos ,char* token){
   switch(pos){
      case 1:
      new_ride->id = strdup(token);
      break;
      case 2:
      new_ride->date = strdup(token);
      break;
      case 3:
      new_ride->driver = strdup(token);
      break;
      case 4:
      new_ride->user = strdup(token);
      break;
      case 5:
      new_ride->city = strdup(token);
      break;
      case 6:
      new_ride->distance = strdup(token);
      break;
      case 7:
      new_ride->score_user = strdup(token);
      break;
      case 8:
      new_ride->score_driver = strdup(token);
      break;
      case 9:
      new_ride->tip = strdup(token);
      break;
   }
}

RIDES* GetcontentR(RIDES *ride){
   RIDES *copy = malloc(sizeof(RIDES));
   for(int pos = 1; pos <= 10;pos++){
      switch(pos){
         case 1:
         copy->id = strdup(ride->id);
         break;
         case 2:
         copy->date = strdup(ride->date);
         break;
         case 3:
         copy->driver = strdup(ride->driver);
         break;
         case 4:
         copy->user = strdup(ride->user);
         break;
         case 5:
         copy->city = strdup(ride->city);
         break;
         case 6:
         copy->distance = strdup(ride->distance);
         break;
         case 7:
         copy->score_user = strdup(ride->score_user);
         break;
         case 8:
         copy->score_driver = strdup(ride->score_driver);
         break;
         case 9:
         copy->tip = strdup(ride->tip);
         break;
         case 10:
         copy->type_car = (!ride->type_car) ? NULL : strdup (ride->type_car);
         break;
      }
   }
   return copy;
}

void adicionaHashRides(char *line){
   RIDES *new_ride = malloc(sizeof(RIDES));
   separa(line,new_ride,2);
   new_ride ->type_car = NULL;
   g_hash_table_insert(rides,new_ride->id,new_ride);
   RIDES *copy = GetcontentR(new_ride);
   DRIVERS *driver = lookup_drivers(copy->driver);
   addToDriver(driver, copy->score_driver,copy->date,copy->distance, copy->tip);
   
   new_ride->type_car = getcarD (driver);
   
   User *user = lookup_users (copy->user);
   int car_class = identifie_car_class (driver);
   addToUser (user,copy->distance, copy->tip, car_class, copy->score_user,copy->date);
   free_ride(copy);
}

char *getcityR (RIDES *ride) {
   return strdup(ride->city);
}

char *getcarR (RIDES *ride) {
   return strdup (ride->type_car);
}

char *getdistanceR (RIDES *ride) {
   return strdup (ride->distance);
}

char *getDateR (RIDES *ride) {
   return strdup (ride->date);
}

RIDES* lookup_rides (char* key) {
    return (g_hash_table_lookup (rides, key));
}

void foreach_rides_Q4 (Q4 *preco) {
   g_hash_table_foreach (rides,(GHFunc)preco_medio, preco);
}

void foreach_rides_Q5 (Q5 *query5) {
   g_hash_table_foreach (rides,(GHFunc)preco_medio_Q5,query5);
}

void foreach_rides_Q6 (Q6 *q) {
   g_hash_table_foreach (rides, (GHFunc)distancia_media, q);
}

void hash_table_destroy_rides () {
   g_hash_table_destroy (rides);
}