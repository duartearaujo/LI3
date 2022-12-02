#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/queries.h"

/* Função para fazer print dos valores do driver pedido na query 1 no ficheiro */
void printvaloresQ1 (DRIVERS *d, FILE *res) {  
    char *account_st = getAccountStatusD (d);
    if (!strcmp (account_st, "active")) {
        double valor_atual = getValorAtualD (d);
        int count = getCountD (d);
        double avaliacao_media = valor_atual / count;   /*é calculada a avaliação média de cada driver*/
        double total_auferido = getTotalAuferido (d);

        char * name = getNameD (d);
        char * gender = getGenderD (d);
        char * birth = getBirthD (d);

        fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",name, gender, calculaIdade(birth), avaliacao_media, count, total_auferido);

        free (name);
        free (gender);
        free (birth);
    }
    free (account_st);
}

/* Função para fazer print dos valores do user pedido na query 1 no ficheiro */
void printvaloresQ1_2 (User *u, FILE *res)  {
    char *account_st = getAccStatusU (u);
    if (!strcmp(account_st,"active")) {
        double acc_avaliation = getAccAvaliationU (u);
        int n_viagens = getNViagensU (u);
        double avaliacao_media = acc_avaliation / n_viagens;
        double total_gasto = getTotalGastoU(u);

        char *name = getNameU (u);
        char *gender= getGenderU (u);
        char *data = getDataU (u);
        fprintf (res,"%s;%s;%d;%.3f;%d;%.3f\n",name, gender, calculaIdade(data), avaliacao_media, n_viagens, total_gasto);

        free (name);
        free (gender);
        free (data);
    }
    free (account_st);
}