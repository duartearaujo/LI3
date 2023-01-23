#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/queries.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/dataverification.h"
#include "../include/cidades.h"


int iniciaI(){
    if (system("clear")) {
        perror("O sistema não conseguiu limpar o terminal.");
        return 0;
    };

    printf("PROJETO DE LI3\n");
    printf("by Filipe Rodrigues, João Coelho e Duarte Araújo\n\n");
    size_t len;
    ssize_t read;
    char *path = NULL;
    printf("Insira o path para os ficheiros: ");
    read = getline(&path, &len, stdin);
    path[read-1] = '\0';
    printf ("Carregando os ficheiros...\n");

    int u = iniciaHashUsers (path);
    int d = iniciaHashDrivers (path);
    createArrayQ9();
    iniciaHashCidades();
    int r = iniciaHashRides (path);
    if (!(u && d && r)) return 0;
    ordena_Q9();
    free (path);
    return 1;
}

int verifica_input (char **query) {
    int n_query = atoi (query[0]);
    if (n_query == 2 || n_query == 3)
        return verifica_inteiro (query [1]);
    if (n_query == 5 || n_query == 9) 
        return (verificadata (query[1]) && verificadata (query [2]));
    if (n_query == 4)
        return ( query [1][0] != '\0');
    if (n_query == 6)
        return ( query [1][0] != '\0' && verificadata (query[2]) && verificadata (query [3]));
    if (n_query == 7)
        return (query [2] && verifica_inteiro (query [1]) && query [2][0] != '\0');
    if (n_query == 8)
        return ((query[1][0] == 'M' || query[1][0] == 'F') && verifica_inteiro (query [2]));
    return -1;
}

void menudequeries () {
    printf ("\nMenu de Queries:\n");
    printf ("Query |                                               Descrição                                                         | Argumentos\n");
    printf ("  1   | Resumo de um perfil (User ou driver).                                                                           | Id/Username\n");
    printf ("  2   | Listar os N condutores com maior avaliação média.                                                               | N\n");
    printf ("  3   | Listar os N utilizadores com maior distância viajada.                                                           | N\n");
    printf ("  4   | Preço médio das viagens numa cidade.                                                                            | Cidade\n");
    printf ("  5   | Preço médio das viagens entre duas datas:                                                                       | Data1 Data2\n");
    printf ("  6   | Distância média percorrida, numa determinada cidade, num dado intervalo de tempo.                               | Cidade Data1 Data2\n");
    printf ("  7   | Listar os N condutores com maior avaliação média numa cidade.                                                   | N Cidade\n");
    printf ("  8   | Listar todas as viagens nas quais o utilizador e o condutor são do mesmo género e têm perfis com X ou mais anos.| M/F X\n");
    printf ("  9   | Listar as viagens nas quais o passageiro deu gorjeta num dado intervalo de tempo.                               | Data1 Data2\n\n");
}

void parsequeryI(){
    menudequeries ();
    int i = 1;
    int n_query = 1;
    char **query = NULL;
    char *q = NULL;
    char *args = NULL;
    size_t len;
    ssize_t read;

    printf("Especifique a query: ");
    read = getline(&q, &len, stdin);
    q[read-1] = '\0';
    
    int Nquery = atoi (q);
    if (Nquery < 1 || Nquery > 9){
        printf ("Número de query inválido.\n");
        return;
    }

    printf("Insira os argumentos separados por espaço: ");
    read = getline(&args, &len, stdin);
    args[read-1] = '\0';
    char *temp = args;
    char *token = strsep(&temp," ");

    if (Nquery == 6){
        query = malloc(4 * sizeof(char *)); 
        query[0] = strdup(q);
        query[1] = query[2] = query[3] = '\0';
    }
    else if (Nquery > 4){
        query = malloc(3 * sizeof(char *));
        query[0] = strdup(q);
        query[1] = query[2] = '\0';
    }
    else{
        query = malloc(2 * sizeof(char *));
        query[0] = strdup(q);
        query[1] = '\0';
    }
    while (token) {
        query[i] = strdup(token); 
        token = strsep(&temp," ");
        i++;
    }
    if (!verifica_input (query)) {
        printf ("Argumentos inválidos.\n");
        return;
    }
    querieIdentifier(query, n_query++, 1);

    for (--i; i>= 0; i--) free (query[i]);  /*free do array*/
    free (query);
    free (q);
    free (args);
    char *confirmacao = NULL;
    printf ("Pretende continuar?(y or n): ");
    read = getline (&confirmacao, &len, stdin);
    confirmacao[read -1] = '\0';
    if (confirmacao [0] != 'y' && confirmacao [0] != 'n') {
        printf ("Formato inválido de resposta. Terminando o programa...\n");
        return;
    }
    if (confirmacao[0] == 'y') parsequeryI();
    free (confirmacao);
}