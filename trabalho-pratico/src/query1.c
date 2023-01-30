#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/users.h"
#include "../include/drivers.h"
#include "../include/queries.h"
#include "../include/query1.h"
#include "../include/interactive.h"

/* Função para fazer print dos valores do driver pedido na query 1 no ficheiro */
void printvaloresQ1 (DRIVERS *d, FILE *res, int modo, int *informacoespaginas, char *paginas[][linhas_por_pagina]) {  
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
            mvprintw (informacoespaginas[0], 0, "\t%s;%c;%d;%.3f;%d;%.3f",name, gender, calculaIdade(birth), avaliacao_media, count, total_auferido);
            sprintf(line, "\t%s;%c;%d;%.3f;%d;%.3f",name, gender, calculaIdade(birth), avaliacao_media, count, total_auferido);
            paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup(line);
            if (informacoespaginas[0] >= linhas_por_pagina) novapagina (informacoespaginas, paginas);
        }
        free (name);
        free (birth);
    }
    else if (modo == 1){
        mvprintw (informacoespaginas[0], 0, "\tO Driver está inativo");
        paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup("\tO Driver está inativo");
        if (informacoespaginas[0] >= linhas_por_pagina) novapagina (informacoespaginas, paginas);
    }
}

/* Função para fazer print dos valores do user pedido na query 1 no ficheiro */
void printvaloresQ1_2 (User *u, FILE *res, int modo, int *informacoespaginas, char *paginas[][linhas_por_pagina])  {
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
            mvprintw (informacoespaginas[0], 0, "\t%s;%c;%d;%.3f;%d;%.3f",name, gender, calculaIdade(data), avaliacao_media, n_viagens, total_gasto);
            sprintf(line, "\t%s;%c;%d;%.3f;%d;%.3f",name, gender, calculaIdade(data), avaliacao_media, n_viagens, total_gasto);
            paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup(line);
            if (informacoespaginas[0] >= linhas_por_pagina) novapagina (informacoespaginas, paginas);
        }
        free (name);
        free (data);
    }
    else if (modo == 1){
        mvprintw (informacoespaginas[0], 0, "\tO User está inativo");
        paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup("\tO User está inativo");
        if (informacoespaginas[0] >= linhas_por_pagina) novapagina (informacoespaginas, paginas);
    }
}

void query1Exe(FILE *res, int modo, char* argv, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    if(identifyArgument(argv)) {
            DRIVERS *d =GetcontentD (lookup_drivers (argv)); /*faz lookup na hash dos drivers do Driver pedido*/
            if (d) { 
                printvaloresQ1 (d, res, modo, informacoespaginas, paginas); /*Função que faz print aos valores pretendidos dos drivers*/
                free_driver (d);
            }
            else if (modo == 1){
                mvprintw (informacoespaginas[0], 0, "\tO driver inserido não existe.");
                paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup("\tO driver inserido não existe.");
                if (informacoespaginas[0] >= linhas_por_pagina) novapagina (informacoespaginas, paginas);
            }
        }
        else {
            User *u = GetcontentU( lookup_users (argv) ); /*faz lookup na hash dos users do User pedido*/
            if (u) { 
                printvaloresQ1_2 (u, res,modo, informacoespaginas, paginas); /*Função que faz print aos valores pretendidos dos users*/
                free_user (u);
            }
            else if (modo == 1){
                mvprintw (informacoespaginas[0], 0, "\tO user inserido não existe.");
                paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup("\tO user inserido não existe.");
                if (informacoespaginas[0] >= linhas_por_pagina) novapagina (informacoespaginas, paginas);
            }
        }
}