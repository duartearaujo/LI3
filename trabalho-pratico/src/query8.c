#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/query8.h"
#include "../include/interactive.h"

int printArray_Q8(FILE *res, int modo,char gender_enunciado,int idade_conta_enunciado, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    char line[256] = {0};
    int pos = getPosQ8(gender_enunciado);
    for(int i = 0; i < pos && get_Idade_Conta_DriverQ8(i,gender_enunciado) >= idade_conta_enunciado;i++){
        if(get_Idade_Conta_UserQ8(i,gender_enunciado) >= idade_conta_enunciado){
            char *username = getUsernameQ8(i,gender_enunciado);
            char *id_driver = getIdDriverQ8(i,gender_enunciado);
            char *nome_driver = getNomeDriverQ8(i,gender_enunciado);
            char *nome_user = getNomeUserQ8(i,gender_enunciado);
            if (modo == 0)
                fprintf(res,"%s;%s;%s;%s\n",id_driver,nome_driver,username,nome_user);
            else{
                mvprintw(informacoespaginas[0], 0, "\t%s;%s;%s;%s",id_driver,nome_driver,username,nome_user);
                sprintf(line, "\t%s;%s;%s;%s",id_driver,nome_driver,username,nome_user);
                paginas[informacoespaginas[1]] [informacoespaginas[0]++] = strdup(line);
                if (informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (informacoespaginas, paginas)) return 0;
            }
            free(username);
            free(id_driver);
            free(nome_driver);
            free(nome_user);
        }
    }
    return 1;
}

int query8Exe(FILE *res, int modo, char **argv, int *informacoespaginas, char *paginas[][linhas_por_pagina]){
    int r = 1;
    if(argv[1][0] == 'M') printArray_Q8(res,modo,argv[1][0],atoi(argv[2])*10000,informacoespaginas,paginas);
    else if(argv[1][0] == 'F') printArray_Q8(res,modo,argv[1][0],atoi(argv[2])*10000,informacoespaginas,paginas);
    return r;
}