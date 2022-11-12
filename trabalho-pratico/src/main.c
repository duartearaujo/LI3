#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/main.h"

struct HASH{
    GHashTable *user;
    GHashTable *ride;
    GHashTable *driver;
};

GHashTable* retornaHash(int i, HASH *hash){
    switch(i)
    {
    case 1: {
        return hash -> user;
    }     
    break;
    case 2: {
        return hash -> ride;
    }
    break;
    case 3: {
        return hash -> driver;
    }
    break;
    default:
        break;
    }
    return NULL;
}

int main(int argc, char **argv){
    FILE *fp = NULL;
    HASH *hash = malloc(sizeof(HASH));
    char *filename = malloc ((strlen (argv[1]) + strlen ("drivers.csv"))*sizeof (char));
    int i = 1;
    if(argc < 2){
        fp = stdin;
    }
    else{
        while (i<=3) {
            switch (i){
                case 1: {
                    hash -> user = g_hash_table_new(g_str_hash, g_str_equal);
                    strcpy(filename,argv[1]);
                    strcat (filename,"users.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser (fp, hash -> user, i);
                    lookupUser(hash -> user);
                    fclose (fp);
                    break;
                }
                case 2: {
                    hash -> ride = g_hash_table_new(g_str_hash, g_str_equal);
                    strcpy(filename,argv[1]);
                    strcat (filename,"rides.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser(fp, hash -> ride, i);
                    lookupRide(hash -> ride);
                    fclose (fp);
                    break;
                }
                case 3: {
                    hash -> driver = g_hash_table_new(g_str_hash, g_str_equal);
                    strcpy(filename,argv[1]);
                    strcat (filename,"drivers.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser(fp, hash -> driver, i);
                    procura(hash -> driver);
                    fclose (fp);
                    break;
                }
                default:
                    break;
            }        
            i++;
        }
    }
    //parse das queries
    fp = fopen (argv[2], "r");
    parsequerie (fp, hash);
    return 0;
}

