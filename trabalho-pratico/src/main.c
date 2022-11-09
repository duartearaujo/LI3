#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"

int main(int argc, char **argv){
    FILE *fp = NULL;
    char *filename = NULL;
    int i = 1;
    if(argc < 2){
        fp = stdin;
    }
    else{
        while (i<=1) {
            switch (i)
            {
                case 1:
                    filename = strdup(argv[1]);
                    strcat (filename,"users.csv");
                    GHashTable *user = g_hash_table_new(g_str_hash, g_str_equal);
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Error");
                        return 2;
                    }
                    parser (fp,user,i);
                    fclose (fp);
                    break;
                default:
                    break;
            }        
            i++;
        }
    }
    return 0;
}

