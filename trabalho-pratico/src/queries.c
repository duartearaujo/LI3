#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
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
            if (!carclass) break; // se estiver inativo dá break e dá origem a um ficheiro vazio;

            int identifier_car; 
            if (!strcmp(carclass,"basic")) identifier_car = 0;     // atribiu um int consoante o tipo de carro do driver
            else if (!strcmp(carclass,"green")) identifier_car = 1;
            else identifier_car = 2;

            double valores_medios [5] = {0};
            valores_medios [0] = strtod(argv[1], NULL); // Posicao 0 do array corresponde ao id a procurar
            valores_medios [1] = identifier_car; // Posicao 1 do array corresponde ao int identificador do tipo de carro

            g_hash_table_foreach (retornaHash(2, hash),(GHFunc)calcula_mediasQ1, valores_medios);
            
            double avaliacao_media = valores_medios [2] / valores_medios[3];  // Posicao 2 = acumulador de score_driver; Posicao 3 = nº de viagens; Posicao 4 = total_auferido.
            fprintf (res,"%.3f;%d;%.3f\n", avaliacao_media,(int)valores_medios[3],valores_medios[4]);
        }
        else {
            if (lookupUser(retornaHash(1, hash), res,argv[1])) break;

            Q1USER *valores = inicializaQ1(hash,argv[1]);
            g_hash_table_foreach (retornaHash(2, hash),(GHFunc)calcula_mediasQ1_2, valores);

            printQ1(valores, res);
            free_struct_Q1 (valores);
            free (valores);
        }
        break;
    
    default:
        break;
    }
    fclose (res);
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