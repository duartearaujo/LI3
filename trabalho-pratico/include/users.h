#ifndef users
#define users

#include <glib.h>

typedef struct user User;

void free_user(User *value);

void criaHashUser (HASH *hash, char *line);

void atribui (User* user, int pos, char *info);

int lookupUser (GHashTable *user, FILE *res, char *name);

void addToUser (User *user, char *distance, char *tip, int car_class , char *avaliation, char *date);

User* GetcontentU(User *u);

char *getNameU (User *u);

char *getGenderU (User *u);

char *getAccStatusU (User *u);

char *getDataU (User *u);

int getNViagensU (User *u);

double getTotalGastoU (User *u);

double getAccAvaliationU (User *u);

char *getUsername(User* user);

char *getLastRide(User* user);

int getDistance(User* user);

char *getAccSt(User* user);



#endif