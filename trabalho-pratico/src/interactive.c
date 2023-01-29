#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "../include/interactive.h"
#include "../include/queries.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/drivers.h"
#include "../include/dataverification.h"
#include "../include/cidades.h"

int novapagina(int *informacoespaginas, char (*paginas)[][linhas_por_pagina]) {
    mvprintw (informacoespaginas[0]++,0,"\t\t---- FIM DA PAGINA ----");
    mvprintw (informacoespaginas[0]++,0,"n - proxima pagina       p - pagina anterior       e - exit");
    int ch = getch();
    if (ch == 'n') {
        informacoespaginas[1] ++;
        informacoespaginas[0] = 0;
        erase();
        return 1;
    }
    if (ch == 'p' && informacoespaginas [1] >= 0) {
        informacoespaginas[1]--;
        for (int i = 0; i < informacoespaginas[2]; i++) mvprintw (i,0,"%s", (*paginas) [informacoespaginas[1]]);
    }
    if (ch == 'e')
        return 0;
    return -1;
}

int iniciaI(int *informacoespaginas,  char (*paginas)[][linhas_por_pagina]){
    mvprintw (informacoespaginas[0]++,0,"PROJETO DE LI3");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);

    mvprintw (informacoespaginas[0]++,0,"by Filipe Rodrigues, João Coelho e Duarte Araújo");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);

    char *path = malloc (sizeof (char) * 256);
    mvprintw(informacoespaginas[0]++,0,"Insira o path para os ficheiros: ");
 
    getstr(path);
    refresh ();
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);

    mvprintw (informacoespaginas[0]++,0,"Carregando os ficheiros...");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    refresh ();

    int u = iniciaHashUsers (path);
    int d = iniciaHashDrivers (path);
    inicializaQ9();
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

void menudequeries (int *informacoespaginas, char (*paginas)[][linhas_por_pagina]) {
    informacoespaginas[0]++;
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"Menu de Queries:");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"Query |                                               Descrição                                                       | Argumentos");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  1   | Resumo de um perfil (User ou driver).                                                                           | Id/Username");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  2   | Listar os N condutores com maior avaliação média.                                                            | N");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  3   | Listar os N utilizadores com maior distância viajada.                                                          | N");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  4   | Preço médio das viagens numa cidade.                                                                          | Cidade");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  5   | Preço médio das viagens entre duas datas:                                                                     | Data1 Data2");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  6   | Distância média percorrida, numa determinada cidade, num dado intervalo de tempo.                             | Cidade Data1 Data2");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  7   | Listar os N condutores com maior avaliação média numa cidade.                                                | N Cidade");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  8   | Listar todas as viagens nas quais o utilizador e o condutor são do mesmo género e têm perfis com X ou mais anos.| M/F X");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw (informacoespaginas[0]++,0,"  9   | Listar as viagens nas quais o passageiro deu gorjeta num dado intervalo de tempo.                               | Data1 Data2");
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    informacoespaginas[0]++;
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
}

void continuacao (int *informacoespaginas, char (*paginas)[][linhas_por_pagina]) {
    int confirmacao;
    mvprintw (informacoespaginas[0]++,0, "Pretende continuar?(y or n): ");
    confirmacao = getch();
    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    if (confirmacao != 'y' && confirmacao != 'n') {
        mvprintw (informacoespaginas[0]++,0,"Formato inválido de resposta.");
        continuacao (informacoespaginas, paginas);
        if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
        return;
    }
    if (confirmacao == 'y') parsequeryI(informacoespaginas, paginas);
}

void parsequeryI(int *informacoespaginas, char (*paginas)[][linhas_por_pagina]){
    menudequeries (informacoespaginas,paginas);
    int i = 1;
    int n_query = 1;
    char **query = NULL;
    char *q = malloc (sizeof (char) *2);
    char *args = malloc (sizeof (char) * 256);

    if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
    mvprintw(informacoespaginas[0]++,0,"Especifique a query: ");
    getstr(q);
    
    int Nquery = atoi (q);
    if (Nquery < 1 || Nquery > 9){
        mvprintw (informacoespaginas[0]++,0,"Número de query inválido.");
        if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
        parsequeryI (informacoespaginas, paginas);
        return;
    }

    mvprintw(informacoespaginas[0]++,0,"Insira os argumentos separados por espaço: ");
    getstr (args);

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
        mvprintw (informacoespaginas[0]++,0,"Argumentos inválidos.\n");
        if (informacoespaginas[0] >= informacoespaginas [2]) novapagina (informacoespaginas, paginas);
        return;
    }
    querieIdentifier(query, n_query++, 1, informacoespaginas, paginas);

    for (--i; i>= 0; i--) free (query[i]);  /*free do array*/
    free (query);
    free (q);
    free (args);
    continuacao (informacoespaginas, paginas);
}

void main_I () {
    initscr();
    refresh();
    int informacoespaginas[3];
    informacoespaginas [0] = 0; //Linha atual
    informacoespaginas [1] = 0; //Pagina atual
    informacoespaginas [2] = linhas_por_pagina; //Linhas por pagina
    int total_paginas = 10000 / linhas_por_pagina;  // Total number of pages
    char (*paginas)[linhas_por_pagina][total_paginas] = {0};
    int i = iniciaI(informacoespaginas, paginas);
    if (i) parsequeryI(informacoespaginas, paginas);
    endwin();
}