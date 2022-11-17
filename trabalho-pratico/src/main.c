#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/main.h"

/*struct que tem dentro todas as hashtables*/
struct HASH{  
    GHashTable *user;
    GHashTable *ride;
    GHashTable *driver;
};

/*retorna a hashTable de acordo com o valor de i recebido*/
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

/*função main do projeto*/
int main(int argc, char **argv){  
    FILE *fp = NULL;
    HASH *hash = malloc(sizeof(HASH));
    int i = 1;
    if(argc < 2){
        fp = stdin;
    }
    else{
        while (i<=3) {
            switch (i){  /*cria a hashtable consoante o valor do i*/
                case 1: {
                    hash -> user = g_hash_table_new_full(g_str_hash, g_str_equal,NULL, (GDestroyNotify)free_user);  /*cria a hashtable dos users*/
                    char *filename = malloc ((strlen (argv[1]) + strlen ("/users.csv") + 1)*sizeof (char));  /*alloca espaço para o input(path dos ficheiros) + o nome do ficheiro que se pretende ler*/
                    strcpy(filename,argv[1]);
                    strcat (filename,"/users.csv");  /*concat do path dos ficheiros mais o nome do ficheiro que se vai ler neste case*/
                    fp = fopen(filename,"r");  /*abre o ficheiro*/
                    if(!fp){
                        perror("Não conseguiu abrir o ficheiro");
                        return 2;
                    }
                    parser (fp,hash, i);  /*faz o parse do ficheiro*/
                    free (filename);  /*free do path*/
                    fclose (fp);  /*fecha o ficheiro*/
                    break;
                }
                case 2: {  /*a mesma coisa do case anterior mas aplicado aos drivers*/
                    hash -> driver = g_hash_table_new_full(g_str_hash, g_str_equal, NULL, (GDestroyNotify) free_driver);
                    char *filename = malloc ((strlen (argv[1]) + strlen ("/drivers.csv") +1)*sizeof (char));
                    strcpy(filename,argv[1]);
                    strcat (filename,"/drivers.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Não conseguiu abrir o ficheiro");
                        return 2;
                    }
                    parser(fp,hash, i);
                    free (filename);
                    fclose (fp);
                    break;
                }
                case 3: {  /*a mesma coisa do case anterior mas aplicado às rides*/
                    hash -> ride = g_hash_table_new_full(g_str_hash, g_str_equal,NULL,(GDestroyNotify) free_ride);
                    char *filename = malloc ((strlen (argv[1]) + strlen ("/rides.csv") + 1)*sizeof (char));
                    strcpy(filename,argv[1]);
                    strcat (filename,"/rides.csv");
                    fp = fopen(filename,"r");
                    if(!fp){
                        perror("Não conseguiu abrir o ficheiro");
                        return 2;
                    }
                    parser(fp,hash, i);
                    free (filename);
                    fclose (fp);
                    break;
                }
                default:
                    break;
            }        
            i++;
        }
    }
    /*parse das queries*/
    fp = fopen (argv[2], "r");  /*abre o ficheiro com os testes(queries)*/
    parsequerie (fp, hash);  /*parse das queries*/

    /*free das hashes e mais*/
    fclose (fp);
    g_hash_table_destroy (hash->user);
    g_hash_table_destroy (hash->ride);
    g_hash_table_destroy (hash->driver);
    free (hash);
    return 0;
}
