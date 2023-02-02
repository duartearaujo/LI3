#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/interactive.h"
#include "../include/datas.h"

double preco_medio_Q5(int limite_inferior,int limite_superior){
    int i, max = getPosQ5Q6(), idade;
    double preco_total = 0,preco_medio = 0,numero_viagens = 0;
    for (i = 0; i < max && getTempoDeVida(i) < limite_superior; i++);
    if (i < max) idade = getTempoDeVida(i);
    while(i < max && idade <= limite_inferior ){
        numero_viagens++;
        char car_class = getcarArrays(i);
        int distancia = getdistanceArrays(i);
        switch (identifie_car_class_char(car_class))
        {
        case 0:
            preco_total += distancia * 0.62 + 3.25;
            break;
        case 1:
            preco_total += distancia * 0.79 + 4;
            break;
        case 2:
            preco_total  += distancia * 0.94 + 5.20;
            break;
        default:
            break;
        }
        idade = getTempoDeVida(++i);
    }
    if(numero_viagens) preco_medio = preco_total / numero_viagens;
    return preco_medio;
}

int printQ5 (FILE *res, int modo,double preco_medio, int *informacoespaginas, char *paginas[][linhas_por_pagina]) {
    char line[256] = {0};
    if(preco_medio){
        if (modo == 0)
            fprintf (res, "%.3f\n", preco_medio);
        else{
            mvprintw (informacoespaginas[0], 0, "\t%.3f", preco_medio);
            sprintf(line, "\t%.3f", preco_medio);
            paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup(line);
            if (informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (informacoespaginas, paginas)) return 0;
        }
    }
    return 1;
}

int query5Exe(FILE *res, int modo, char **argv, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    int r = 1;
    double preco_medio = preco_medio_Q5(tempo_De_Vida(strdup(argv[1])),tempo_De_Vida(strdup(argv[2])));
    r = printQ5(res, modo,preco_medio,informacoespaginas, paginas);
    return r;
}