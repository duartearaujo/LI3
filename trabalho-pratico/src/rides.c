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
#include "../include/datas.h"

/* Struct onde vão ser armazenados os dados do ficheiro rides.csv.*/
struct RIDES{ 
   char *id; /**< Campo para guardar o id da viagem.*/
   char *date; /**< Campo para guardar a data da viagem.*/
   char *driver; /**< Campo para guardar o id do driver da viagem.*/
   char *user; /**< Campo para guardar o username do user da viagem.*/
   char *city; /**< Campo para guardar a cidade da viagem.*/
   char *tip; /**< Campo para guardar a tip da viagem.*/
   int score_user; /**< Campo para guardar a classificação dada pelo user da viagem.*/
   int score_driver; /**< Campo para guardar a classificação dada pelo driver da viagem.*/
   int distance; /**< Campo para guardar a distância percorrida durante a viagem.*/
   int idade_viagem; /**< Campo para guardar a idade da viagem.*/
   char type_car; /**< Campo para guardar o tipo do carro utilizado na viagem.*/
};

/* Struct usada nos arrays do query 8.*/
struct q8{
   RIDES* ride;
   int idade_conta_driver;
   int idade_conta_user;
};

/* Struct que contêm todas as estruturas utilizadas para resolver as queries 5,6,8 e 9*/
struct array_RIDES {
   RIDES **array_q9;
   RIDES **arrayQ5Q6;
   q8 **array_female;  /*Array da estrutura definida acima.*/
   q8 **array_male;
   int pos_female;
   int pos_male;
   int pos_q9;
   int posQ5Q6;
};

static arrayRides *arrays = NULL;  /*Static da estrutura array_RIDES.*/

/* Função responsável por inicializar uma estrutura q8.*/
q8* inicializa_dados_Q8(){
   q8* new = malloc(sizeof(q8));
   new->idade_conta_driver = 0;
   new->idade_conta_user = 0;
   new->ride = NULL;
   return new;
}

/* Função encarregada de inicializar a estrutura array_RIDES.*/
void inicializaArrays (){
   arrays = malloc (sizeof (arrayRides));
   arrays->pos_female = 0;
   arrays->pos_male = 0;
   arrays->pos_q9 = 0;
   arrays->posQ5Q6 = 0;
   arrays->array_female = NULL;
   arrays->array_male = NULL;
   arrays->array_q9 = NULL;
   arrays->arrayQ5Q6 = NULL;
}

/* Função que inicia o parse do ficheiro dos rides(rides.csv), que por sua vez vai atribuir a informação presente no ficheiro às respetivas estruturas.*/
int iniciaEstruturasRides (char *path) {
   FILE *fp = NULL;
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

/* Função que recebe os tokens(dado do ficheiro rides.csv) e atribui-o ao respetivo campo da estrutura RIDES.*/
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

/* Cria e retorna uma cópia exata do RIDES dado como argumento.*/
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

/* Adiciona um novo elemento ao array da query 5 e 6.*/
void adicionaArrayQ5Q6(RIDES *new_ride){
   arrays->posQ5Q6++;
   arrays->arrayQ5Q6 = realloc(arrays->arrayQ5Q6,arrays->posQ5Q6 * sizeof(RIDES*));
   arrays->arrayQ5Q6[arrays->posQ5Q6-1] = new_ride;
}

/* Função que adiciona elementos a grande parte das estruturas usadas no projeto.*/
void adicionaEstruturasRides(char *line){
   RIDES *new_ride = malloc(sizeof(RIDES));
   if (separa(line,new_ride,2)) {
      new_ride ->idade_viagem = tempo_De_Vida (strdup(new_ride->date));

      RIDES *copy = GetcontentR(new_ride);
      DRIVERS *driver = lookup_drivers(copy->driver);
      char gender_Driver = getGenderD(lookup_drivers(copy->driver));
      char gender_User = getGenderU(lookup_users(copy->user));
      char account_status_driver = getAccountStatusD(lookup_drivers(new_ride->driver));
      char account_status_user = getAccStatusU(lookup_users(new_ride->user));
      if(account_status_driver == 'a' && account_status_user == 'a'){  /*Verifica se o driver e o user estão ambos ativos.*/
         if(gender_Driver == 'M' && gender_User == 'M'){  /*Verifica se o driver e o user são ambos homens.*/
            q8* dados = inicializa_dados_Q8();
            dados->ride = new_ride;
            dados->idade_conta_driver = get_Idade_Conta_D(lookup_drivers(new_ride->driver));
            dados->idade_conta_user = get_Idade_Conta_U(lookup_users(new_ride->user));
            arrays->pos_male++;
            arrays->array_male = (q8**) realloc(arrays->array_male,arrays->pos_male * sizeof(q8*));
            arrays->array_male[arrays->pos_male-1] = dados;
         }
         else if(gender_Driver == 'F' && gender_User == 'F'){  /*Verifica se o driver e o user são ambos mulheres.*/
            q8* dados = inicializa_dados_Q8();
            dados->ride = new_ride;
            dados->idade_conta_driver = get_Idade_Conta_D(lookup_drivers(new_ride->driver));
            dados->idade_conta_user = get_Idade_Conta_U(lookup_users(new_ride->user));
            arrays->pos_female++;
            arrays->array_female = (q8**) realloc(arrays->array_female,arrays->pos_female * sizeof(q8*));
            arrays->array_female[arrays->pos_female-1] = dados;
         }
      }
      addToDriver(driver, copy->score_driver,copy->date,copy->distance, copy->tip);
      
      new_ride->type_car = getcarD (driver);
      
      User *user = lookup_users (copy->user);
      int car_class = identifie_car_class (driver);
      addToUser (user,copy->distance, copy->tip, car_class, copy->score_user,copy->date);
      
      addToCidades (copy->city,copy->distance, getcarD (driver), copy->driver, getNameD(driver), copy->score_driver);

      if (strtod(new_ride->tip, NULL)) addQ9 (new_ride);
      adicionaArrayQ5Q6(new_ride);
      free_ride(copy);
   }
}

/* Retorna a cidade do RIDES.*/
char *getcityR (RIDES *ride) {
   return strdup(ride->city);
}

/* Retorna a cidade do elemento que se encontra numa posição em específico do array da query 5 e 6.*/
char* getcityArrays (int pos){
   return strdup (arrays->arrayQ5Q6[pos]->city);
}

/* Retorna o tipo do carro do RIDES.*/
char getcarR (RIDES *ride) {
   return ride->type_car;
}

/* Retorna o tipo do carro do elemento que se encontra numa posição em específico do array da query 5 e 6.*/
char getcarArrays (int pos) {
   return arrays->arrayQ5Q6[pos]->type_car;
}

/* Retorna a distância do RIDES.*/
int getdistanceR (RIDES *ride) {
   return ride->distance;
}

/* Retorna a distância do elemento que se encontra numa posição em específico do array da query 5 e 6.*/
int getdistanceArrays (int pos){
   return arrays->arrayQ5Q6[pos]->distance;
}

/* Retorna a posição final de um dos arrays da query 8(a posição retornada depende do sexo dado como argumento na query 8).*/
int getPosQ8 (char gender){
   if(gender == 'M') return arrays->pos_male;
   else if(gender == 'F') return arrays->pos_female;
   return 0;
}

/* Retorna a idade da conta do driver de um elemento em específico de um dos arrays da query 8(o valor retornado depende do sexo dado como argumento na 
query 8).
*/
int get_Idade_Conta_DriverQ8(int pos,char gender){
   if(gender == 'M') return arrays->array_male[pos]->idade_conta_driver;
   else if(gender == 'F') return arrays->array_female[pos]->idade_conta_driver;
   return 0;
}

/* Retorna a idade da conta do user de um elemento em específico de um dos arrays da query 8(o valor retornado depende do sexo dado como argumento na 
query 8).
*/
int get_Idade_Conta_UserQ8(int pos,char gender){
   if(gender == 'M') return arrays->array_male[pos]->idade_conta_user;
   else if(gender == 'F') return arrays->array_female[pos]->idade_conta_user;
   return 0;
}

/* Retorna o username de um elemento em específico de um dos arrays da query 8(o valor retornado depende do sexo dado como argumento na 
query 8).
*/
char *getUsernameQ8(int pos,char gender){
   if(gender == 'M') return strdup(arrays->array_male[pos]->ride->user);
   if(gender == 'F') return strdup(arrays->array_female[pos]->ride->user);
   return NULL;
}

/* Retorna o id do driver de um elemento em específico de um dos arrays da query 8(o valor retornado depende do sexo dado como argumento na 
query 8).
*/
char *getIdDriverQ8(int pos,char gender){
   if(gender == 'M') return strdup(arrays->array_male[pos]->ride->driver);
   if(gender == 'F') return strdup(arrays->array_female[pos]->ride->driver);
   return NULL;
}

/* Retorna o nome do driver de um elemento em específico de um dos arrays da query 8(o valor retornado depende do sexo dado como argumento na 
query 8).
*/
char *getNomeDriverQ8(int pos,char gender){
   if(gender == 'M') return getNameD(lookup_drivers(arrays->array_male[pos]->ride->driver));
   if(gender == 'F') return getNameD(lookup_drivers(arrays->array_female[pos]->ride->driver));
   return NULL;
}

/* Retorna o nome do user de um elemento em específico de um dos arrays da query 8(o valor retornado depende do sexo dado como argumento na 
query 8).
*/
char *getNomeUserQ8(int pos,char gender){
   if(gender == 'M') return getNameU(lookup_users(arrays->array_male[pos]->ride->user));
   if(gender == 'F') return getNameU(lookup_users(arrays->array_female[pos]->ride->user));
   return NULL;
}

/* Retorna a posição final do array da query 5 e 6.*/
int getPosQ5Q6 () {
   return arrays->posQ5Q6;
}

/* Retorna a idade da viagem de um elemento que se encontra numa posição específica do array das queries 5 e 6.*/
int getTempoDeVida(int pos){
   return (arrays->arrayQ5Q6[pos]->idade_viagem);
}

/* Retorna o username do RIDES.*/
char *getUsernameR (RIDES *ride) {
   return strdup (ride->user);
}

/* Retorna o id do driver do RIDES.*/
char *getIdDriverR (RIDES *ride) {
   return strdup (ride->driver);
}

/* Retorna o id do RIDES.*/
char *getIdR (RIDES *ride) {
   return strdup (ride->id);
}

/* Retorna a data do RIDES.*/
char *getDateR (RIDES *ride) {
   return strdup (ride->date);
}

/* Retorna a tip do RIDES.*/
double getTip (RIDES *ride) {
   return strtod(ride->tip,NULL);
}

/* Retorna a idade da viagem do RIDES.*/
int getIdadeViagem (RIDES *ride) {
   return ride->idade_viagem;
}

/* Retorna o id de um elemento que se encontra numa posição específica do array da query 9.*/
char* getId_Q9 (int pos) {
   return (strdup(arrays->array_q9[pos]->id));
}

/* Retorna a data de um elemento que se encontra numa posição específica do array da query 9.*/
char* getDate_Q9 (int pos) {
   return (strdup(arrays->array_q9[pos]->date));
}

/* Retorna a cidade de um elemento que se encontra numa posição específica do array da query 9.*/
char* getCity_Q9 (int pos) {
   return (strdup(arrays->array_q9[pos]->city));
}

/* Retorna a distância de um elemento que se encontra numa posição específica do array da query 9.*/
int getDistance_Q9 (int pos) {
   return (arrays->array_q9[pos]->distance);
}

/* Retorna a tip de um elemento que se encontra numa posição específica do array da query 9.*/
double getTip_Q9 (int pos) {
   return (strtod (arrays->array_q9[pos]->tip, NULL));
}

/* Retorna a idade da viagem de um elemento que se encontra numa posição específica do array da query 9.*/
int getIdadeViagem_Q9 (int pos) {
   return arrays->array_q9[pos]->idade_viagem;
}

/* Retorna a posição final do array da query 9.*/
int getposQ9 () {
   return arrays->pos_q9;
}

/* Adiciona um novo elemento ao array da query 9.*/
void addQ9(RIDES *ride){                  
    arrays->pos_q9++;
    arrays->array_q9 = (RIDES**) realloc(arrays->array_q9,arrays->pos_q9 * sizeof(RIDES*));
    arrays->array_q9[(arrays->pos_q9 - 1)] = ride;
}

/* Método de ordenação utilizado para ordenar o array das queries 5 e 6.*/
int ordenaQ5Q6(const void *p1, const void* p2) {
   RIDES *dados_1 = *((RIDES**) p1);
   RIDES *dados_2 = *((RIDES**) p2);
   int result = -1;
   if(dados_1->idade_viagem > dados_2->idade_viagem) result = 1;
   else if(dados_1->idade_viagem == dados_2->idade_viagem) result = 0;
   return result;
}

/* Ordena o array das queries 5 e 6 a partir do valor da idade da viagem de cada elemento(tal processo está explícito na função 'ordenaQ5Q6').*/
void ordena_Q5Q6(){
   qsort (arrays->arrayQ5Q6,(size_t)arrays->posQ5Q6, sizeof(RIDES*), ordenaQ5Q6);
}

/* Método de ordenação utilizado para ordenar os arrays da query 8.*/
int desempate_Q8(const void *p1, const void* p2){
   q8 *dados_1 = *((q8**) p1);
   q8 *dados_2 = *((q8**) p2);
   int result = 1;
   int idade_conta_driver = dados_1->idade_conta_driver;
   int idade_conta_driver2 = dados_2->idade_conta_driver;
   int idade_conta_user = dados_1->idade_conta_user;
   int idade_conta_user2 = dados_2->idade_conta_user;
   char *id = dados_1->ride->id;
   char *id2 = dados_2->ride->id;
   if (idade_conta_driver > idade_conta_driver2) result = -1;  /*Ordena a partir da idade da conta do driver.*/
   else if(idade_conta_driver== idade_conta_driver2){
      if(idade_conta_user > idade_conta_user2) result = -1;  /*(Idade da conta do driver ==) -> o desempate é feito através da idade da conta do user.*/
      else if(idade_conta_user == idade_conta_user2){
         if(atoi(id) < atoi(id2)) result = -1;  /*(Idade da conta do driver e do user ==) -> o desempate é feito através do id da viagem.*/
      }
   }
   return result;
}

/* Ordena os arrays da query 8(método de ordenação explícito na função 'desempate_Q8').*/
void ordena_Q8(){  
   qsort (arrays->array_male,(size_t)arrays->pos_male, sizeof(q8*), desempate_Q8);
   qsort (arrays->array_female,(size_t)arrays->pos_female, sizeof(q8*), desempate_Q8);
}

/* Ordena o array da query 9(método de ordenação explícito na função 'desempate_Q9').*/
void ordena_Q9(){  
   qsort (arrays->array_q9,(size_t)arrays->pos_q9, sizeof(RIDES*), desempate_Q9);
}

/* Função que faz free de um RIDES.*/
void free_ride (RIDES *value) {
   free (value->id);
   free (value->date);
   free (value->driver);
   free (value->user);
   free (value->city);
   free (value->tip);
   free (value);
}

/* Função encarregada de fazer free de uma estrutura q8.*/
void freeQ8(q8* dados){
   free(dados);
}

/* Função encarregada de fazer free da estrutura array_RIDES.*/
void freeArrays(){
   if(arrays){
      int i;
      free(arrays->array_q9);
      for(i = 0; i < arrays->posQ5Q6;i++){
         free_ride(arrays->arrayQ5Q6[i]);
      }
      free(arrays->arrayQ5Q6);
      for(i = 0; i < arrays->pos_male;i++){
         freeQ8(arrays->array_male[i]);
      }
      for(i = 0; i < arrays->pos_female;i++){
         freeQ8(arrays->array_female[i]);
      }
      free(arrays->array_male);
      free(arrays->array_female);
      free(arrays);
   }
}