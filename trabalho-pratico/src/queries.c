#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/main.h"

int querie1(char *str){
    int id = 0;
    if(str[1] >= 48 && str[1] <= 57) id = 1;
    return id;
}

void querieIdentifier(char **argv, HASH *hash) {
    int q = atoi (argv[0]);
    switch (q)
    {
    case 1:
        if(querie1(argv[1])) procura(retornaHash(3, hash)); // mudar a procura
        else lookupUser(retornaHash(1, hash));
        break;
    
    default:
        break;
    }
    return;
}

int calculaIdade(char *str){
    int idade = 0;
    char *token = strsep(&str, "/");
    int dia = atoi(token);
    token = strsep(&str, "/");
    int mes = atoi(token);
    token = strsep(&str, "/");
    int ano = atoi(token);
    if(dia <= 9 && mes <= 10 && ano <= 2022) idade = 2022 - ano;
    else if(dia > 9 && mes >= 10) idade = (2022 - ano) - 1;
    return idade;
}