#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/query1.h"
#include "../include/interactive.h"
#include "../include/datas.h"

/*Função para identificar se o input recebido da query 1 é um id(driver) ou um username (user)*/
int identifyArgument(char *str){  
    int id = 0;
    if(str[1] >= 48 && str[1] <= 57) id = 1;
    return id;
}

/* Função para fazer print dos valores do driver pedido na query 1 no ficheiro */
int printvaloresQ1 (DRIVERS *d, FILE *res, int modo) {  
    char account_st = getAccountStatusD (d);
    char line[256] = {0};
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
        else{
            sprintf(line, "\t%s;%c;%d;%.3f;%d;%.3f",name, gender, calculaIdade(birth), avaliacao_media, count, total_auferido);
            if (!copia (strdup (line))) {
                free (name);
                free (birth);
                return 0;
            }
        }
        free (name);
        free (birth);
    }
    else if (modo == 1){
        sprintf(line, "\tO Driver está inativo");
        if (!copia(strdup (line))) return 0;
    }
    return 1;
}

/* Função para fazer print dos valores do user pedido na query 1 no ficheiro */
int printvaloresQ1_2 (User *u, FILE *res, int modo)  {
    char account_st = getAccStatusU (u);
    char line[256] = {0};
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
        else{ 
            sprintf(line, "\t%s;%c;%d;%.3f;%d;%.3f",name, gender, calculaIdade(data), avaliacao_media, n_viagens, total_gasto);
            if (!copia (strdup (line))) {
                free (name);
                free (data);
                return 0;
            }
        }
        free (name);
        free (data);
    }
    else if (modo == 1){
        sprintf(line, "\tO User está inativo");
        if (!copia(strdup (line))) return 0;
    }
    return 1;
}

int query1Exe(FILE *res, int modo, char* argv){
    int r = 1;
    if(identifyArgument(argv)) {
        DRIVERS *d =GetcontentD (lookup_drivers (argv)); /*faz lookup na hash dos drivers do Driver pedido*/
        if (d) { 
            r = printvaloresQ1 (d, res, modo); /*Função que faz print aos valores pretendidos dos drivers*/
            free_driver (d);
        }
        else if (modo == 1){
                if (!copia(strdup ("\tO driver inserido não existe."))) return 0;
            }
    }
    else {
        User *u = GetcontentU( lookup_users (argv) ); /*faz lookup na hash dos users do User pedido*/
        if (u) { 
            r = printvaloresQ1_2 (u, res,modo); /*Função que faz print aos valores pretendidos dos users*/
            free_user (u);
        }
        else if (modo == 1){
            if (!copia(strdup ("\tO user inserido não existe."))) return 0;
        }
    }
    return r;
}