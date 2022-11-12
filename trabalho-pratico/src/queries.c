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
    FILE *res = fopen ("../Resultados/commandoutput1.txt","a");
    switch (q)
    {
    case 1:
        if(querie1(argv[1])) {
            char * carclass = procuraQ1(retornaHash(3, hash), argv[1], res);

            int identifier_car;
            if (!strcmp(carclass,"basic")) identifier_car = 0;
            else if (!strcmp(carclass,"green")) identifier_car = 1;
            else identifier_car = 2;

            double valores_medios [5] = {0};
            valores_medios [0] = strtod(argv[1], NULL);
            valores_medios [1] = identifier_car;

            g_hash_table_foreach (retornaHash(2, hash),(GHFunc)calcula_mediasQ1, valores_medios);
            
            double avaliacao_media = valores_medios [2] / valores_medios[3];
            printf ("%.3f;%d;%.3f\n", avaliacao_media,(int)valores_medios[3],valores_medios[4]);
        }
        else lookupUser(retornaHash(1, hash));
        break;
    
    default:
        break;
    }
    return;
}

int calculaIdade(char *str){
    int idade = 0;
    int dia = atoi(strsep(&str, "/"));
    int mes = atoi(strsep(&str, "/"));
    int ano = atoi(strsep(&str, "/"));
    if (mes < 10) idade = 2022 - ano;
    else if (mes == 10) {
        if (dia <= 9) idade = 2022 - ano;
        else idade = 2022 - ano - 1;
    }
    else idade = 2022 - ano -1;
    return idade;
}