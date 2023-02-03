#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/dataverification.h"

/* Função para verificar se a data recebida como argumento está da forma dd/mm/aaaa. Se estiver correta devolve 1 caso contrário devolve 0.*/
int verificadata (char *data) {

    if (strlen (data) != 10) return 0;
    if (!(data[2] =='/' && data [5] == '/')) return 0;
    char day_str[3] = {0};
    strncpy(day_str, data, 2);

    if ((day_str [0] < '0' || day_str [0] > '9') || (day_str [1] < '0' || day_str [1] > '9')) return 0;
    int day = atoi(day_str);

    if (day < 1 || day > 31) {
        return 0;
    }

    char month_str[3] = {0};
    strncpy(month_str, data + 3, 2);
    int month = atoi(month_str);
    if ((month_str [0] < '0' || month_str [0] > '9') || (month_str [1] < '0' || month_str [1] > '9')) return 0;

    if (month < 1 || month > 12) {
        return 0;
    }

    char year_str[5] = {0};
    strncpy(year_str, data + 6, 4);
    int year = atoi(year_str);

    if (year < 1000) {
        return 0;
    }
    return 1;
}

/* Função para verificar se a string recebida como argumento tem a forma green/basic/premium. Se estiver correta devolve 1 caso contrário devolve 0.*/
int verificacar (char *car) {
    int t = strlen (car);
    if (t < 5 && t != 7) return 0;
    for (int i = 0; i < t; i++)
        car[i] = tolower (car[i]);
    car [t] = 0;
    return (!strcmp (car, "green") || !strcmp (car, "basic") || !strcmp (car, "premium"));
}

/* Função para verificar se a string recebida como argumento tem a forma active/inactive. Se estiver correta devolve 1 caso contrário devolve 0.*/
int verificastatus (char *status) {
    int t = strlen (status);
    if (t < 6 && t != 8) return 0;
    for (int i = 0; i < t; i++)
        status[i] = tolower (status[i]);
    status [t] = 0;
    return (!strcmp (status, "inactive") || !strcmp (status, "active"));
}

/* Verifica se a string corresponde a uma avaliacao válida, isto é, um inteiro maior que 0. Se estiver correta devolve 1 caso contrário devolve 0.*/
int verificaavaliacao (char *avaliacao) {
    if (avaliacao[0] == '\0' || avaliacao[0] < '0' || avaliacao[0] > '9') return 0;
    char *sobra;
    long res = strtol (avaliacao, &sobra, 10);
    if (sobra[0] != '\0') return 0;
    if (res <= 0) return 0;
    return 1;
}


/* Verifica se a string corresponde a uma distancia válida, isto é, um inteiro maior que 0. Se estiver correta devolve 1 caso contrário devolve 0.*/
int verificadistancia (char *distance) {
    if (distance[0] == '\0') return 0;
    char *sobra;
    long res = strtol (distance, &sobra,10);
    if (sobra[0] != '\0') return 0;
    if (res <= 0) return 0;
    return 1;
}

/* Verifica se a string corresponde a uma tip válida, isto é, um double maior ou igual a 0. Se estiver correta devolve 1 caso contrário devolve 0.*/
int verificatip (char *tip) {
    if (tip[0] == '\0' || tip[0] < '0' || tip[0] > '9') return 0;
    char *sobra;
    double res = strtod (tip, &sobra);
    if (sobra[0] != '\0') return 0;
    if (res < 0) return 0;
    return 1;
}

/* Verifica se a string corresponde a um inteiro válido e maior que 0. Se estiver correto devolve 1 caso contrário devolve 0.*/
int verifica_inteiro (char *inteiro) {
    if (inteiro[0] == '\0' || inteiro[0] < '0' || inteiro[0] > '9') return 0;
    char *sobra;
    long res = strtol (inteiro, &sobra, 10);
    if (sobra[0] != '\0') return 0;
    if (res < 0) return 0;
    return 1;
}