#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query4.h"

struct Q4 {
    char *city;
    int n_viagens;
    double total_preco;
};

Q4* inicializaQ4 (char *city) {
    Q4 *new = malloc (sizeof (Q4));
    new->city = city;
    new->n_viagens = 0;
    new->total_preco = 0;
    return new;
}

void freeQ4 (Q4 *value) {
    free (value->city);
    free (value);
}

void preco_medio (gpointer key, RIDES *value, Q4 *total) {
    char *city = getcityR (value);
    if (!strcmp (total->city,city)) {
        total->n_viagens++;
        char *car = getcarR(value);
        char *distance = getdistanceR(value);
        switch (identifie_car_class_char(car))
        {
         case 0:
            total->total_preco += strtod (distance, NULL) * 0.62 + 3.25;
            break;
         case 1:
            total->total_preco += strtod (distance, NULL) * 0.79 + 4;
            break;
         case 2:
            total->total_preco  += strtod (distance, NULL) * 0.94 + 5.20;
            break;
         default:
            break;
        }
        free (distance);
        free (car);
    }
    free (city);
}

void printQ4 (Q4 *value, FILE *res) {
    double media = value->total_preco / value ->n_viagens; 
    fprintf (res, "%.3f\n", media);
}