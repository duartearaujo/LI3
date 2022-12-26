#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/dataverification.h"

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

int verificacar (char *car) {
    int t = strlen (car);
    if (t < 5 && t != 7) return 0;
    for (int i = 0; i < t; i++)
        car[i] = tolower (car[i]);
    car [t] = 0;
    return (!strcmp (car, "green") || !strcmp (car, "basic") || !strcmp (car, "premium"));
}

int verificastatus (char *status) {
    int t = strlen (status);
    if (t < 6 && t != 8) return 0;
    for (int i = 0; i < t; i++)
        status[i] = tolower (status[i]);
    status [t] = 0;
    return (!strcmp (status, "inactive") || !strcmp (status, "active"));
}

int verificaavaliacao (char *avaliacao) {
    if (avaliacao[0] == '\0') return 0;
    char *sobra;
    double res = strtod (avaliacao, &sobra);
    if (strlen (sobra) != 0) return 0;
    if (res <= 0) return 0;
    return 1;
}

int verificadistancia (char *distance) {
    if (distance[0] == '\0') return 0;
    char *sobra;
    int res = strtol (distance, &sobra,10);
    if (sobra[0] != '\0') return 0;
    if (res <= 0) return 0;
    return 1;
}

int verificatip (char *tip) {
    if (tip[0] == '\0') return 0;
    char *sobra;
    double res = strtod (tip, &sobra);
    if (sobra[0] != '\0') return 0;
    if (res < 0) return 0;
    return 1;
}