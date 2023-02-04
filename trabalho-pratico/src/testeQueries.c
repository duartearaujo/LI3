#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/parse.h"
#include "../include/users.h"
#include "../include/rides.h"
#include "../include/queries.h"
#include "../include/drivers.h"
#include "../include/cidades.h"
#include "../include/query1.h"
#include "../include/query2.h"
#include "../include/query3.h"
#include "../include/query4.h"
#include "../include/query5.h"
#include "../include/query6.h"
#include "../include/query7.h"
#include "../include/query8.h"
#include "../include/query9.h"
#include "../include/catalogos.h"

/* Verifica se dois ficheiros dados como argumento são iguais ou não.Esta funcção é utilizada para verificar se o resultado do teste é igual à solução ou não.*/
int compareFiles(FILE *fp1, FILE *fp2){
    int ch1 = getc(fp1);
    int ch2 = getc(fp2);
    while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
        ch1 = getc(fp1);
        ch2 = getc(fp2);
    }
    if(ch1 == ch2) return 1;
    return 0;
}

/* Cria o ficheiro onde o resultado do teste vai ser escrito e chama as funções que executam as queries para escrever o resultado nesse mesmo ficheiro.
Depois abre o file onde a solução do respetivo teste se encontra e chama a função que compara dois ficheiros para verificar se o resultado obtido está
certo ou não. Esta função é utilizada para fazer os testes das queries que recebem um único argumento.*/
int testaQueries1Argumento(int modo,int n_teste,int query){
    printf("A iniciar os testes da Query %d:\n",query);
    int i = 0,N = 0,inicio = 0,erros = 0,corretos = 0;
    float time_used = 0;
    char *argumentos[12] = {"ClarPacheco48","000000004780","000000003123","2126","994","0","5216","4090","0","Braga","Coimbra","Roma"};
    if(query == 1){
        inicio = 0;
        N = 3;
    }
    else if(query == 2){
        inicio = 3;
        N = 6;
    }
    else if(query == 3){
        inicio = 6;
        N = 9;
    }
    else if(query == 4){
        inicio = 9;
        N = 12;
    }
    for(i = inicio; i < N;i++){
        FILE *res = NULL,*solucao = NULL;
        char filename [37 + n_teste];
        sprintf(filename, "Resultados_testes/command%d_output.txt", n_teste);
        res = fopen(filename, "a"); /**< Cria o ficheiro onde o resultado do teste vai ser escrito.*/
        clock_t t = clock();
        if(query == 1) query1Exe(res,modo,argumentos[i]); /**< Executa a query 1 caso o argumento dado seja 1.*/
        else if(query == 2) query2Exe(res,modo,argumentos[i]); /**< Executa a query 2 caso o argumento dado seja 2.*/
        else if(query == 3) query3Exe(res,modo,argumentos[i]); /**< Executa a query 3 caso o argumento dado seja 3.*/
        else if(query == 4) exec_Q4(argumentos[i],res,modo); /**< Executa a query 4 caso o argumento dado seja 4.*/
        if (res) fclose (res);
        res = fopen(filename, "r");
        t = clock() - t;
        time_used = ((float)t)/CLOCKS_PER_SEC;
        printf ("\tQuery%d: %f\n",query,time_used);
        if(time_used >= 10) erros = 2;
        char solucao_teste[33 + n_teste];
        sprintf(solucao_teste, "SolucoesTestes/solucao_teste%d.txt", n_teste);
        solucao = fopen(solucao_teste, "r");
        if(compareFiles(res,solucao)) corretos++; /**< Verifica se o resultado do teste está certo.*/
        if (res) fclose (res);
        if (solucao) fclose (solucao);
        n_teste++;
    }
    printf("Query %d : Passou a %d/3 Testes\n\n",query,corretos);
    if(erros == 2) printf("Query %d ultrapassou o tempo útil!\n\n",query);
    return n_teste;
}

/* Cria o ficheiro onde o resultado do teste vai ser escrito e chama as funções que executam as queries para escrever o resultado nesse mesmo ficheiro.
Depois abre o file onde a solução do respetivo teste se encontra e chama a função que compara dois ficheiros para verificar se o resultado obtido está
certo ou não. Esta função é utilizada para fazer os testes das queries que recebem dois argumentos.*/
int testaQueries2Argumentos(int modo,int n_teste,int query){
    printf("A iniciar os testes da Query %d:\n",query);
    int N = 0,erros = 0,linha = 0,inicio = 0,corretos = 0;
    float time_used = 0;
    char *argumentos[12][3] = {{NULL,"24/06/2010","26/02/2012"},
                              {NULL,"10/07/2014","20/07/2014"},
                              {NULL,"03/06/2018","31/10/2019"},
                              {NULL,"0","Porto"},
                              {NULL,"97","Faro"},
                              {NULL,"1702","Rome"},
                              {NULL,"M","12"},
                              {NULL,"F","15"},
                              {NULL,"F","12"},
                              {NULL,"13/11/2012","13/11/2012"},
                              {NULL,"08/03/2042","08/03/2042"},
                              {NULL,"27/10/2018","27/10/2018"},};
    if(query == 5){
        inicio = 0;
        N = 3;
    }
    if(query == 7){
        inicio = 3;
        N = 6;
    }
    if(query == 8){
        inicio = 6;
        N = 9;
    }
    if(query == 9){
        inicio = 9;
        N = 12;
    }
    for(linha = inicio; linha < N;linha++){
        FILE *res = NULL,*solucao = NULL;
        char filename [37 + n_teste];
        sprintf(filename, "Resultados_testes/command%d_output.txt", n_teste);
        res = fopen(filename, "a"); /**< Cria o ficheiro onde o resultado do teste vai ser escrito.*/
        clock_t t = clock();
        if(query == 5) query5Exe(res,modo,argumentos[linha]); /**< Executa a query 5 caso o argumento dado seja 5.*/
        if(query == 7) exec_Q7(argumentos[linha][2],atoi(argumentos[linha][1]),res,modo); /**< Executa a query 7 caso o argumento dado seja 7.*/
        if(query == 8) query8Exe(res,modo,argumentos[linha]); /**< Executa a query 8 caso o argumento dado seja 8.*/
        if(query == 9) query9Exe(res,modo,argumentos[linha]); /**< Executa a query 9 caso o argumento dado seja 9.*/
        if (res) fclose (res);
        res = fopen(filename, "r");
        t = clock() - t;
        time_used = ((float)t)/CLOCKS_PER_SEC;
        printf ("\tQuery%d: %f\n",query,time_used);
        if(time_used >= 10) erros = 2;
        char solucao_teste[33 + n_teste];
        sprintf(solucao_teste, "SolucoesTestes/solucao_teste%d.txt", n_teste);
        solucao = fopen(solucao_teste, "r");
        if(compareFiles(res,solucao)) corretos++; /**< Verifica se o resultado do teste está certo.*/
        if (res) fclose (res);
        if (solucao) fclose (solucao);
        n_teste++;
    }
    printf("Query %d : Passou a %d/3 Testes\n\n",query,corretos);
    if(erros == 2) printf("Query %d ultrapassou o tempo útil!\n\n",query);
    return n_teste;
}

/* Cria o ficheiro onde o resultado do teste vai ser escrito e chama as funções que executam as queries para escrever o resultado nesse mesmo ficheiro.
Depois abre o file onde a solução do respetivo teste se encontra e chama a função que compara dois ficheiros para verificar se o resultado obtido está
certo ou não. Esta função é utilizada para fazer os testes da query 6 já que é a única que recebe três argumentos.*/
void testaQueries3Argumentos(int modo,int n_teste){
    printf("A iniciar os testes da Query 6:\n");
    int linha = 0,erros = 0,corretos = 0;
    float time_used = 0;
    char *argumentos[3][4] = {{NULL,"London","13/08/2019","31/01/2020"},
                              {NULL,"Lisboa","05/05/2018","27/01/2020"},
                              {NULL,"Porto","19/07/2012","29/10/2013"}};
    while(linha < 3){
        FILE *res = NULL,*solucao = NULL;
        char filename [37 + n_teste];
        sprintf(filename, "Resultados_testes/command%d_output.txt", n_teste);
        res = fopen(filename, "a"); /**< Cria o ficheiro onde o resultado do teste vai ser escrito.*/
        clock_t t = clock();
        query6Exe(res,modo,argumentos[linha]); /**< Executa a query 6.*/
        if (res) fclose (res);
        res = fopen(filename, "r");
        t = clock() - t;
        time_used = ((float)t)/CLOCKS_PER_SEC;
        printf ("\tQuery6: %f\n",time_used);
        if(time_used >= 10) erros = 2;
        char solucao_teste[33 + n_teste];
        sprintf(solucao_teste, "SolucoesTestes/solucao_teste%d.txt", n_teste);
        solucao = fopen(solucao_teste, "r");
        if(compareFiles(res,solucao)) corretos++; /**< Verifica se o resultado do teste está certo.*/
        if (res) fclose (res);
        if (solucao) fclose (solucao);
        n_teste++;
        linha++;
    }
    printf("Query 6 : Passou a %d/3 Testes\n\n",corretos);
    if(erros == 2) printf("Query 6 ultrapassou o tempo útil!\n\n");
}

/* Função main dos testes automáticos. São chamadas as funções que fazem os testes para cada query.*/
int main(int argc,char **argv){
    int r = iniciaHashTables(argv[1]);
    int n_teste = 1;
    if(!r) return 1;
    n_teste = testaQueries1Argumento(0,n_teste,1);
    n_teste = testaQueries1Argumento(0,n_teste,2);
    n_teste = testaQueries1Argumento(0,n_teste,3);
    n_teste = testaQueries1Argumento(0,n_teste,4);
    n_teste = testaQueries2Argumentos(0,n_teste,5);
    testaQueries3Argumentos(0,25);
    n_teste = testaQueries2Argumentos(0,n_teste,7);
    n_teste = testaQueries2Argumentos(0,n_teste,8);
    n_teste = testaQueries2Argumentos(0,n_teste,9);
    freeEstruturas();
    return 0;
}