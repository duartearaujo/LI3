#include <stdio.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/parse.h"
#include "../include/queries.h"

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
   free (value);
}

void assignsData(RIDES* new_ride ,int pos ,char* token){
   char *str = strdup(token);
   switch(pos){
      case 1:
      new_ride->id = str;
      break;
      case 2:
      new_ride->date = str;
      break;
      case 3:
      new_ride->driver = str;
      break;
      case 4:
      new_ride->user = str;
      break;
      case 5:
      new_ride->city = str;
      break;
      case 6:
      new_ride->distance = str;
      break;
      case 7:
      new_ride->score_user = str;
      break;
      case 8:
      new_ride->score_driver = str;
      break;
      case 9:
      new_ride->tip = str;
      break;
   }
}

void newElement(HASH *hash,char *line){
   RIDES *new_ride = malloc(sizeof(RIDES));
   separa(line,new_ride,2);
   g_hash_table_insert(retornaHash(2,hash),new_ride->id,new_ride);
   DRIVERS *driver = g_hash_table_lookup(retornaHash(3,hash),new_ride->driver);
   addToDriver(driver, new_ride->score_driver,new_ride->date,new_ride->distance, new_ride->tip);
   
   User *user = g_hash_table_lookup (retornaHash (1,hash),new_ride->user);
   int car_class = identifie_car_class (driver);
   addToUser (user,new_ride->distance, new_ride->tip, car_class, new_ride->score_user,new_ride->date);
}


void lookupRide(GHashTable* hashRides){
    RIDES *s = g_hash_table_lookup(hashRides,"000000000001");
    char *key = s->user;
    printf("%s\n",key);
}