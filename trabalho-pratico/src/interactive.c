#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ncurses.h>
#include "../include/interactive.h"
#include "../include/queries.h"
#include "../include/catalogos.h"
#include "../include/dataverification.h"

/* Defenição de linhas_por_pagina com o valor 30.*/
#define linhas_por_pagina 30

/* Defenição de total_paginas com o valor 335 (~10000(linhas) / linhas_por_pagina).*/
#define total_paginas 335

/* Struct para guardar informações sobre as páginas do modo interativo.*/
struct paginas_interativo {
    int informacoespaginas[3];
    char *pages[total_paginas][linhas_por_pagina];
};

static paginas_interativo *paginas = NULL; /* Static para declarar a estrutura globalmente apenas no ficheiro interactive.c*/

/* Função que faz print da linha que vem de outros ficheiros no terminal e guarda a linha na página.*/
int copia (char *line) {
    mvprintw (paginas->informacoespaginas[0], 0, "%s",line);
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = line;
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina ()) return 0;
    return 1;
}

/* Função que trata da funcionaliade de saltar para uma página à escolha do utilizador. Se o número inserido for:
    inválido: a função é chamda recursivamente
    maior que o número de páginas existente: é criado uma nova página
*/
int saltar_pagina (int linha, int paginas) {
    mvprintw (linha,90,"Insira o número da página q deseja ir (1 a %d): ",paginas + 1);
    char pagina [6];
    int n_pagina;
    getstr (pagina);
    int verificacao = 1; 
    for (int i = 0; pagina[i] && verificacao; i++) if (pagina[i] > '9' || pagina [i] < '0') verificacao = 0;
    if (!verificacao || pagina [0] == '0')
        n_pagina = saltar_pagina (linha, paginas);
    else n_pagina = atoi (pagina) - 1;
    if (n_pagina < 0) n_pagina = saltar_pagina (linha, paginas);
    return n_pagina;
}

/* Função para funcionalidades de final de página. É pedido para inserir uma letra q corresponde a um comando:
p - Move para a página anterior.
n - Move para a página seguinte. Se não houver cria uma nova.
e - Fecha o programa.
s - Salta para uma página à escolha do utilizador.
*/
int novapagina() {
    mvprintw (paginas->informacoespaginas[0],0,"\t\t---- FIM DA PAGINA ----");
    mvprintw (paginas->informacoespaginas[0]+1,0,"p - Pagina anterior       n - Proxima pagina       e - Sair       s - Saltar p/página");
    int ch = getch();
    if (ch == 'n') {
        erase();
        paginas->informacoespaginas[1] ++;
        if (paginas->informacoespaginas[1] <= paginas->informacoespaginas[2]){
            for (int i = 0; i < linhas_por_pagina; i++) if (paginas->pages[paginas->informacoespaginas[1]] [i]) mvprintw (i,0,"%s", paginas->pages[paginas->informacoespaginas[1]] [i]);
            if (novapagina(paginas->informacoespaginas, paginas) == 0) return 0;
        }
        else {
            paginas->informacoespaginas[0] = 0;
            paginas->informacoespaginas[2]++;
        }
        return 1;
    }
    else if (ch == 'p') {
        erase();
        if (paginas->informacoespaginas [1])
            paginas->informacoespaginas[1]--;
        for (int i = 0; i < linhas_por_pagina; i++) if (paginas->pages[paginas->informacoespaginas[1]] [i]) mvprintw (i,0,"%s", paginas->pages[paginas->informacoespaginas[1]] [i]);
        if (novapagina(paginas->informacoespaginas, paginas) == 0) return 0;
    }
    else if (ch == 's'){
        int pagina = saltar_pagina (paginas->informacoespaginas[0]+1,paginas->informacoespaginas[2]);
        erase();
        if (pagina > paginas->informacoespaginas[2]) {
            paginas->informacoespaginas[0] = 0;
            paginas->informacoespaginas[2]++;
            paginas->informacoespaginas[1] = paginas->informacoespaginas[2];
            return 1;
        }
        else {
            paginas->informacoespaginas[1] = pagina;
            for (int i = 0; i < linhas_por_pagina; i++) if (paginas->pages[paginas->informacoespaginas[1]] [i]) mvprintw (i,0,"%s", paginas->pages[paginas->informacoespaginas[1]] [i]);
            if (novapagina(paginas->informacoespaginas, paginas) == 0) return 0;
        }
    }
    else if (ch == 'e')
        return 0;
    else novapagina(paginas->informacoespaginas, paginas);
    return -1;
}

/* Inicia o modo interativo. Primeiro pede o path dos ficheiros, se for inválido o programa acaba.*/
int iniciaI(){

    mvprintw (paginas->informacoespaginas[0],0,"PROJETO DE LI3");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("PROJETO DE LI3");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;

    mvprintw (paginas->informacoespaginas[0],0,"by Filipe Rodrigues, João Coelho e Duarte Araújo");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("by Filipe Rodrigues, João Coelho e Duarte Araújo");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;

    char *path = malloc (sizeof (char) * 256);
    mvprintw(paginas->informacoespaginas[0],0,"Insira o path para os ficheiros: ");
    getstr(path);

    char line[256];
    sprintf (line, "Insira o path para os ficheiros: %s", path);
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup (line);
    
    refresh ();
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) {free (path);return 0;}

    mvprintw (paginas->informacoespaginas[0],0,"Carregando os ficheiros...");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("Carregando os ficheiros...");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) {free (path);return 0;}
    refresh ();

    if (!iniciaHashTables (path)) {free (path);return 0;}
    free (path);
    return 1;
}

/* Função que verifica se o input de argumentos dado pelo utilizador é válido para a query pedida. A verificação utiliza funções do módulo dataverication.h*/
int verifica_input (char **query) {
    int n_query = atoi (query[0]);
    if (n_query == 1)
        return (query[1][0] != '\0');
    if (n_query == 2 || n_query == 3)
        return verifica_inteiro (query [1]);
    if (n_query == 5 || n_query == 9) 
        return (query[1] != NULL && query[2] != NULL && verificadata (query[1]) && verificadata (query [2]));
    if (n_query == 4)
        return ( query [1][0] != '\0');
    if (n_query == 6)
        return ( query [1][0] != '\0' && query[2] != NULL && query[3] != NULL && verificadata (query[2]) && verificadata (query [3]));
    if (n_query == 7)
        return (query [2] && verifica_inteiro (query [1]) && query [2][0] != '\0');
    if (n_query == 8)
        return ((query[1][0] == 'M' || query[1][0] == 'F') && query[2] != NULL && verifica_inteiro (query [2]));
    return -1;
}

/* Função para dar print ao resumo de cada querie.*/
int menudequeries () {
    paginas->informacoespaginas[0]++;
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    mvprintw (paginas->informacoespaginas[0],0,"Menu de Queries:");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("Menu de Queries:");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"Query |                                               Descrição                                                       | Argumentos");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("Query |                                               Descrição                                                       | Argumentos");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  1   | Resumo de um perfil (User ou driver).                                                                           | Id/Username");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  1   | Resumo de um perfil (User ou driver).                                                                           | Id/Username");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  2   | Listar os N condutores com maior avaliação média.                                                            | N");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  2   | Listar os N condutores com maior avaliação média.                                                            | N");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  3   | Listar os N utilizadores com maior distância viajada.                                                          | N");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  3   | Listar os N utilizadores com maior distância viajada.                                                          | N");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  4   | Preço médio das viagens numa cidade.                                                                          | Cidade");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  4   | Preço médio das viagens numa cidade.                                                                          | Cidade");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  5   | Preço médio das viagens entre duas datas:                                                                     | Data1 Data2");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  5   | Preço médio das viagens entre duas datas:                                                                     | Data1 Data2");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  6   | Distância média percorrida, numa determinada cidade, num dado intervalo de tempo.                             | Cidade Data1 Data2");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  6   | Distância média percorrida, numa determinada cidade, num dado intervalo de tempo.                             | Cidade Data1 Data2");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  7   | Listar os N condutores com maior avaliação média numa cidade.                                                | N Cidade");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  7   | Listar os N condutores com maior avaliação média numa cidade.                                                | N Cidade");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  8   | Listar todas as viagens nas quais o utilizador e o condutor são do mesmo género e têm perfis com X ou mais anos.| M/F X");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  8   | Listar todas as viagens nas quais o utilizador e o condutor são do mesmo género e têm perfis com X ou mais anos.| M/F X");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    mvprintw (paginas->informacoespaginas[0],0,"  9   | Listar as viagens nas quais o passageiro deu gorjeta num dado intervalo de tempo.                               | Data1 Data2");
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("  9   | Listar as viagens nas quais o passageiro deu gorjeta num dado intervalo de tempo.                               | Data1 Data2");
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    
    paginas->informacoespaginas[0]++;
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    return 1;
}

/* Função para a funcionalidade de continuação do programa. Realiza um pedido de um char y ou n. Se o char não corresponder a nenhum dos dois a função é chamada recursivamente. Se for 'y'
o é chamada a função parsequeryI para a continuação do programa, se for 'n' p programa acaba.*/
int continuacao () {
    int confirmacao;
    char line[31];
    mvprintw (paginas->informacoespaginas[0],0, "Pretende continuar?(y or n): ");
    confirmacao = getch();
    sprintf (line, "Pretende continuar?(y or n): %c", confirmacao);
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup (line); 
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
    if (confirmacao != 'y' && confirmacao != 'n') {
        mvprintw (paginas->informacoespaginas[0],0,"Formato inválido de resposta.");
        paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("Formato inválido de resposta.");     
        if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
        continuacao (paginas->informacoespaginas, paginas);
        return 1;
    }
    if (confirmacao == 'y') parsequeryI(paginas->informacoespaginas, paginas);
    return 1;
}

/* Função para realizar os pedidos de queries do utilizador. Primeiro pede para o utilizador especificar a query que deseja executar, sendo feito uma verificação se o número é válido.
De seguida é pedido os argumentos que passam por uma verificação com auxílio da função verifica_input. É chamada a função querieidentifier para a execução da query e por fim é feita confimação se o utilizidador que continuar a executar o programa.*/
int parsequeryI(){
    if (!menudequeries ()) return 0;
    int i = 1;
    int n_query = 1;
    char **query = NULL;
    char *q = malloc (sizeof (char) *2);
    int Nquery_input;
    char *args = malloc (sizeof (char) * 256);
    char line[256] = {0};

    mvprintw(paginas->informacoespaginas[0],0,"Especifique a query: ");
    Nquery_input = getch();

    sprintf (line, "Especifique a query: %c", Nquery_input);
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup (line);    
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) {
        free (query);
        free (q);
        free (args);
        return 0;
    }
    if (Nquery_input < '1' || Nquery_input > '9'){
        mvprintw (paginas->informacoespaginas[0],0,"Número de query inválido.");
        paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("Número de query inválido.");
        if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) return 0;
        parsequeryI (paginas->informacoespaginas, paginas);
        free (query);
        free (q);
        free (args);
        return 1;
    }
    sprintf (q, "%c", Nquery_input);
    int Nquery = atoi (q);
    mvprintw(paginas->informacoespaginas[0],0,"Insira os argumentos separados por espaço: ");
    getstr (args);
    sprintf (line, "Insira os argumentos separados por espaço: %s", args);
    paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup (line);
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) {
        free (query);
        free (q);
        free (args);
        return 0;
    }
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
        mvprintw (paginas->informacoespaginas[0],0,"Argumentos inválidos.");
        paginas->pages[paginas->informacoespaginas[1]] [paginas->informacoespaginas[0]++] = strdup ("Argumentos inválidos.");
        if (paginas->informacoespaginas[0] >= linhas_por_pagina) if (!novapagina (paginas->informacoespaginas, paginas)) {
            free (query);
            free (q);
            free (args);
            return 0;
        }
        parsequeryI (paginas->informacoespaginas, paginas);      
        free (query);
        free (q);
        free (args);  
        return 1;
    }
    if (!queryHandler(query, n_query++, 1)) {
        free (query);
        free (q);
        free (args);
        return 0;
    }
    for (--i; i>= 0; i--) free (query[i]);  /*free do array*/
    free (query);
    free (q);
    free (args);
    if (!continuacao (paginas->informacoespaginas, paginas)) return 0;
    return 1;
}

/* Main do modo interativo. Inicia a struct do modo, prenche o array de ints sobre as informações de cada página. Chama a função iniciaI para iniciar o programa. De seguida chama a função parsequeryI para resolver as queries.
Por fim, para encerrar o programa, é feito os free's necessários.*/
void main_I () {
    initscr();
    refresh();
    paginas = malloc (sizeof (paginas_interativo));
    paginas->informacoespaginas [0] = 0; //Linha atual
    paginas->informacoespaginas [1] = 0; //Pagina atual
    paginas->informacoespaginas [2] = 0; //Maior página
    int i = iniciaI();
    if (i) parsequeryI();
    if (paginas->informacoespaginas[0] >= linhas_por_pagina) {
        erase();
        mvprintw (0,0, "Libertando Memória...");
    }
    else
        mvprintw (paginas->informacoespaginas[0],0, "Libertando Memória...");
    refresh();
    for (int i = 0; i <= paginas->informacoespaginas[2]; i++)
        for (int j = 0; j < linhas_por_pagina; j++) 
            if (paginas->pages[i][j]) free (paginas->pages[i][j]);
    freeEstruturas ();

    endwin();
}