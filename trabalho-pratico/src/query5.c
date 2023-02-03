#include <stdio.h>
#include <stdlib.h>
#include <glib.h>
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/interactive.h"
#include "../include/datas.h"

/* Recebe as datas dadas como argumento da query(após terem sido convertidas em dias devido ao uso da função 'tempo_De_Vida') e percorre o array, somando os
valores dos preços das viagens que se encontram dentro do intervalo formado entre as datas argumento(excluindo as tips).A função retorna a média do preço
das viagens dentro do intervalo.
*/
double preco_medio_Q5(int limite_inferior,int limite_superior){
    int i, max = getPosQ5Q6(), idade;
    double preco_total = 0,preco_medio = 0,numero_viagens = 0;
    if (getTempoDeVida (max-1) > limite_superior) {
        for (i = 0; i < max && getTempoDeVida(i) < limite_superior; i++);
        if (i < max) idade = getTempoDeVida(i);
        while(i < max && idade <= limite_inferior ){
            numero_viagens++;
            char car_class = getcarArrays(i);
            int distancia = getdistanceArrays(i);
            switch (identifie_car_class_char(car_class)) /*Custo por quilômetro depende da car_class do carro.*/
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
        if(numero_viagens) preco_medio = preco_total / numero_viagens;  /*Calcula a média dos preços das viagens.*/
    }
    return preco_medio;
}

/* Função responsável pelo print do valor dado como argumento(preco_medio) para o local pretendido, modo interativo->terminal || modo batch->ficheiro da pasta
Resultados.
*/
int printQ5 (FILE *res, int modo,double preco_medio) {
    char line[256] = {0};
    if(preco_medio){
        if (modo == 0)
            fprintf (res, "%.3f\n", preco_medio);  /*Modo Batch.*/
        else{
            sprintf(line, "\t%.3f", preco_medio);  /*Modo Interativo*/
            if (!copia (strdup (line))) return 0;
        }
    }
    return 1;
}

/* Responsável por chamar todas as funções que permitem a execução da query 5.Como a estrutura usada nesta query foi criada durante o parse só é necessário
chamar a função printQ5 para se obter o resultado esperado da query.
*/
int query5Exe(FILE *res, int modo, char **argv){
    int r = 1;
    double preco_medio = preco_medio_Q5(tempo_De_Vida(strdup(argv[1])),tempo_De_Vida(strdup(argv[2])));
    r = printQ5(res, modo,preco_medio);
    return r;
}