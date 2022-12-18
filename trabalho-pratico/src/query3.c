#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/queries.h"
#include "../include/query3.h"

/*Função que faz print dos resultados da querie 3*/
void Q3Print(FILE *res, int N){
    int i = 0, j = 0, p = 0;
    while(i < N){ /*Ciclo que limita o print dos elementos com base no input da querie*/
        User *user = getElement_Q3(j);
        char AccSt = getAccStatusU(user);
        char *username = getUsername(user);
        char *name =getNameU(user);
        int distance = getDistance(user);
        if(AccSt == 'a'){ /*Se o status for inativo então o user é ignorado e o print não é executado*/
            fprintf(res, "%s;%s;%d\n", username, name, distance);
            i++;
            p++;
        }
        j++;
        free(username);
        free(name);
        free_user(user);
    }
}