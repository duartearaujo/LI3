#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "../include/query7.h"
#include "../include/cidades.h"
#include "../include/drivers.h"
#include "../include/interactive.h"

/* Struct auxiliar para dar print do resultado da query 7. Possui o ficheiro no caso do modo bath, número de prints e modo de print*/
struct PrintQ7 {
    FILE *res; /**< Ficheiro para guardar o output. Pode ser NULL no caso de estar no modo interativo*/
    int N; /**< Número de elementos para retornar*/
    int modo; /**< Modo que o programa se encontra*/
};

/* Função que se encarrega dos prints da query 7. A cada elemento da travessia inorder da árvore pretendida é feito getters, print do resultado e free das variáveis necessárias.
Quando faz N prints é retornado TRUE para acabar a travessia.*/
gboolean printQ7_aux (gpointer key, gpointer value, gpointer user_data) {
    PrintQ7 *ficheiro = user_data;
    AvC* driver = value;
    char *id = getIdAvC (driver);
    char line[256] = {0};
    if (verifica_ativo(id)) {
        char *name = getNameAvC(driver);
        double avaliacao_media = getAvaliacaoMediaAvC (driver);
        if (ficheiro->modo == 0) /* Modo Batch*/
            fprintf (ficheiro->res,"%s;%s;%.3f\n",id,name,avaliacao_media);
        else{ /* Modo Interativo*/
            sprintf(line, "\t%s;%s;%.3f",id,name,avaliacao_media);
                if (!copia (strdup (line))) {
                    free (name);
                    free (id);
                    return FALSE;
                }
            }
        free (name);
        ficheiro->N--;
    }
    free (id);
    if (ficheiro->N)
        return FALSE;
    return TRUE;
}

/* Cria a estrutura PrintQ7 e atribui os valores necessários. Chama a tree_foreach_city para começar a travessia e assim dar print ao resultado.*/
int printQ7 (char *city,int N, FILE *res, int modo) {
    int r = 1;
    PrintQ7 *p = malloc(sizeof (PrintQ7));
    p->N = N;
    p->res = res;
    p->modo = modo;
    tree_foreach_city (city,p);
    if (p->N) r = 0; 
    free (p);
    return r;
}

/* Função de comparação para inserir AvC's nas árvores de acordo com a query 7. Compara a avaliação média e devolve os valores de maneira q a árvore fique ordenada de forma decrescente.
Se as avaliações forem iguais é ordenado segundo o id dos drivers.*/
gint organiza_arvore (gconstpointer a, gconstpointer b, gpointer c) {
    AvC const* ax = a;
    AvC const* bx = b;
    double am_a = getavaliacaomediaC (ax);
    double am_b = getavaliacaomediaC (bx);
    if (am_a == am_b) {
        char *id_a = getIdC(ax);
        char *id_b = getIdC(bx);
        int compare = strcmp (id_a, id_b);
        free (id_a);
        free (id_b);
        return (0 - compare);
    }
    if (am_a < am_b) return 1;
    return -1;
}

/* Função de execução da query 7. Se N != 0 é chamada a função de ordenação da query 7 e depois a função de print.*/
int exec_Q7 (char *city, int N,FILE *res, int modo) {
    int r = 1;
    if (N){
        ordena_arvore_Q7 (city);
        r = printQ7 (city,N, res, modo) ;
    }
    return r;
}