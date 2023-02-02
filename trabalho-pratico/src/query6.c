#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/query6.h"
#include "../include/interactive.h"
#include "../include/datas.h"

double distancia_media(int limite_inferior, int limite_superior, char *city){
    int pos, max = getPosQ5Q6(),idade;
    double distancia = 0, n_viagens = 0, distancia_media = 0;
    for (pos = 0; pos < max && getTempoDeVida(pos) < limite_superior; pos++);
    if (pos < max) idade = getTempoDeVida(pos);
    while(pos < max && idade <= limite_inferior ){
        char *cityride = getcityArrays (pos);
        if (!strcmp (city, cityride)){
            n_viagens++;
            distancia += getdistanceArrays(pos);
        }
        idade = getTempoDeVida(++pos);
        free (cityride);
    }
    if(n_viagens) distancia_media = distancia / n_viagens;
    return distancia_media;
}

int printQ6(FILE *res, int modo,double distancia_media){
    char line[256] = {0};
    if(distancia_media){
        if (modo == 0)
            fprintf(res, "%.3f\n", distancia_media);
        else{
            sprintf(line, "\t%.3f", distancia_media);
            if (!copia (strdup (line))) return 0;
        }
    }
    return 1;
}

int query6Exe(FILE *res, int modo, char **argumentos){
    int r = 1;
    double distancia = distancia_media(tempo_De_Vida(strdup(argumentos[2])),tempo_De_Vida(strdup(argumentos[3])), argumentos [1]);
    r = printQ6(res,modo,distancia);
    return r;
}