#include <stdio.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/parse.h"
#include "../include/queries.h"
#include "../include/dataverification.h"

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

void free_ride (RIDES *value) {
   free (value->id);
   free (value->date);
   free (value->driver);
   free (value->user);
   free (value->city);
   free (value->tip);
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
      addToDriver(driver, copy->score_driver,copy->date,copy->distance, copy->tip, copy->city);
      
      new_ride->type_car = getcarD (driver);
      
      User *user = lookup_users (copy->user);
      int car_class = identifie_car_class (driver);
      addToUser (user,copy->distance, copy->tip, car_class, copy->score_user,copy->date);
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

void foreach_rides_Q4 (Q4 *preco) {
   g_hash_table_foreach (rides,(GHFunc)preco_medio, preco);
}

void foreach_rides_Q5 (Q5 *query5) {
   g_hash_table_foreach (rides,(GHFunc)preco_medio_Q5,query5);
}

void foreach_rides_Q6 (Q6 *q) {
   g_hash_table_foreach (rides, (GHFunc)distancia_media, q);
}

void foreach_rides_Q8 () {
   g_hash_table_foreach (rides,(GHFunc)verifica_dados_Q8, NULL);
}

void foreach_rides_Q9 (){
   g_hash_table_foreach (rides, (GHFunc)guardaQ9, NULL);
}

void hash_table_destroy_rides () {
   g_hash_table_destroy (rides);
}