#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/interactive.h"

/* Função utilizada para percorrer um dos dois arrays criados no ficheiro rides.c (array_male, array_female), qual dos arrays é percorrido depende exclusi-
vamente do valor dado como argumento da query 8 (M ou F).
A função, tal como já foi referido anteriormente, vai percorrendo o array e, se a idade das contas do user e do driver forem superiores à idade dada como
argumento, (caso estejamos no modo batch) vai fazer print dos valores pretendidos no ficheiro associado ao resultado da query, caso contrário, ou seja, este-
jamos no modo interativo, vai fazer print no terminal (a forma do print desta query segue a seguinte forma: id_driver,nome_driver,username(do user),nome_user).
*/
int printArray_Q8(FILE *res, int modo,char gender_enunciado,int idade_conta_enunciado){
    char line[256] = {0};
    int pos = getPosQ8(gender_enunciado);
    for(int i = 0; i < pos && get_Idade_Conta_DriverQ8(i,gender_enunciado) >= idade_conta_enunciado;i++){
        if(get_Idade_Conta_UserQ8(i,gender_enunciado) >= idade_conta_enunciado){
            char *username = getUsernameQ8(i,gender_enunciado);
            char *id_driver = getIdDriverQ8(i,gender_enunciado);
            char *nome_driver = getNomeDriverQ8(i,gender_enunciado);
            char *nome_user = getNomeUserQ8(i,gender_enunciado);
            if (modo == 0)
                fprintf(res,"%s;%s;%s;%s\n",id_driver,nome_driver,username,nome_user);  /*Modo Batch.*/
            else{
                sprintf(line, "\t%s;%s;%s;%s",id_driver,nome_driver,username,nome_user);  /*Modo Interativo.*/
                if (!copia (strdup (line))) {
                    free(username);
                    free(id_driver);
                    free(nome_driver);
                    free(nome_user);
                    return 0;
                }
            }
            free(username);
            free(id_driver);
            free(nome_driver);
            free(nome_user);
        }
    }
    return 1;
}

/* Função responsável por chamar todas as funções que permitem a execução da query 8.Nesta query em específico só é necessário chamar a função print definida
em cima.
*/
int query8Exe(FILE *res, int modo, char **argv){
    int r = 1;
    if(argv[1][0] == 'M') printArray_Q8(res,modo,argv[1][0],atoi(argv[2])*10000);
    else if(argv[1][0] == 'F') printArray_Q8(res,modo,argv[1][0],atoi(argv[2])*10000);
    return r;
}