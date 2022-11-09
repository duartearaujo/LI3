#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"

int main(int argc, char **argv){
    FILE *fp = NULL;
    char *filename = NULL;
    int i = 1;
    if(argc < 2){
        fp = stdin;
    }
    else{
        while (i<=3) {
            switch (i){
                case 1: {
                    GHashTable *user = g_hash_table_new(g_str_hash, g_str_equal);
                    filename = strdup(argv[1]);
                    if(!realloc (filename, (strlen (argv[1]) + strlen ("drivers.csv"))*sizeof(char))) return 3;
                    strcat (filename,"users.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser (fp,user,i);
                    lookupUser(user);
                    fclose (fp);
                    break;
                }
                case 2: {
                    GHashTable *hashRides = g_hash_table_new(g_str_hash, g_str_equal);
                    filename = strdup(argv[1]);
                    strcat (filename,"rides.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser(fp,hashRides,i);
                    lookupRide(hashRides);
                    fclose (fp);
                    break;
                }
                case 3: {
                    GHashTable *HashDrv = g_hash_table_new(g_str_hash, g_str_equal);
                    filename = strdup(argv[1]);
                    strcat (filename,"drivers.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser(fp,HashDrv,i);
                    procura(HashDrv);
                    fclose (fp);
                    break;
                }
                default:
                    break;
            }        
            i++;
        }
    }
    return 0;
}

