#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"

struct Q5{
    char *data_inferior;
    char *data_superior;
    int numeroViagens;
    double total_preco;
};

Q5* inicializaQ5(char *data_inferior, char *data_superior){
    Q5* query5 = malloc(sizeof(Q5));
    query5->data_inferior = data_inferior;
    query5->data_superior = data_superior;
    query5->numeroViagens = 0;
    query5->total_preco = 0;
    return query5;
}

void freeQ5 (Q5 *query5) {
    free (query5->data_inferior);
    free(query5->data_superior);
    free (query5);
}

void preco_medio_Q5(gpointer key, RIDES *value, Q5 *query5){
    char *data = getDateR(value);
    if((compareDates(data,query5->data_inferior) && !compareDates(data,query5->data_superior)) || !strcmp(data,query5->data_inferior) || !strcmp(data,query5->data_superior)){
        query5->numeroViagens++;
        char *carro = getcarR(value);
        char *distancia = getdistanceR(value);
        switch (identifie_car_class_char(carro))
        {
         case 0:
            query5->total_preco += strtod (distancia, NULL) * 0.62 + 3.25;
            break;
         case 1:
            query5->total_preco += strtod (distancia, NULL) * 0.79 + 4;
            break;
         case 2:
            query5->total_preco  += strtod (distancia, NULL) * 0.94 + 5.20;
            break;
         default:
            break;
        }
        free(carro);
        free(distancia);
    }
    free(data);
}

void printQ5 (Q5 *query5, FILE *res) {
    double valor_medio = query5->total_preco / query5->numeroViagens; 
    fprintf (res, "%.3f\n", valor_medio);
}