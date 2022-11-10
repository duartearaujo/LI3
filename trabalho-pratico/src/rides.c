#include <stdio.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/parse.h"


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
   char *comment;
};

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
      break;
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
      case 10:
      new_ride->comment = str;
      break;
   }
}


void newElement(GHashTable *hashRides, char *line){
   RIDES *new_ride = malloc(sizeof(RIDES));
   separa(line,new_ride,2);
   g_hash_table_insert(hashRides,new_ride->id,new_ride);
}


void lookupRide(GHashTable* hashRides){
    RIDES *s = g_hash_table_lookup(hashRides,"000000000001");
    char *key = s->user;
    printf("%s\n",key);
}
