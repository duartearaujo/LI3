#include <stdio.h>
#include <stdlib.h>
#include "../include/rides.h"
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/parse.h"
#include "../include/queries.h"


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

struct RIDES_AM{
   char *id;
   int count;
   double valor_atual;
   double avaliacao_media;
   char *mostRecentRide;
};

struct ARRAYS_RIDES{
   int *verificacao;
   int tamanho;
   RIDES_AM **rides_am;
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

ARRAYS_RIDES* createArray(int N){
   ARRAYS_RIDES *ride = malloc(sizeof(ARRAYS_RIDES));
   int *verify = malloc(sizeof(int) * N);
   for(int i = 0; i < N;i++){
      verify[i] = 0;
   }
   ride->verificacao = verify;
   ride->rides_am = malloc(sizeof(RIDES_AM) * N); 
   ride->tamanho = N;
   return ride;
}

void printfArray(FILE *res, ARRAYS_RIDES *array,GHashTable* driver,int N){
   for(int i = 9999; i > 9999-N ;i--){
      char* str = lookupName(driver,array->rides_am[i]->id);
      fprintf(res,"%s;%s;%.3f\n",array->rides_am[i]->id,str,array->rides_am[i]->avaliacao_media);
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
   addToUser (user,new_ride->distance, new_ride->tip, car_class, new_ride->score_user);
}


void lookupRide(GHashTable* hashRides){
    RIDES *s = g_hash_table_lookup(hashRides,"000000000001");
    char *key = s->user;
    printf("%s\n",key);
}

RIDES_AM* createNewElement(RIDES *value){
   RIDES_AM *ride = malloc(sizeof(RIDES_AM));
   ride->id = strdup(value->driver);
   ride->valor_atual = strtod(value->score_driver,NULL);
   ride->count = 1;
   ride->avaliacao_media = ride->valor_atual / ride->count;
   ride->mostRecentRide = strdup(value->date);
   return ride;
}

void calcula_mediasQ2 (gpointer key, RIDES *value, ARRAYS_RIDES *user_data){
   int i = 0;
   int r = 0;
   int casoDeParagem = 0;
   while(i < user_data->tamanho && casoDeParagem == 0){
      if(user_data->verificacao[i] == 0){
         user_data->rides_am[i] = createNewElement(value);
         user_data->verificacao[i] = 1;
         casoDeParagem = 1;
      }
      else if(strcmp(user_data->rides_am[i]->id,value->driver) == 0){
         if(!(r = compareDates(user_data->rides_am[i]->mostRecentRide,value->date))) user_data->rides_am[i]->mostRecentRide = value->date;
         user_data->rides_am[i]->valor_atual += strtod(value->score_driver,NULL);
         user_data->rides_am[i]->count++;
         user_data->rides_am[i]->avaliacao_media = user_data->rides_am[i]->valor_atual / user_data->rides_am[i]->count;
         casoDeParagem = 2;
      }
      i++;
   }
}

void swap(RIDES_AM** array, int a, int b){
  RIDES_AM *t = array[a];
  array[a] = array[b];
  array[b] = t;
}


void ordenaArray(ARRAYS_RIDES* array,int N) {
   int i, j, m;
   for (i = array->tamanho; i > N; i--) {
   m = 0;
   for (j = 0; j < i; j++)
   if (array->rides_am[j]->avaliacao_media > array->rides_am[m]->avaliacao_media) m = j;
      swap(array->rides_am, i-1, m);
   }
}