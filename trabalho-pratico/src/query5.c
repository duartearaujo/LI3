#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/interactive.h"

struct Q5{
    int data_inferior;
    int data_superior;
    int numeroViagens;
    double total_preco;
};

Q5* inicializaQ5(char *data_inferior, char *data_superior){
    Q5* query5 = malloc(sizeof(Q5));
    query5->data_inferior = tempo_De_Vida(data_inferior);
    query5->data_superior = tempo_De_Vida(data_superior);
    query5->numeroViagens = 0;
    query5->total_preco = 0;
    return query5;
}

void freeQ5 (Q5 *query5) {
    free (query5);
}

void preco_medio_Q5(gpointer key, RIDES *value, Q5 *query5){
    char *data = getDateR(value);
    int tempo = tempo_De_Vida(data);
    if((tempo != -1 && query5->data_inferior != -1 && query5->data_superior != -1) && (tempo <= query5->data_inferior && tempo >= query5->data_superior)){
        query5->numeroViagens++;
        char carro = getcarR(value);
        int distancia = getdistanceR(value);
        switch (identifie_car_class_char(carro))
        {
         case 0:
            query5->total_preco += distancia * 0.62 + 3.25;
            break;
         case 1:
            query5->total_preco += distancia * 0.79 + 4;
            break;
         case 2:
            query5->total_preco  += distancia * 0.94 + 5.20;
            break;
         default:
            break;
        }
    }
}

void printQ5 (Q5 *query5, FILE *res, int modo, int *informacoespaginas, char *paginas[][linhas_por_pagina]) {
    if(query5->numeroViagens){
        double valor_medio = query5->total_preco / query5->numeroViagens; 
        if (modo == 0)
            fprintf (res, "%.3f\n", valor_medio);
        else{
            mvprintw (informacoespaginas[0]++, 0, "\t%.3f", valor_medio);
            if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
        }
    }
}

void query5Exe(FILE *res, int modo, char **argv, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    Q5* query5 = inicializaQ5 (strdup(argv[1]),strdup(argv[2]));
        foreach_rides_Q5(query5);
        printQ5(query5, res, modo, informacoespaginas, paginas);
        freeQ5(query5);
}