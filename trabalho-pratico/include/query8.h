#ifndef query8
#define query8

#include "../include/interactive.h"

typedef struct dados_Q8 dados_Q8;

typedef struct array_Q8 array_Q8;

dados_Q8* inicializa_dados_Q8();

void inicializa_array_Q8(int idade_enunciado,char gender_enunciado);

void passa_Para_Struct(char *nome_driver,char *nome_user,char *id,char *id_viagem,char *username,int idade_conta_driver,int idade_conta_user,int pos);

void verifica_dados_Q8 (gpointer key, RIDES* ride, void *a);

int desempate_Q8(const void *p1, const void* p2);

void ordena_Q8();

void printArray_Q8(FILE *res, int modo, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

void freeDados_Q8(dados_Q8* data);

void freeArray_Q8();

void query8Exe(FILE *res, int modo, char **argv, int *informacoespaginas,char *paginas[][linhas_por_pagina]);

#endif