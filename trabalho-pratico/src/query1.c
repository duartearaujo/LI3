#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/queries.h"

/* Função para fazer print dos valores do driver pedido na query 1 no ficheiro */
void printvaloresQ1 (DRIVERS *d, FILE *res, int modo) {  
    char account_st = getAccountStatusD (d);
    if (account_st == 'a') {
        double valor_atual = getValorAtualD (d);
        int count = getCountD (d);
        double avaliacao_media = valor_atual / count;   /*é calculada a avaliação média de cada driver*/
        double total_auferido = getTotalAuferido (d);

        char * name = getNameD (d);
        char gender = getGenderD (d);
        char * birth = getBirthD (d);
        if (modo == 0)
            fprintf (res,"%s;%c;%d;%.3f;%d;%.3f\n",name, gender, calculaIdade(birth), avaliacao_media, count, total_auferido);
        else 
            printf ("\t%s;%c;%d;%.3f;%d;%.3f\n",name, gender, calculaIdade(birth), avaliacao_media, count, total_auferido);
        free (name);
        free (birth);
    }
    else if (modo == 1)
        printf ("\tO Driver está inativo\n");
}

/* Função para fazer print dos valores do user pedido na query 1 no ficheiro */
void printvaloresQ1_2 (User *u, FILE *res, int modo)  {
    char account_st = getAccStatusU (u);
    if (account_st == 'a') {
        double acc_avaliation = getAccAvaliationU (u);
        int n_viagens = getNViagensU (u);
        double avaliacao_media = acc_avaliation / n_viagens;
        double total_gasto = getTotalGastoU(u);

        char *name = getNameU (u);
        char gender= getGenderU (u);
        char *data = getDataU (u);
        if (modo == 0)  
            fprintf (res,"%s;%c;%d;%.3f;%d;%.3f\n",name, gender, calculaIdade(data), avaliacao_media, n_viagens, total_gasto);
        else
            printf ("\t%s;%c;%d;%.3f;%d;%.3f\n",name, gender, calculaIdade(data), avaliacao_media, n_viagens, total_gasto);
        free (name);
        free (data);
    }
    else if (modo == 1)
        printf ("\tO User está inativo\n");
}