#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/cidades.h"
#include "../include/queries.h"
#include "../include/query6.h"
#include "../include/interactive.h"
#include "../include/datas.h"

/*Função que calcula a distância média percorrida na cidade recebida como argumento, no intervalo de tempo especificado*/
double distancia_media(int limite_inferior, int limite_superior, char *city){
    int pos, max = getPosQ5Q6(),idade;
    double distancia = 0, n_viagens = 0, distancia_media = 0;
    if (getTempoDeVida (max-1) > limite_superior && existscity (city)) {
        for (pos = 0; pos < max && getTempoDeVida(pos) < limite_superior; pos++); /*Ciclo para obter a posição da data limite superior (mais recente)*/
        if (pos < max) idade = getTempoDeVida(pos);
        while(pos < max && idade <= limite_inferior ){ /*Ciclo que limita o cálculo da distancia total com base na data limite inferior (mais antiga)*/
            char *cityride = getcityArrays (pos);
            if (!strcmp (city, cityride)){ /*Verifica se a cidade da ride é a que queremos*/
                n_viagens++;
                distancia += getdistanceArrays(pos);
            }
            idade = getTempoDeVida(++pos);
            free (cityride);
        }
        if(n_viagens) distancia_media = distancia / n_viagens;
    }
    return distancia_media;
}

/*Função que faz o print dos resultados da query 6*/
int printQ6(FILE *res, int modo,double distancia_media){
    char line[256] = {0};
    if(distancia_media){
        if (modo == 0) /*Modo batch*/
            fprintf(res, "%.3f\n", distancia_media);
        else{ /*Modo interativo*/
            sprintf(line, "\t%.3f", distancia_media);
            if (!copia (strdup (line))) return 0;
        }
    }
    return 1;
}

/*Função chamada pela querieIdentifier para executar a query 6*/
int query6Exe(FILE *res, int modo, char **argumentos){
    int r = 1;
    double distancia = distancia_media(tempo_De_Vida(strdup(argumentos[2])),tempo_De_Vida(strdup(argumentos[3])), argumentos [1]);
    r = printQ6(res,modo,distancia);
    return r;
}